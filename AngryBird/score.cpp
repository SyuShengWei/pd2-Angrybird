#include "score.h"

Score::Score()
{
    score = 0 ;
    birdLeft = 0;
}

void Score::increaseScore(int i)
{
    score = score + i;

    setPlainText("Score = " + QString::number(score) + "\n" + "Bird Left = " + QString::number(birdLeft));
    setDefaultTextColor(Qt::red);
    setFont(QFont("timer",16));
}

int Score::getScore()
{
    return score;
}

void Score::setScore(int i)
{
    score = i ;
}

void Score::setBirdLeft(int i)
{
    birdLeft = i;
}

int Score::getBirdLeft()
{
    return birdLeft;
}


