#include "blockbird.h"

BlockBird::BlockBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
    //change bird Type
    setBirdType(3);
    setHP(500);
}

int BlockBird::birdAbility()
{
    //bird ability
    //std::cout<<"Ability"<<std::endl;
    return 3;
    //new bird
}
