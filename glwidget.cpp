#include "glwidget.h"
#include "square.h"
#include<QShortcut>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer), parent)
{
    // Cria-se 4 vetores de floats que servirão como vértices do quadrado
    // Essa parte tem qeu ser movida para a engine do jogo
    double v1[3] = {-50.0, -50.0, 0.0};
    double v2[3] = { 50.0, -50.0, 0.0};
    double v3[3] = { 50.0,  50.0, 0.0};
    double v4[3] = {-50.0,  50.0, 0.0};
    // Adiciona um quadrado à cena (Polimorfismo)
    this->scene.append(new Square(v1, v2, v3, v4));


    // Configura a janela
    this->setMinimumSize(500, 500); // tamanho mínimo
    const QRect screen = QApplication::desktop()->screenGeometry(); // Qual o tamanho do desktop?
    this->move(screen.center() - this->rect().center()); // move a janela para o centro do desktop

    // Configurando atalhos
    this->esc = new QShortcut(Qt::Key_Escape, this); // tecla de escape (para sair do modo FULL SCREEN
    this->altEnter = new QShortcut(Qt::Key_F11, this); // para alternar o modo normal e FULL SCREEN

    // Faz as conexões necessárias com os SLOTS da classe
    connect(this->esc,SIGNAL(activated()), this, SLOT(showNormal()));
    connect(this->altEnter,SIGNAL(activated()), this, SLOT(toFullScreen()));
}

GLWidget::~GLWidget()
{
}

// Determina o tamano da janela, quando é mostrada em modo Normal
QSize GLWidget::sizeHint() const
{
    return QSize(500, 500);
}

// Configura a OpenGL
void GLWidget::initializeGL()
{
    glEnable(GL_DOUBLEBUFFER);
    glEnable(GL_DEPTH_TEST);

    // Cor de fundo
    glClearColor(0.0,0.0,0.0,1.0);

    // Determina o quanto da GLWidget será utilizada (para o total)
    glViewport(0,0,this->width(),this->height());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Mantém a proporção
    glOrtho(-this->width()/2,this->width()/2,-this->height()/2,this->height()/2, 10, -10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Desenha a cena na tela
void GLWidget::paintGL()
{
    // Limpa os buffers de cor e profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Percorre a cena, desenhando cada figura que houver nela
    for(this->it = this->scene.begin(); this->it != this->scene.end(); ++it)
        (*it)->draw();
}

// Atualiza as configurações da OpenGL sempre que necessário
void GLWidget::updateGL()
{
    glViewport(0,0,this->width(),this->height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Mantém a proporção
    glOrtho(-this->width()/2,this->width()/2,-this->height()/2,this->height()/2, 10, -10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Requisita uma atualização da GLWidget caso a janela seja redimensionada
void GLWidget::resizeGL(int w, int h)
{
    qDebug() <<"RES: " << w << " x " << h ;
    this->updateGL();
}


// Alterna os modos tela cheia e normal
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
