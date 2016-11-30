#pragma once
#include "models.h"

namespace untitled {
class Score;

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QObject *parent = 0);
    Level(QJsonObject level, double nextRank = 0);

    double getRank();
    double getReadTotal();
    std::vector<Score *> getScores();

private:
    double rank = 0;
    double percentComplete = 0;

    std::vector<Score *> scores;

    void setRank(double rank);
    void setScores(std::vector<Score *> scores);

signals:

public slots:


};
}
