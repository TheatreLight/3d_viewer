#include "gl_view.h"

#include <QDebug>

gl_view::gl_view(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void gl_view::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

void gl_view::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

}

void gl_view::paintGL()
{
    glClearColor(redB, greenB, blueB, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLineWidth(widthLine);
    glPointSize(widthPoint);

    if (!isOrtho) {

        glScaled(scaleZoom, scaleZoom, scaleZoom);
        glFrustum(-1, 1, -1.2, 1.2, 1, 20);
        glTranslatef(0, 0, -6);
    }
    else {

        glOrtho(-1, 1, -1.2, 1.2, 1, 20);
        glTranslatef(0, 0, -5);
        glScalef(0.25, 0.25, 0.25);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    if (new_arr != NULL) {
        glVertexPointer(3, GL_DOUBLE, 0, new_arr);
        if (isWire) {
            if (!isNoPoint) {
                glColor3f(redP, greenP, blueP);
                if (isCircle) {
                    glEnable(GL_POINT_SMOOTH);
                } else {
                    glDisable(GL_POINT_SMOOTH);
                }
                glDrawArrays(GL_POINTS, 0, count);
            }
            glColor3f(red, green, blue);
            glDrawArrays(GL_LINES_ADJACENCY, 0, count);
            glDrawArrays(GL_LINES, 0, count);
        } else {
            if (!isNoPoint) {
                glColor3f(redP, greenP, blueP);
                if (isCircle) {
                    glEnable(GL_POINT_SMOOTH);
                } else {
                    glDisable(GL_POINT_SMOOTH);
                }
                glDrawArrays(GL_POINTS, 0, count);
            }
            glColor3f(red, green, blue);
            glLineStipple(4, 0xAAAA);
            glEnable(GL_LINE_STIPPLE);
            glDrawArrays(GL_LINES, 0, count);
            glDisable(GL_LINE_STIPPLE);
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void gl_view::s21_draw(bool isWire, bool isOrtho)
{
    this->isOrtho = isOrtho;
    this->isWire = isWire;
}

void gl_view::s21_draw_2(double *new_arr, int count)
{
    this->new_arr = new_arr;
    this->count = count;
    update();
}

void gl_view::scale_x(double scale)
{
//    this->isOrtho = isOrtho;
    this->scaleZoom = scale;
    if (!isOrtho)
        update();
}

void gl_view::s21_color_input(float red, float green, float blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void gl_view::s21_color_point_input(float redP, float greenP, float blueP)
{
    this->redP = redP;
    this->greenP = greenP;
    this->blueP = blueP;
}

void gl_view::s21_color_background_input(float redB, float greenB, float blueB)
{
    this->redB = redB;
    this->greenB = greenB;
    this->blueB = blueB;
}

void gl_view::s21_width_input(float widthLine, float widthPoint)
{
    this->widthLine = widthLine;
    this->widthPoint = widthPoint;
}

void gl_view::s21_updateGL()
{
    update();
}

void gl_view::s21_point_type_input(bool isNoPoint, bool isCircle)
{
    this->isNoPoint = isNoPoint;
    this->isCircle = isCircle;
}
