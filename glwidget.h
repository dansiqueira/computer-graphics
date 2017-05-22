#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
//#include <QGLShaderProgram>

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
//    QMatrix4x4 pMatrix; // matriz de projeção
//    QGLShaderProgram shader;
//    QVector<QVector3D> vertices;
    QShortcut *esc;
    QShortcut *altEnter;

signals:

public slots:
    void toFullScreen();
};

#endif // GLWIDGET_H
