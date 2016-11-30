#pragma once
#include "models.h"

namespace untitled {
class LevelPicker
{
private:
    std::vector<Level *> levels;
    std::map<QString, Score *> scoreMap;
    void setLevelsAndScores(QJsonArray json);

public:
    LevelPicker (QJsonArray levels);
    void setRead(QString element, double read);
    QString pick();
    Score* getScore(QString element);


};
}
