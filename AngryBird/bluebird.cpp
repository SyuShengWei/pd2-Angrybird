#include "bluebird.h"

BlueBird::BlueBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
    //change bird Type
    setBirdType(3);
    setHP(100);
}

int BlueBird::birdAbility()
{
    //bird ability
    killTimer->start(3000);
    //std::cout<<"Ability"<<std::endl;
    return 2;
    //new bird
}
