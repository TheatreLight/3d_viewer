#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../models/objparser.h"
#include "../models/affinity.h"

START_TEST(objparser_test) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.numbers_of_vertexes_in_all_facets = 36;
    exp.matrix_3d.matrix[1][0] = 1.0;
    exp.matrix_3d.matrix[1][1] = -1.0;
    exp.matrix_3d.matrix[1][2] = -1.0;

    exp.matrix_3d.matrix[2][0] = 1.0;
    exp.matrix_3d.matrix[2][1] = -1.0;
    exp.matrix_3d.matrix[2][2] = 1.0;

    exp.matrix_3d.matrix[3][0] = -1.0;
    exp.matrix_3d.matrix[3][1] = -1.0;
    exp.matrix_3d.matrix[3][2] = 1.0;

    exp.matrix_3d.matrix[4][0] = -1.0;
    exp.matrix_3d.matrix[4][1] = -1.0;
    exp.matrix_3d.matrix[4][2] = -1.0;

    exp.matrix_3d.matrix[5][0] = 1.0;
    exp.matrix_3d.matrix[5][1] = 1.0;
    exp.matrix_3d.matrix[5][2] = -0.999999;

    exp.matrix_3d.matrix[6][0] = 0.999999;
    exp.matrix_3d.matrix[6][1] = 1.0;
    exp.matrix_3d.matrix[6][2] = 1.000001;

    exp.matrix_3d.matrix[7][0] = -1.0;
    exp.matrix_3d.matrix[7][1] = 1.0;
    exp.matrix_3d.matrix[7][2] = 1.0;

    exp.matrix_3d.matrix[8][0] = -1.0;
    exp.matrix_3d.matrix[8][1] = 1.0;
    exp.matrix_3d.matrix[8][2] = -1.0;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    int exp_numbers_of_vertexes_in_all_facets =
            exp.numbers_of_vertexes_in_all_facets - data.numbers_of_vertexes_in_all_facets;

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
    ck_assert_int_eq(exp_numbers_of_vertexes_in_all_facets, 0);
}
END_TEST

Suite *objparser_suite(void) {
    Suite *s;
    s = suite_create("objparser_test");

    TCase *tc_objparser;
    tc_objparser = tcase_create("Parser_test");
    tcase_add_test(tc_objparser, objparser_test);
    suite_add_tcase(s, tc_objparser);

    return s;
}

START_TEST(move_x) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.matrix_3d.matrix[1][0] = 2.0;
    exp.matrix_3d.matrix[1][1] = -1.0;
    exp.matrix_3d.matrix[1][2] = -1.0;

    exp.matrix_3d.matrix[2][0] = 2.0;
    exp.matrix_3d.matrix[2][1] = -1.0;
    exp.matrix_3d.matrix[2][2] = 1.0;

    exp.matrix_3d.matrix[3][0] = 0.0;
    exp.matrix_3d.matrix[3][1] = -1.0;
    exp.matrix_3d.matrix[3][2] = 1.0;

    exp.matrix_3d.matrix[4][0] = 0.0;
    exp.matrix_3d.matrix[4][1] = -1.0;
    exp.matrix_3d.matrix[4][2] = -1.0;

    exp.matrix_3d.matrix[5][0] = 2.0;
    exp.matrix_3d.matrix[5][1] = 1.0;
    exp.matrix_3d.matrix[5][2] = -0.999999;

    exp.matrix_3d.matrix[6][0] = 1.999999;
    exp.matrix_3d.matrix[6][1] = 1.0;
    exp.matrix_3d.matrix[6][2] = 1.000001;

    exp.matrix_3d.matrix[7][0] = 0.0;
    exp.matrix_3d.matrix[7][1] = 1.0;
    exp.matrix_3d.matrix[7][2] = 1.0;

    exp.matrix_3d.matrix[8][0] = 0.0;
    exp.matrix_3d.matrix[8][1] = 1.0;
    exp.matrix_3d.matrix[8][2] = -1.0;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);
    s21_move(&data, 1, 0, 0);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
}
END_TEST

START_TEST(move_y) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.matrix_3d.matrix[1][0] = 1.0;
    exp.matrix_3d.matrix[1][1] = 0.0;
    exp.matrix_3d.matrix[1][2] = -1.0;

    exp.matrix_3d.matrix[2][0] = 1.0;
    exp.matrix_3d.matrix[2][1] = 0.0;
    exp.matrix_3d.matrix[2][2] = 1.0;

    exp.matrix_3d.matrix[3][0] = -1.0;
    exp.matrix_3d.matrix[3][1] = 0.0;
    exp.matrix_3d.matrix[3][2] = 1.0;

    exp.matrix_3d.matrix[4][0] = -1.0;
    exp.matrix_3d.matrix[4][1] = 0.0;
    exp.matrix_3d.matrix[4][2] = -1.0;

    exp.matrix_3d.matrix[5][0] = 1.0;
    exp.matrix_3d.matrix[5][1] = 2.0;
    exp.matrix_3d.matrix[5][2] = -0.999999;

    exp.matrix_3d.matrix[6][0] = 0.999999;
    exp.matrix_3d.matrix[6][1] = 2.0;
    exp.matrix_3d.matrix[6][2] = 1.000001;

    exp.matrix_3d.matrix[7][0] = -1.0;
    exp.matrix_3d.matrix[7][1] = 2.0;
    exp.matrix_3d.matrix[7][2] = 1.0;

    exp.matrix_3d.matrix[8][0] = -1.0;
    exp.matrix_3d.matrix[8][1] = 2.0;
    exp.matrix_3d.matrix[8][2] = -1.0;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);
    s21_move(&data, 0, 1, 0);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
}
END_TEST

START_TEST(move_z) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.matrix_3d.matrix[1][0] = 1.0;
    exp.matrix_3d.matrix[1][1] = -1.0;
    exp.matrix_3d.matrix[1][2] = 0.0;

    exp.matrix_3d.matrix[2][0] = 1.0;
    exp.matrix_3d.matrix[2][1] = -1.0;
    exp.matrix_3d.matrix[2][2] = 2.0;

    exp.matrix_3d.matrix[3][0] = -1.0;
    exp.matrix_3d.matrix[3][1] = -1.0;
    exp.matrix_3d.matrix[3][2] = 2.0;

    exp.matrix_3d.matrix[4][0] = -1.0;
    exp.matrix_3d.matrix[4][1] = -1.0;
    exp.matrix_3d.matrix[4][2] = 0.0;

    exp.matrix_3d.matrix[5][0] = 1.0;
    exp.matrix_3d.matrix[5][1] = 1.0;
    exp.matrix_3d.matrix[5][2] = 0.000001;

    exp.matrix_3d.matrix[6][0] = 0.999999;
    exp.matrix_3d.matrix[6][1] = 1.0;
    exp.matrix_3d.matrix[6][2] = 2.000001;

    exp.matrix_3d.matrix[7][0] = -1.0;
    exp.matrix_3d.matrix[7][1] = 1.0;
    exp.matrix_3d.matrix[7][2] = 2.0;

    exp.matrix_3d.matrix[8][0] = -1.0;
    exp.matrix_3d.matrix[8][1] = 1.0;
    exp.matrix_3d.matrix[8][2] = 0.0;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);
    s21_move(&data, 0, 0, 1);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
}
END_TEST

START_TEST(move_xyz) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.matrix_3d.matrix[1][0] = 2.0;
    exp.matrix_3d.matrix[1][1] = 0.0;
    exp.matrix_3d.matrix[1][2] = 0.0;

    exp.matrix_3d.matrix[2][0] = 2.0;
    exp.matrix_3d.matrix[2][1] = 0.0;
    exp.matrix_3d.matrix[2][2] = 2.0;

    exp.matrix_3d.matrix[3][0] = 0.0;
    exp.matrix_3d.matrix[3][1] = 0.0;
    exp.matrix_3d.matrix[3][2] = 2.0;

    exp.matrix_3d.matrix[4][0] = 0.0;
    exp.matrix_3d.matrix[4][1] = 0.0;
    exp.matrix_3d.matrix[4][2] = 0.0;

    exp.matrix_3d.matrix[5][0] = 2.0;
    exp.matrix_3d.matrix[5][1] = 2.0;
    exp.matrix_3d.matrix[5][2] = 0.000001;

    exp.matrix_3d.matrix[6][0] = 1.999999;
    exp.matrix_3d.matrix[6][1] = 2.0;
    exp.matrix_3d.matrix[6][2] = 2.000001;

    exp.matrix_3d.matrix[7][0] = 0.0;
    exp.matrix_3d.matrix[7][1] = 2.0;
    exp.matrix_3d.matrix[7][2] = 2.0;

    exp.matrix_3d.matrix[8][0] = 0.0;
    exp.matrix_3d.matrix[8][1] = 2.0;
    exp.matrix_3d.matrix[8][2] = 0.0;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);
    s21_move(&data, 1, 1, 1);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
}
END_TEST

Suite *move_suite(void) {
    Suite *s;
    s = suite_create("move_test");

    TCase *tc_move_x;
    tc_move_x = tcase_create("Move_x_test");
    tcase_add_test(tc_move_x, move_x);
    suite_add_tcase(s, tc_move_x);

    TCase *tc_move_y;
    tc_move_y = tcase_create("Move_y_test");
    tcase_add_test(tc_move_y, move_y);
    suite_add_tcase(s, tc_move_y);

    TCase *tc_move_z;
    tc_move_z = tcase_create("Move_y_test");
    tcase_add_test(tc_move_z, move_z);
    suite_add_tcase(s, tc_move_z);

    TCase *tc_move_xyz;
    tc_move_xyz = tcase_create("Move_y_test");
    tcase_add_test(tc_move_xyz, move_xyz);
    suite_add_tcase(s, tc_move_xyz);

    return s;
}

START_TEST(scale_2) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.matrix_3d.matrix[1][0] = 1.0 * 2;
    exp.matrix_3d.matrix[1][1] = -1.0 * 2;
    exp.matrix_3d.matrix[1][2] = -1.0 * 2;

    exp.matrix_3d.matrix[2][0] = 1.0 * 2;
    exp.matrix_3d.matrix[2][1] = -1.0 * 2;
    exp.matrix_3d.matrix[2][2] = 1.0 * 2;

    exp.matrix_3d.matrix[3][0] = -1.0 * 2;
    exp.matrix_3d.matrix[3][1] = -1.0 * 2;
    exp.matrix_3d.matrix[3][2] = 1.0 * 2;

    exp.matrix_3d.matrix[4][0] = -1.0 * 2;
    exp.matrix_3d.matrix[4][1] = -1.0 * 2;
    exp.matrix_3d.matrix[4][2] = -1.0 * 2;

    exp.matrix_3d.matrix[5][0] = 1.0 * 2;
    exp.matrix_3d.matrix[5][1] = 1.0 * 2;
    exp.matrix_3d.matrix[5][2] = -0.999999 * 2;

    exp.matrix_3d.matrix[6][0] = 0.999999 * 2;
    exp.matrix_3d.matrix[6][1] = 1.0 * 2;
    exp.matrix_3d.matrix[6][2] = 1.000001 * 2;

    exp.matrix_3d.matrix[7][0] = -1.0 * 2;
    exp.matrix_3d.matrix[7][1] = 1.0 * 2;
    exp.matrix_3d.matrix[7][2] = 1.0 * 2;

    exp.matrix_3d.matrix[8][0] = -1.0 * 2;
    exp.matrix_3d.matrix[8][1] = 1.0 * 2;
    exp.matrix_3d.matrix[8][2] = -1.0 * 2;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);
    s21_scale(&data, 2.0);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
}
END_TEST

Suite *scale_suite(void) {
    Suite *s;
    s = suite_create("scale_test");

    TCase *tc_scale;
    tc_scale = tcase_create("scale_test");
    tcase_add_test(tc_scale, scale_2);
    suite_add_tcase(s, tc_scale);

    return s;
}

START_TEST(rotate_x) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.matrix_3d.matrix[1][0] = 1.0;
    exp.matrix_3d.matrix[1][1] = -0.366025;
    exp.matrix_3d.matrix[1][2] = -1.366025;

    exp.matrix_3d.matrix[2][0] = 1.0;
    exp.matrix_3d.matrix[2][1] = -1.366025;
    exp.matrix_3d.matrix[2][2] = 0.366025;

    exp.matrix_3d.matrix[3][0] = -1.0;
    exp.matrix_3d.matrix[3][1] = -1.366025;
    exp.matrix_3d.matrix[3][2] = 0.366025;

    exp.matrix_3d.matrix[4][0] = -1.0;
    exp.matrix_3d.matrix[4][1] = -0.366025;
    exp.matrix_3d.matrix[4][2] = -1.366025;

    exp.matrix_3d.matrix[5][0] = 1.0;
    exp.matrix_3d.matrix[5][1] = 1.366025;
    exp.matrix_3d.matrix[5][2] = -0.366025;

    exp.matrix_3d.matrix[6][0] = 0.999999;
    exp.matrix_3d.matrix[6][1] = 0.366025;
    exp.matrix_3d.matrix[6][2] = 1.366026;

    exp.matrix_3d.matrix[7][0] = -1.0;
    exp.matrix_3d.matrix[7][1] = 0.366025;
    exp.matrix_3d.matrix[7][2] = 1.366025;

    exp.matrix_3d.matrix[8][0] = -1.0;
    exp.matrix_3d.matrix[8][1] = 1.366025;
    exp.matrix_3d.matrix[8][2] = -0.366025;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);
    s21_rotate(&data, 30, 0, 0);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
}
END_TEST

START_TEST(rotate_y) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.matrix_3d.matrix[1][0] = 1.366025;
    exp.matrix_3d.matrix[1][1] = -1.0;
    exp.matrix_3d.matrix[1][2] = -0.366025;

    exp.matrix_3d.matrix[2][0] = 0.366025;
    exp.matrix_3d.matrix[2][1] = -1.0;
    exp.matrix_3d.matrix[2][2] = 1.366025;

    exp.matrix_3d.matrix[3][0] = -1.366025;
    exp.matrix_3d.matrix[3][1] = -1.0;
    exp.matrix_3d.matrix[3][2] = 0.366025;

    exp.matrix_3d.matrix[4][0] = -0.366025;
    exp.matrix_3d.matrix[4][1] = -1.0;
    exp.matrix_3d.matrix[4][2] = -1.366025;

    exp.matrix_3d.matrix[5][0] = 1.366025;
    exp.matrix_3d.matrix[5][1] = 1.0;
    exp.matrix_3d.matrix[5][2] = -0.366025;

    exp.matrix_3d.matrix[6][0] = 0.366025;
    exp.matrix_3d.matrix[6][1] = 1.0;
    exp.matrix_3d.matrix[6][2] = 1.366025;

    exp.matrix_3d.matrix[7][0] = -1.366025;
    exp.matrix_3d.matrix[7][1] = 1.0;
    exp.matrix_3d.matrix[7][2] = 0.366025;

    exp.matrix_3d.matrix[8][0] = -0.366025;
    exp.matrix_3d.matrix[8][1] = 1.0;
    exp.matrix_3d.matrix[8][2] = -1.366025;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);
    s21_rotate(&data, 0, 30, 0);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
}
END_TEST

START_TEST(rotate_z) {
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    obj_data_t exp = s21_create_data(8, 12);
    exp.matrix_3d.matrix[1][0] = 1.366025;
    exp.matrix_3d.matrix[1][1] = -0.366025;
    exp.matrix_3d.matrix[1][2] = -1.0;

    exp.matrix_3d.matrix[2][0] = 1.366025;
    exp.matrix_3d.matrix[2][1] = -0.366025;
    exp.matrix_3d.matrix[2][2] = 1.0;

    exp.matrix_3d.matrix[3][0] = -0.366025;
    exp.matrix_3d.matrix[3][1] = -1.366025;
    exp.matrix_3d.matrix[3][2] = 1.0;

    exp.matrix_3d.matrix[4][0] = -0.366025;
    exp.matrix_3d.matrix[4][1] = -1.366025;
    exp.matrix_3d.matrix[4][2] = -1.0;

    exp.matrix_3d.matrix[5][0] = 0.366025;
    exp.matrix_3d.matrix[5][1] = 1.366025;
    exp.matrix_3d.matrix[5][2] = -0.999999;

    exp.matrix_3d.matrix[6][0] = 0.366025;
    exp.matrix_3d.matrix[6][1] = 1.366025;
    exp.matrix_3d.matrix[6][2] = 1.000001;

    exp.matrix_3d.matrix[7][0] = -1.366025;
    exp.matrix_3d.matrix[7][1] = 0.366025;
    exp.matrix_3d.matrix[7][2] = 1.0;

    exp.matrix_3d.matrix[8][0] = -1.366025;
    exp.matrix_3d.matrix[8][1] = 0.366025;
    exp.matrix_3d.matrix[8][2] = -1.0;

    exp.polygons[1].vertexes[1] = 2;
    exp.polygons[1].vertexes[2] = 3;
    exp.polygons[1].vertexes[3] = 4;

    exp.polygons[2].vertexes[1] = 8;
    exp.polygons[2].vertexes[2] = 7;
    exp.polygons[2].vertexes[3] = 6;

    exp.polygons[3].vertexes[1] = 5;
    exp.polygons[3].vertexes[2] = 6;
    exp.polygons[3].vertexes[3] = 2;

    exp.polygons[4].vertexes[1] = 6;
    exp.polygons[4].vertexes[2] = 7;
    exp.polygons[4].vertexes[3] = 3;

    exp.polygons[5].vertexes[1] = 3;
    exp.polygons[5].vertexes[2] = 7;
    exp.polygons[5].vertexes[3] = 8;

    exp.polygons[6].vertexes[1] = 1;
    exp.polygons[6].vertexes[2] = 4;
    exp.polygons[6].vertexes[3] = 8;

    exp.polygons[7].vertexes[1] = 1;
    exp.polygons[7].vertexes[2] = 2;
    exp.polygons[7].vertexes[3] = 4;

    exp.polygons[8].vertexes[1] = 5;
    exp.polygons[8].vertexes[2] = 8;
    exp.polygons[8].vertexes[3] = 6;

    exp.polygons[9].vertexes[1] = 1;
    exp.polygons[9].vertexes[2] = 5;
    exp.polygons[9].vertexes[3] = 2;

    exp.polygons[10].vertexes[1] = 2;
    exp.polygons[10].vertexes[2] = 6;
    exp.polygons[10].vertexes[3] = 3;

    exp.polygons[11].vertexes[1] = 4;
    exp.polygons[11].vertexes[2] = 3;
    exp.polygons[11].vertexes[3] = 8;

    exp.polygons[12].vertexes[1] = 5;
    exp.polygons[12].vertexes[2] = 1;
    exp.polygons[12].vertexes[3] = 8;

    int act_result = objparser(&data, file_name);
    s21_rotate(&data, 0, 0, 30);

    int is_matrix_eq = s21_eq_matrix(&data.matrix_3d, &exp.matrix_3d);

    int is_polygons_eq = SUCCESS;
    for (int i = 1; i <= data.count_of_facets; i++) {
        for (int j = 1; j <= 3; j++) {
            if (data.polygons[i].vertexes[j] != exp.polygons[i].vertexes[j]) {
                is_polygons_eq = FAILURE;
                break;
            }
        }
        if (is_polygons_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    s21_remove_data(&exp);

    ck_assert_int_eq(act_result, 0);

    ck_assert_int_eq(is_matrix_eq, SUCCESS);
    ck_assert_int_eq(is_polygons_eq, SUCCESS);
}
END_TEST

Suite *rotate_suite(void) {
    Suite *s;
    s = suite_create("rotate_test");

    TCase *tc_rotate_x;
    tc_rotate_x = tcase_create("rotate_x_test");
    tcase_add_test(tc_rotate_x, rotate_x);
    suite_add_tcase(s, tc_rotate_x);

    TCase *tc_rotate_y;
    tc_rotate_y = tcase_create("rotate_y_test");
    tcase_add_test(tc_rotate_y, rotate_y);
    suite_add_tcase(s, tc_rotate_y);

    TCase *tc_rotate_z;
    tc_rotate_z = tcase_create("rotate_z_test");
    tcase_add_test(tc_rotate_z, rotate_z);
    suite_add_tcase(s, tc_rotate_z);

    return s;
}

START_TEST(create_cube_arr) {
    // Подготовка
    char *file_name = "resurces/сube.obj";
    obj_data_t data;
    int act_result = objparser(&data, file_name);

    const double exp_array[] = {
        1.000000, -1.000000,  1.000000,  -1.000000, -1.000000,  1.000000,  -1.000000, -1.000000, -1.000000,
       -1.000000,  1.000000, -1.000000,  -1.000000,  1.000000,  1.000000,   0.999999,  1.000000,  1.000001,
        1.000000,  1.000000, -0.999999,   0.999999,  1.000000,  1.000001,   1.000000, -1.000000,  1.000000,
        0.999999,  1.000000,  1.000001,  -1.000000,  1.000000,  1.000000,  -1.000000, -1.000000,  1.000000,
       -1.000000, -1.000000,  1.000000,  -1.000000,  1.000000,  1.000000,  -1.000000,  1.000000, -1.000000,
        1.000000, -1.000000, -1.000000,  -1.000000, -1.000000, -1.000000,  -1.000000,  1.000000, -1.000000,
        1.000000, -1.000000, -1.000000,   1.000000, -1.000000,  1.000000,  -1.000000, -1.000000, -1.000000,
        1.000000,  1.000000, -0.999999,  -1.000000,  1.000000, -1.000000,   0.999999,  1.000000,  1.000001,
        1.000000, -1.000000, -1.000000,   1.000000,  1.000000, -0.999999,   1.000000, -1.000000,  1.000000,
        1.000000, -1.000000,  1.000000,   0.999999,  1.000000,  1.000001,  -1.000000, -1.000000,  1.000000,
       -1.000000, -1.000000, -1.000000,  -1.000000, -1.000000,  1.000000,  -1.000000,  1.000000, -1.000000,
        1.000000,  1.000000, -0.999999,   1.000000, -1.000000, -1.000000,  -1.000000,  1.000000, -1.000000};

    if (act_result) {
        char *err_msg[] = _OBJPARSER_ERROR_;
        ck_assert_msg(act_result != 0, "%s", err_msg[act_result]);
    }

    // Действие
    double *d = (double *)calloc(data.numbers_of_vertexes_in_all_facets * 3, sizeof(double));
    double *actual_arr = get_vertex_array_from_data(&data, d);

    int is_arr_eq = SUCCESS;
    for (int i = 0; i < data.count_of_facets * 3 * 3; i++) {
        if (actual_arr[i] != exp_array[i]) {
            is_arr_eq = FAILURE;
            break;
        }
        if (is_arr_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    if (actual_arr) free(actual_arr);

    // Проверка
    ck_assert_int_eq(is_arr_eq, SUCCESS);
}
END_TEST

START_TEST(create_cone_arr) {
    // Подготовка
    char *file_name = "resurces/cone.obj";
    obj_data_t data;
    int act_result = objparser(&data, file_name);

    const double exp_array[] = {
        0,         -1, -1,         0,        1,  0,         0.19509,   -1,  -0.980785,     // 1
        0.19509,   -1, -0.980785,  0,        1,  0,         0.382683,  -1,  -0.923880,     // 2
        0.382683,  -1, -0.923880,  0,        1,  0,         0.555570,  -1,  -0.83147,      // 3
        0.555570,  -1, -0.83147,   0,        1,  0,         0.707107,  -1,  -0.707107,     // 4
        0.707107,  -1, -0.707107,  0,        1,  0,         0.831470,  -1,  -0.55557,      // 5
        0.831470,  -1, -0.55557,   0,        1,  0,         0.92388,   -1,  -0.382683,     // 6
        0.92388,   -1, -0.382683,  0,        1,  0,         0.980785,  -1,  -0.19509,      // 7
        0.980785,  -1, -0.19509,   0,        1,  0,         1,         -1,   0,      // 8
        1,         -1,  0,         0,        1,  0,         0.980785,  -1,   0.19509,      // 9
        0.980785,  -1,  0.19509,   0,        1,  0,         0.92388,   -1,   0.382683,      // 10
        0.92388,   -1,  0.382683,  0,        1,  0,         0.83147,   -1,   0.55557,      // 11
        0.831470,  -1,  0.55557,   0,        1,  0,         0.707107,  -1,   0.707107,      // 12
        0.707107,  -1,  0.707107,  0,        1,  0,         0.555570,  -1,   0.83147,      // 13
        0.555570,  -1,  0.83147,   0,        1,  0,         0.382683,  -1,   0.92388,      // 14
        0.382683,  -1,  0.923880,  0,        1,  0,         0.19509,   -1,   0.980785,      // 15
        0.19509,   -1,  0.980785,  0,        1,  0,         0,         -1,   1,      // 16
        0,         -1,  1,         0,        1,  0,        -0.19509,   -1,   0.980785,      // 17
       -0.19509,   -1,  0.980785,  0,        1,  0,        -0.382683,  -1,   0.92388,      // 18
       -0.382683,  -1,  0.92388,   0,        1,  0,        -0.555570,  -1,   0.83147,      // 19
       -0.555570,  -1,  0.83147,   0,        1,  0,        -0.707107,  -1,   0.707107,      // 20
       -0.707107,  -1,  0.707107,  0,        1,  0,        -0.831469,  -1,   0.55557,      // 21
       -0.831469,  -1,  0.55557,   0,        1,  0,        -0.92388,   -1,   0.382684,      // 22
       -0.92388,   -1,  0.382684,  0,        1,  0,        -0.980785,  -1,   0.19509,      // 23
       -0.980785,  -1,  0.19509,   0,        1,  0,        -1,         -1,   0,      // 24
       -1,         -1,  0,         0,        1,  0,        -0.980785,  -1,  -0.19509,      // 25
       -0.980785,  -1, -0.19509,   0,        1,  0,        -0.923879,   -1, -0.382684,      // 26
       -0.923879,   -1, -0.382684,  0,        1,  0,        -0.831470,  -1, -0.55557,      // 27
       -0.831470,  -1, -0.55557,   0,        1,  0,        -0.707107,  -1,  -0.707107,      // 28
       -0.707107,  -1, -0.707107,  0,        1,  0,        -0.555570,  -1,  -0.83147,      // 29
       -0.555570,  -1, -0.83147,   0,        1,  0,        -0.382683,  -1,  -0.92388,      // 30
        0,         -1, -1,
        0.19509, -1, -0.980785,
        0.382683,  -1, -0.92388,
        0.55557,  -1,  -0.83147,
        0.707107,  -1, -0.707107,
        0.83147, -1, -0.55557,
        0.92388,   -1, -0.382683,
        0.980785, -1, -0.19509,
        1.000000,  -1,  0.000000,
        0.980785, -1,  0.195090,
        0.923880,  -1,  0.382683,
        0.831470, -1,  0.555570,
        0.707107,  -1,  0.707107,
        0.55557, -1, -0.83147,
         0.382683,  -1,  0.92388,
          0.19509,  -1,  0.980785,
        0,         -1,  1,
        -0.195090,  -1,  0.980785,
        -0.382683,  -1,  0.92388,
         -0.555570, -1,  0.83147,
       -0.707107,  -1,  0.707107,
       -0.831469,  -1,  0.555570,
       -0.923880,  -1,  0.382684,
       -0.980785, -1,  0.19509,
       -1,         -1,  0,
       -0.980785,  -1, -0.195090,
       -0.923879,  -1, -0.382684,
       -0.83147, -1, -0.55557,
       -0.707107,  -1, -0.707107,
       -0.55557,   -1, -0.83147,
       -0.382683,  -1, -0.92388,
       -0.19509, -1, -0.980785,
       -0.382683,  -1, -0.923880,  0,        1,  0,        -0.195090,  -1, -0.980785,
       -0.195090,  -1, -0.980785,  0,        1,  0,         0.000000,  -1, -1.000000
       };

    if (act_result) {
        char *err_msg[] = _OBJPARSER_ERROR_;
        ck_assert_msg(act_result != 0, "%s", err_msg[act_result]);
    }

    // Действие
    double *d = (double *)calloc(data.numbers_of_vertexes_in_all_facets * 3, sizeof(double));
    double *actual_arr = get_vertex_array_from_data(&data, d);
    int is_arr_eq = SUCCESS;
    for (int i = 0; i < data.count_of_facets * 3 * 3; i++) {
        double a = actual_arr[i];
        double e = exp_array[i];
        double sub = a - e;
        sub = sub < 0 ? -sub : sub;
        if (sub > 1e-6) {
            is_arr_eq = FAILURE;
            break;
        }
        if (is_arr_eq == FAILURE) {
            break;
        }
    }

    s21_remove_data(&data);
    if (actual_arr) free(actual_arr);

    // Проверка
    ck_assert_int_eq(is_arr_eq, SUCCESS);
}
END_TEST

Suite *create_suite(void) {
    Suite *s;
    s = suite_create("create_arr_test");

    TCase *tc_create_cube_arr;
    tc_create_cube_arr = tcase_create("create_cube_arr_test");
    tcase_add_test(tc_create_cube_arr, create_cube_arr);
    suite_add_tcase(s, tc_create_cube_arr);

    TCase *tc_create_cone_arr;
    tc_create_cone_arr = tcase_create("create_cone_arr_test");
    tcase_add_test(tc_create_cone_arr, create_cone_arr);
    suite_add_tcase(s, tc_create_cone_arr);

    return s;
}

int main(void) {
    int number_failed;
    SRunner *sr;
    sr = srunner_create(objparser_suite());
    srunner_add_suite(sr, move_suite());
    srunner_add_suite(sr, scale_suite());
    srunner_add_suite(sr, rotate_suite());
    srunner_add_suite(sr, create_suite());
    // srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
