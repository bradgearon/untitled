#include <QDebug>
#include "levelpicker.h"
#include "score.h"

LevelPicker::LevelPicker(QJsonArray json)
{
    u_int count = static_cast<u_int>(json.count());
    this->levels = std::vector<Level *>(count);
    this->levelMap = std::map<QString, Score *>();

    updateLevelsAndScores(json);
}

void LevelPicker::updateLevelsAndScores(QJsonArray json) {
    u_int count = static_cast<u_int>(this->levels.size());

    for (u_int i = 0; i < count; i++) {
        Level* level;
        int ii = static_cast<int>(i);

        if(this->levels[i] == NULL) {
            level = this->levels[i];
        } else {
            level = new Level(json[ii].toObject());
            this->levels[i] = level;
        }

        double nextDiff = count > i + 1 ?
                    level->getRank() - json[ii + 1].toObject()["rank"].toInt() :
                    level->getRank() * .5;

        for(auto element: level->getElements()) {
            Score * levelScore;

            if(this->levelMap[element] == NULL) {
                levelScore = new Score();
                this->levelMap[element] = levelScore;
            } else {
                levelScore = this->levelMap[element];
            }

            // todo: connect Score::onValueUpdated to updateWhateverItis
            levelScore->setName(element);
            levelScore->setRank(level->getRank());
            levelScore->setWeight(level->getRank());
            levelScore->setLevel(level);
            levelScore->setNextDifference(nextDiff);

        }
    }
}


std::vector<Level *> LevelPicker::getLevels()
{
    return this->levels;
}

