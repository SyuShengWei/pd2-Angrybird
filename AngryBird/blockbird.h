#ifndef BLOCKBIRD_H
#define BLOCKBIRD_H


#include "bird.h"

class BlockBird : public Bird
{
public:
    BlockBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    int virtual birdAbility();
};

#endif // BLOCKBIRD_H
