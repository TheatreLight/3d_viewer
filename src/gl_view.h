#ifndef SRC_GL_VIEW_H_
#define SRC_GL_VIEW_H_

#include <QOpenGLWidget>

#include "models/data.h"

class gl_view : public QOpenGLWidget {
  Q_OBJECT

 public:
  double scaleZoom = 1;
  bool isOrtho = true, isWire = true, isNoPoint = true, isCircle = false;
  int count = 0;
  int angle = 0;
  float widthLine = 1, widthPoint = 1, red = 1, green = 1, blue = 1, redP = 1,
        greenP = 1, blueP = 1, redB = 0.05, greenB = 0.06, blueB = 0.01;
  obj_data_t *data = NULL;
  double *new_arr = NULL;
  explicit gl_view(QWidget *parent = nullptr);
  void s21_point_type_input(bool isNoPoint, bool isCircle);
  void s21_color_input(float red, float green, float blue);
  void s21_color_point_input(float redP, float greenP, float blueP);
  void s21_color_background_input(float redB, float greenB, float blueB);
  void s21_width_input(float widthLine, float widthPoint);
  void s21_draw(bool isWire, bool isOrtho);
  void s21_draw_2(double *new_arr, int count);
  void scale_x(double scale);
  void s21_updateGL();
  // protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

#endif  // SRC_GL_VIEW_H_
