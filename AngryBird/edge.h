#ifndef EDGE_H
#define EDGE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Edge : public GameItem
{
public:
    Edge(float x ,float y,b2Vec2 b2vec1,b2Vec2 b2vec2 , b2World *world);
};

#endif // EDGE_H
