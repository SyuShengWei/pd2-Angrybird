#include "yellowbird.h"


YellowBird::YellowBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
    //change bird Type
    setBirdType(2);
    setHP(100);
}


int YellowBird::birdAbility()
{
    //bird ability
    std::cout<<"Ability"<<std::endl;
    this->getBody().SetLinearVelocity(b2Vec2(this->getBody().GetLinearVelocity().x * 2,this->getBody().GetLinearVelocity().y * 2));

    //new bird
    return 0 ;
}
