#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QDir>
#include <QDebug>
#include <QTimer>
extern "C" {
#include "models/objparser.h"
#include "models/data.h"
#include "models/affinity.h"
#include "models/polygons.h"
#include "models/s21_matrix.h"
#include "models/string_util.h"
#include "s21_conf.h"
}
#include "gl_view.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    QTimer *timer;
    QImage image;
    int frame_count;

 public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 private slots:
    void on_choose_file_clicked();

    void on_save_img_clicked();

    void on_save_gif_clicked();

    void on_move_dec_x_clicked();

    void on_move_inc_x_clicked();

    void on_move_dec_y_clicked();

    void on_move_inc_y_clicked();

    void on_move_dec_z_clicked();

    void on_move_inc_z_clicked();

    void on_rotate_dec_x_clicked();

    void on_rotate_inc_x_clicked();

    void on_rotate_dec_y_clicked();

    void on_rotate_inc_y_clicked();

    void on_rotate_dec_z_clicked();

    void on_rotate_inc_z_clicked();

    void on_background_color_clicked();

    void on_vertices_color_clicked();

    void on_moving_value_x_valueChanged(double arg1);

    void on_moving_value_y_valueChanged(double arg1);

    void on_moving_value_z_valueChanged(double arg1);

    void on_rotation_angle_x_valueChanged(double arg1);

     void on_rotation_angle_y_valueChanged(double arg1);

    void on_rotation_angle_z_valueChanged(double arg1);

    void on_scale_per_valueChanged(int arg1);

    void on_scale_dec_clicked();

    void on_scale_inc_clicked();

    void on_projection_type_activated(int index);

    void on_edges_type_activated(int index);

    void on_edges_thickness_sliderMoved(int position);

    void on_verticalSlider_3_sliderMoved(int position);

    void on_verticalSlider_2_sliderMoved(int position);

    void on_verticalSlider_sliderMoved(int position);

    void on_vertices_thickness_sliderMoved(int position);

    void on_vertices_type_activated(int index);

    void gif_creator();

 private:
    gl_view *Op_Gl;
    Ui::MainWindow *ui;

    obj_data_t dataFromFile;
    conf_data_t confData;

    int zoom_per = 100, _zoom_per = 0;

    float  _moveChange_x = 0, _moveChange_y = 0, _moveChange_z = 0,
    _rotateChange_x = 0, _rotateChange_y = 0, _rotateChange_z = 0;

    double scaleZoom = 1;

    double *new_arr;
};
#endif  // SRC_MAINWINDOW_H_
