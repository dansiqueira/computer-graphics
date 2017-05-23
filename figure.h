#ifndef FIGURE_H
#define FIGURE_H

#include <QVector>
#include <QVector3D>

class Figure
{
protected:
    QVector<QVector3D> vertices;
public:
    Figure();
    virtual void draw() const;
};

#endif // FIGURE_H
