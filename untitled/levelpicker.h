#ifndef LEVELPICKER_H
#define LEVELPICKER_H

#include <QJSValue>
#include "level.h"

class LevelPicker
{
private:
    std::vector<Level*> levels;

public:
    LevelPicker (QJsonArray levels);
    std::vector<Level *> getLevels();
};

#endif // LEVELPICKER_H
