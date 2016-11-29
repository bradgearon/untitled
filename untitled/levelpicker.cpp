#include <QDebug>
#include "levelpicker.h"

LevelPicker::LevelPicker(QJsonArray json)
{
    u_int count = static_cast<u_int>(json.count());
    this->levels = std::vector<Level*>(count);
    for (u_int i = 0; i < count; i++) {
        Level* level = new Level(json[static_cast<int>(i)].toObject());
        this->levels[i] = level;
    }
}

std::vector<Level *> LevelPicker::getLevels()
{
    return this->levels;
}

