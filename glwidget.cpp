#include "glwidget.h"
#include<QShortcut>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer), parent)
{
    this->setMinimumSize(500, 500);
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move(screen.center() - this->rect().center());

    this->esc = new QShortcut(Qt::Key_Escape, this);
    this->altEnter = new QShortcut(Qt::Key_F11, this);

    connect(this->esc,SIGNAL(activated()), this, SLOT(showNormal()));
    connect(this->altEnter,SIGNAL(activated()), this, SLOT(toFullScreen()));
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::sizeHint() const
{
    return QSize(500, 500);
}

void GLWidget::initializeGL()
{
    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0,0.0,0.0,1.0);
    glViewport(0,0,this->width(),this->height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-250,250,-250,250, 10, -10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glPointSize(5);
    glBegin(GL_POINT);
    glVertex2f(   0,    0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(-250, -250);
    glVertex2f( 250,  250);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(-250,  250);
    glVertex2f( 250, -250);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(-250,  0);
    glVertex2f( 250,  0);
    glColor3f(0.0,1.0,1.0);
    glVertex2f( 0,   -250);
    glVertex2f( 0,    250);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2i(-50,-50);
    glVertex2i( 50,-50);
    glVertex2i( 50, 50);
    glVertex2i(-50, 50);
    glEnd();
}

void GLWidget::updateGL()
{
    glViewport(0,0,this->width(),this->height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-250,250,-250,250, 10, -10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::resizeGL(int w, int h)
{
    qDebug() << w << " x " << h ;
    this->updateGL();
}

void GLWidget::toFullScreen()
{
    if (this->windowState() != Qt::WindowFullScreen)
        this->setWindowState(Qt::WindowFullScreen);
    else
    {
        const QRect screen = QApplication::desktop()->screenGeometry();
        this->move(screen.center() - this->rect().center());
        this->showNormal();
    }
}
