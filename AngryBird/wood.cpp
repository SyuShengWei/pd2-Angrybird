#include "wood.h"

Wood::Wood(float x, float y, float w,float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene): GameItem(world)
{
    setHP(500) ;
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height());
    g_size = QSize(w,h/1.5);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);

    //set shape
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = WOOD_DENSITY;
    fixturedef.friction = WOOD_FRICTION;
    fixturedef.restitution = WOOD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
    //
    setTtemType(3);
}
