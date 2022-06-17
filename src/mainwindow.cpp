#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <locale>
#include <stdio.h>

QSize size(640, 480);
QGifImage gif(size);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setlocale(LC_ALL, "C");
    ui->setupUi(this);

    confData = read_config();
    if (confData.isValid == _INVALID_CONF) qDebug() << "Settings.conf not found";
    ui->openGLWidget->s21_color_background_input(confData.redB, confData.greenB, confData.blueB);
    ui->openGLWidget->s21_draw(confData.isWire, confData.isOrtho);
    ui->openGLWidget->s21_color_input(confData.red, confData.green, confData.blue);
    ui->openGLWidget->s21_color_point_input(confData.redP, confData.greenP, confData.blueP);
    ui->openGLWidget->s21_width_input(confData.widthLine, confData.widthPoint);
    ui->openGLWidget->s21_point_type_input(confData.isNoPoint, confData.isCircle);

    frame_count = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::gif_creator);
}

MainWindow::~MainWindow()
{
    setlocale(LC_ALL, "C");
    save_config(confData);
    delete[] new_arr;
    delete timer;
    delete ui;
}

void MainWindow::on_choose_file_clicked()
{
    setlocale(LC_ALL, "C");
    QFileDialog file_dialog(this);
    QString path = file_dialog.getOpenFileName(this, tr("Open a file"), "", tr("Obj(*.obj)"));

    ui->show_filename->setText(path);

    QByteArray bytes = path.toLocal8Bit();
    char *cstr = bytes.data();
    objparser(&dataFromFile, cstr);

    QString str;
    str.setNum(dataFromFile.count_of_vertexes);
    ui->show_vertices_num->setText(str);

    new_arr = new double[dataFromFile.numbers_of_vertexes_in_all_facets * 3];
    get_vertex_array_from_data(&dataFromFile, new_arr);

    QString str_1;
    str_1.setNum(dataFromFile.count_of_facets);
    ui->show_edges_num->setText(str_1);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}

void MainWindow::on_save_img_clicked()
{
    QFileDialog file_dialog_img(this);
    QString f_name = file_dialog_img.getSaveFileName(this, tr("Save a screenshot"), "", tr("image (*.bmp *.jpeg)"));
    QImage img = ui->openGLWidget->grabFramebuffer();
    img.save(f_name);
}

void MainWindow::on_save_gif_clicked()
{
    timer->start(100);
}

void MainWindow::gif_creator() {
    if (frame_count < 50) {
        image = ui->openGLWidget->grabFramebuffer();
        gif.addFrame(image);
        frame_count++;
    } else {
        frame_count = 0;
        timer->stop();

        QFileDialog file_dialog_gif(this);
        QString f_name_gif = file_dialog_gif.getSaveFileName(this, tr("Save a gif"), "", tr("gif (*.gif)"));
        gif.save(f_name_gif);
     }
}

void MainWindow::on_move_dec_x_clicked()
{
    s21_move(&dataFromFile, _moveChange_x * -1, 0, 0);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_move_inc_x_clicked()
{
    s21_move(&dataFromFile, _moveChange_x, 0, 0);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_move_dec_y_clicked()
{
    s21_move(&dataFromFile, 0, _moveChange_y * -1, 0);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_move_inc_y_clicked()
{
    s21_move(&dataFromFile, 0, _moveChange_y, 0);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_move_dec_z_clicked()
{
    s21_move(&dataFromFile, 0, 0, _moveChange_z * -1);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_move_inc_z_clicked()
{
    s21_move(&dataFromFile, 0, 0, _moveChange_z);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_rotate_dec_x_clicked()
{
    s21_rotate(&dataFromFile, _rotateChange_x * -1, 0, 0);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_rotate_inc_x_clicked()
{
    s21_rotate(&dataFromFile, _rotateChange_x, 0, 0);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_rotate_dec_y_clicked()
{
    s21_rotate(&dataFromFile, 0, _rotateChange_y * -1, 0);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_rotate_inc_y_clicked()
{
    s21_rotate(&dataFromFile, 0, _rotateChange_y, 0);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_rotate_dec_z_clicked()
{
    s21_rotate(&dataFromFile, 0, 0, _rotateChange_z * -1);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}


void MainWindow::on_rotate_inc_z_clicked()
{
    s21_rotate(&dataFromFile, 0, 0, _rotateChange_z);
    get_vertex_array_from_data(&dataFromFile, new_arr);

    ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
}

void MainWindow::on_background_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color");
    confData.redB = color.redF();
    confData.greenB = color.greenF();
    confData.blueB = color.blueF();
    if (color.isValid()) {
        ui->openGLWidget->s21_color_background_input(confData.redB, confData.greenB, confData.blueB);
        ui->openGLWidget->s21_updateGL();
    }
}

void MainWindow::on_vertices_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color");
    confData.redP = color.redF();
    confData.greenP = color.greenF();
    confData.blueP = color.blueF();
    if (color.isValid()) {
        ui->openGLWidget->s21_color_point_input(confData.redP, confData.greenP, confData.blueP);
        ui->openGLWidget->s21_updateGL();
    }
}

void MainWindow::on_moving_value_x_valueChanged(double arg1)
{
    _moveChange_x = arg1;
}

void MainWindow::on_moving_value_y_valueChanged(double arg1)
{
    _moveChange_y = arg1;
}

void MainWindow::on_moving_value_z_valueChanged(double arg1)
{
    _moveChange_z = arg1;
}

void MainWindow::on_rotation_angle_x_valueChanged(double arg1)
{
    _rotateChange_x = arg1;
}

void MainWindow::on_rotation_angle_y_valueChanged(double arg1)
{
    _rotateChange_y = arg1;
}

void MainWindow::on_rotation_angle_z_valueChanged(double arg1)
{
    _rotateChange_z = arg1;
}

void MainWindow::on_scale_per_valueChanged(int arg1)
{
    _zoom_per = arg1;
}

void MainWindow::on_scale_dec_clicked()
{

    if (confData.isOrtho) {
        zoom_per = 100 - _zoom_per;
        scaleZoom = (double)zoom_per/100;
        s21_scale(&dataFromFile, scaleZoom);
        get_vertex_array_from_data(&dataFromFile, new_arr);
        ui->openGLWidget->scale_x(scaleZoom);
        ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
    } else {
        zoom_per = _zoom_per;
        if (scaleZoom > 0)
            scaleZoom -= (double)zoom_per/1000;
        ui->openGLWidget->scale_x(scaleZoom);
    }
}


void MainWindow::on_scale_inc_clicked()
{

    if (confData.isOrtho) {
        zoom_per = 100 + _zoom_per;
        scaleZoom = (double)zoom_per/100;
        s21_scale(&dataFromFile, scaleZoom);
        get_vertex_array_from_data(&dataFromFile, new_arr);
        ui->openGLWidget->scale_x(scaleZoom);
        ui->openGLWidget->s21_draw_2(new_arr, dataFromFile.numbers_of_vertexes_in_all_facets);
    } else {
        zoom_per = _zoom_per;
        // if (scaleZoom <= 1)
            scaleZoom += (double)zoom_per/1000;
        ui->openGLWidget->scale_x(scaleZoom);
    }
}


void MainWindow::on_projection_type_activated(int index)
{
    if (index)
        confData.isOrtho = false;
    else
        confData.isOrtho = true;

    ui->openGLWidget->s21_draw(confData.isWire, confData.isOrtho);
    ui->openGLWidget->s21_updateGL();
}


void MainWindow::on_edges_type_activated(int index)
{
    if (index)
        confData.isWire = false;
    else
        confData.isWire = true;
    ui->openGLWidget->s21_draw(confData.isWire, confData.isOrtho);
    ui->openGLWidget->s21_updateGL();
}



void MainWindow::on_edges_thickness_sliderMoved(int position)
{
    confData.widthLine = (float)position/10;
    ui->openGLWidget->s21_width_input(confData.widthLine, confData.widthPoint);
    ui->openGLWidget->s21_updateGL();
}


void MainWindow::on_verticalSlider_3_sliderMoved(int position)
{
    confData.red = (float)position/100;
    ui->openGLWidget->s21_color_input(confData.red, confData.green, confData.blue);
    ui->openGLWidget->s21_updateGL();
}


void MainWindow::on_verticalSlider_2_sliderMoved(int position)
{
    confData.green = (float)position/100;
    ui->openGLWidget->s21_color_input(confData.red, confData.green, confData.blue);
    ui->openGLWidget->s21_updateGL();
}


void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    confData.blue = (float)position/100;
    ui->openGLWidget->s21_color_input(confData.red, confData.green, confData.blue);
    ui->openGLWidget->s21_updateGL();
}


void MainWindow::on_vertices_thickness_sliderMoved(int position)
{
    confData.widthPoint = (float)position/10;
    ui->openGLWidget->s21_width_input(confData.widthLine, confData.widthPoint);
    ui->openGLWidget->s21_updateGL();
}


void MainWindow::on_vertices_type_activated(int index)
{
    if (index == 0) {
        confData.isNoPoint = true;
        confData.isCircle = false;
    } else if (index == 1) {
        confData.isNoPoint = false;
        confData.isCircle = true;
    } else if (index == 2) {
        confData.isNoPoint = false;
        confData.isCircle = false;
    }
    ui->openGLWidget->s21_point_type_input(confData.isNoPoint, confData.isCircle);
    ui->openGLWidget->s21_updateGL();
}
