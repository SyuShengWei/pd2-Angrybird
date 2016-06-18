#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    //set Type
    birdType = 0;
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius*2;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetGravityScale(0);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
    //
    setTtemType(2);

    killTimer = new QTimer();
    connect(killTimer,SIGNAL(timeout()),this,SLOT(killUseless()));
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

int Bird::birdAbility()
{
    //bird ability
    //std::cout<<"Ability"<<std::endl;
    killTimer->start(6000);

    //new bird
    return 0 ;
}

int Bird::getBirdType() const
{
    return birdType;
}

void Bird::setBirdType(int i)
{
    birdType = i ;
}

