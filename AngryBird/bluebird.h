#ifndef BLUEBIRD_H
#define BLUEBIRD_H

#include "bird.h"

class BlueBird : public Bird
{
public:
    BlueBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    int virtual birdAbility();
};
#endif // BLUEBIRD_H
