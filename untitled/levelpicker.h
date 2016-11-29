#ifndef LEVELPICKER_H
#define LEVELPICKER_H

#include <QJSValue>
#include "level.h"
#include "score.h"

class LevelPicker
{
private:
    std::vector<Level *> levels;
    std::map<QString, Score *> levelMap;

public:
    LevelPicker (QJsonArray levels);
    std::vector<Level *> getLevels();

    void updateLevels();
    void updateLevelsAndScores(QJsonArray json);
};

#endif // LEVELPICKER_H
