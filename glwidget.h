#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>

class Figure;

class QShortcut;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    QSize sizeHint() const;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void updateGL();

private:
    QShortcut *esc;
    QShortcut *altEnter;
    QList<Figure*> scene;
    QList<Figure*>::iterator it;

signals:

public slots:
    void toFullScreen();
};

#endif // GLWIDGET_H
