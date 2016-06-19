#ifndef YELLOWBIRD_H
#define YELLOWBIRD_H

#include "bird.h"

class YellowBird : public Bird
{
public:
    YellowBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual int birdAbility();
};

#endif // YELLOWBIRD_H
