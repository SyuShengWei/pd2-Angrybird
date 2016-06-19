#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QSize>
#include <QPushButton>
#include <QBrush>
#include <QImage>
#include <math.h>
#include <QGraphicsPixmapItem>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <wood.h>
#include <pig.h>
#include <edge.h>
#include <yellowbird.h>
#include <bluebird.h>
#include <blockbird.h>
#include <score.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);

    void initialGame();
    void destoryTtem();
    void hit();


signals:
    // Signal for closing the game
    void quitGame();

private slots:
    //keep game slot
    void tick();
    // For debug slot
    void QUITSLOT();
    //timer slots
    void createBird();
    void hidePixmap();
    //buttom slots
    void restart();
    void exitGame();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QList<Bird *> birdList;
    QTimer *createTimer;
    QTimer *pixmapTimer;
    QGraphicsPixmapItem * explosion;
    QGraphicsPixmapItem * slingslot;
    QGraphicsPixmapItem *endGamePix;
    Score *score;

    int hold;
    float mousePress_X,mousePress_Y,mouseRelease_X,mouseRelease_Y;
    QMouseEvent * mouseEvent;
    float originalPos_X,originalPos_Y;
    int birdStep; // 0=next ,1=can hold,2=can move,3=can release,4=can us ability
    int birdAbility;//0=no ability ,1=can use ability,2=blue bird ability on,3=block bird on
    int whichBird;
    //bird left
    int birdLeft;
    int pigLeft;

    void checkLeft();
    void endGame(int signal);

};

#endif // MAINWINDOW_H
