#include "square.h"
#include <QtOpenGL>

Square::Square(double *v1, double *v2, double *v3, double *v4)
{
    this->vertices << QVector3D(v1[0], v1[1], v1[2]) \
            << QVector3D(v2[0], v2[1], v2[2]) \
            << QVector3D(v3[0], v3[1], v3[2]) \
            << QVector3D(v4[0], v4[1], v4[2]);

}

void Square::draw() const
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex3d(this->vertices.at(0).x(), this->vertices.at(0).y(), this->vertices.at(0).z());
    glVertex3d(this->vertices.at(1).x(), this->vertices.at(1).y(), this->vertices.at(1).z());
    glVertex3d(this->vertices.at(2).x(), this->vertices.at(2).y(), this->vertices.at(2).z());
    glVertex3d(this->vertices.at(3).x(), this->vertices.at(3).y(), this->vertices.at(3).z());
    glEnd();
}
