#include "objparser.h"
#define _GNU_SOURCE

#ifdef _WIN32
size_t getline(char **lineptr, size_t *n, FILE *stream);

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while (c != EOF) {
        size_t len = p - bufptr;
        if (len > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            p = bufptr + len;
        }
        *p = c;
        p++;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
#endif

int parse_vertex(obj_data_t *data, char *line, int i) {
    int result = 0;
    char *sep = " ";
    char *tmp = strtok(line, sep);
    for (int k = 0; tmp && k < 3; k++) {
        double d = 0.0;
        int is_scaned = sscanf(tmp, "%lf", &d);
        if (is_scaned) data->matrix_3d.matrix[i][k] = d;
        tmp = strtok(NULL, sep);
    }
    if (tmp) {
        result = 4;  // Vertex parsing error
    }
    return result;
}

int vertexes_size(char *str) {
    int facet_count = 0;
    char *tmp_sep = " ";
    char *tmp = strtok(str, tmp_sep);
    while (tmp) {
        facet_count++;
        tmp = strtok(NULL, tmp_sep);
    }
    return facet_count;
}

int parse_facets(obj_data_t *data, char *line, int j) {
    int facet_count = 0;
    char *fasets = NULL;
    put_to_str(&fasets, "%s", line);
    facet_count = vertexes_size(fasets);
    free_str(&fasets);
    if (facet_count > 3) {
        data->polygons[j].vertexes =
                (int *)realloc(data->polygons[j].vertexes, (facet_count + 1 ) * sizeof(int));
        data->polygons[j].numbers_of_vertexes_in_facets = facet_count;
    }
    char *tmp_sep = " ";
    char *tmp = strtok(line, tmp_sep);
    for (int k = 1; tmp && k <= facet_count; k++) {
        char *vrtx_sep = "/";
        char *vertex_str = NULL;
        put_to_str(&vertex_str, tmp);
        char *vertex_tmp = strtok(vertex_str, vrtx_sep);
        int vertex = 0;
        int is_scaned = sscanf(vertex_tmp, "%d", &vertex);
        if (vertex_tmp && is_scaned) data->polygons[j].vertexes[k] = vertex;
        free_str(&vertex_str);
        size_t len = strlen(tmp) + 1;
        if (k != facet_count) {
            tmp = strtok(tmp + len, tmp_sep);
        } else {
            tmp = strtok(tmp, tmp_sep);
            tmp = strtok(NULL, tmp_sep);
        }
    }
    if (tmp) {
        facet_count = -1;  // Facets parsing error
    }
    return facet_count;
}

/**
 * @brief 
 * 
 * @param file_name путь к obj файлу
 * @return int код с результатом чтения файла
 */
int objparser(obj_data_t *src, char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        return 1;  // No such file or directory
    }
    int result = 0;  // success
    int read = 0;
    int count_of_vertexes = 0;
    int count_of_facets = 0;
    char *line = NULL;
    size_t len = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        if (line == strstr(line, "v ")) {
            count_of_vertexes++;
        } else if (line == strstr(line, "f ")) {
            count_of_facets++;
        }
    }

    if (!count_of_vertexes || !count_of_facets) {
        fclose(file);
        return 3;  // Incorrect obj file
    }

    obj_data_t data = s21_create_data(count_of_vertexes, count_of_facets);
    int i = 1;
    int j = 1;
    fseek(file, 0L, SEEK_SET);
    while (!result && (read = getline(&line, &len, file)) != -1) {
        // char *vertexes = strstr(line, "v ");
        if (line == strstr(line, "v ")) {
            result = parse_vertex(&data, line + 2, i);
            i++;
        } else if (line == strstr(line, "f ")) {
            int numbers_of_vertexes_in_facets = parse_facets(&data, line + 2, j);
            j++;
            if (numbers_of_vertexes_in_facets == -1) {
                result = 5;  // Facets parsing error
                break;
            }
            data.numbers_of_vertexes_in_all_facets += numbers_of_vertexes_in_facets;
        }
    }
    if (line) free(line);
    if (!result && !feof(file)) result = 2;  // "FEOF error"
    fclose(file);
    *src = data;
    return result;
}
