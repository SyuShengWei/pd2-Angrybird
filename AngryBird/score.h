#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QFont>

class Score : public QGraphicsTextItem
{
public:
    Score();

    void increaseScore(int i);
    int  getScore();
    void setScore(int i);
    void setBirdLeft(int i );
    int getBirdLeft();
private:
    int score;
    int birdLeft;
};


#endif // SCORE_H
