#include "pig.h"

#include <iostream>

Pig::Pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : GameItem(world)
{
    setHP(200);
    //set g_pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);
    //create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = this;
    bodyDef.bullet = true;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2CircleShape PigbodyShape;
    PigbodyShape.m_radius = radius*2;
    //create fixture
    b2FixtureDef pigFixtureDef;
    pigFixtureDef.density = PIG_DENSITY;
    pigFixtureDef.friction= PIG_FRICTION;
    pigFixtureDef.restitution=PIG_RESTITUTION;
    pigFixtureDef.shape = &PigbodyShape;

    g_body->SetGravityScale(1);

    g_body->CreateFixture(&pigFixtureDef);
    g_body->SetAngularDamping(3);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

