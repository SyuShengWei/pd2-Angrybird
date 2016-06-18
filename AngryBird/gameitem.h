#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    virtual ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);

    b2Body & getBody();
    QGraphicsPixmapItem & getPixmap();
    void kill(float hit);

    float getHP();
    void setHP(float theHP);

    int  getItemType();
    void setTtemType(int i);

    int ifHit;//0=n,1=y

private:
    float HP;
    int itemType; // Pig = 1 , Bird = 2 , Wood = 3

public slots:
    void paint();
    // TODO virtual void collide();
    void killUseless();

protected:
    b2Body *g_body;
    QGraphicsPixmapItem g_pixmap;
    QSizeF g_size;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;
};

#endif // GAMEITEM_H
