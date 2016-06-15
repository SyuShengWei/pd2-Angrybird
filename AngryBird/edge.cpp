#include "edge.h"

Edge::Edge(float x ,float y,b2Vec2 b2vec1,b2Vec2 b2vec2, b2World *world ) : GameItem(world)
{
    setHP(9999999);
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);

    b2EdgeShape edgeShape;
    edgeShape.Set(b2vec1,b2vec2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &edgeShape;
    g_body->CreateFixture(&fixtureDef);

    paint();
}
