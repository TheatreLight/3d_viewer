#include "s21_conf.h"

conf_data_t read_config(void) {
  FILE *fp;
  char arr[15][15] = {"\0"};
  conf_data_t data;
  if ((fp = fopen("Settings.conf", "r")) != NULL) {
    for (int i = 0; i < 15; i++) {
      fgets(&arr[i][0], 10, fp);
    }
    fclose(fp);
    data.isValid = _VALID_CONF;
  } else {
    data.isValid = _INVALID_CONF;
  }

  data.isOrtho = atoi(&arr[0][0]);
  data.isWire = atoi(&arr[1][0]);
  data.isNoPoint = atoi(&arr[2][0]);
  data.isCircle = atoi(&arr[3][0]);

  data.widthLine = atof(&arr[4][0]);
  data.widthPoint = atof(&arr[5][0]);
  data.red = atof(&arr[6][0]);
  data.green = atof(&arr[7][0]);
  data.blue = atof(&arr[8][0]);
  data.redP = atof(&arr[9][0]);
  data.greenP = atof(&arr[10][0]);
  data.blueP = atof(&arr[11][0]);
  data.redB = atof(&arr[12][0]);
  data.greenB = atof(&arr[13][0]);
  data.blueB = atof(&arr[14][0]);

  return data;
}

int save_config(conf_data_t data) {
  char arr[15][15] = {"\0"};
  sprintf(&arr[0][0], "%d", data.isOrtho);
  sprintf(&arr[1][0], "%d", data.isWire);
  sprintf(&arr[2][0], "%d", data.isNoPoint);
  sprintf(&arr[3][0], "%d", data.isCircle);
  sprintf(&arr[4][0], "%f", data.widthLine);
  sprintf(&arr[5][0], "%f", data.widthPoint);
  sprintf(&arr[6][0], "%f", data.red);
  sprintf(&arr[7][0], "%f", data.green);
  sprintf(&arr[8][0], "%f", data.blue);
  sprintf(&arr[9][0], "%f", data.redP);
  sprintf(&arr[10][0], "%f", data.greenP);
  sprintf(&arr[11][0], "%f", data.blueP);
  sprintf(&arr[12][0], "%f", data.redB);
  sprintf(&arr[13][0], "%f", data.greenB);
  sprintf(&arr[14][0], "%f", data.blueB);

  FILE *fp;
  fp = fopen("Settings.conf", "w+");
  for (int i = 0; i < 15; i++) {
    fputs(&arr[i][0], fp);
    fputs("\n", fp);
  }
  fclose(fp);
  return 0;
}
