#ifndef WOOD_H
#define WOOD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define WOOD_DENSITY 110.0f
#define WOOD_FRICTION 0.5f
#define WOOD_RESTITUTION 0.2f


class Wood : public GameItem
{
public:
    Wood(float x, float y, float w,float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // WOOD_H
