#include <QDebug>
#include "models.h"

LevelPicker::LevelPicker(QJsonArray json)
{
    size_t count = static_cast<size_t>(json.count());
    this->levels = std::vector<Level *>(count);
    this->scoreMap = std::map<QString, Score *>();

    setLevelsAndScores(json);
}

void LevelPicker::setLevelsAndScores(QJsonArray json) {
    size_t count = static_cast<size_t>(this->levels.size());

    for (size_t i = 0; i < count; i++) {
        int ii = static_cast<int>(i);

        // this does 10.1 for rank 15 when 1
        // double nextRank = i + 1 < count ?
            //        json[ii + 1].toObject()["rank"].toDouble() :
               //     0;

        // this does 5.1 for rank 15 when 1
        double nextRank =  0;
        this->levels[i] = new Level(json[ii].toObject(), nextRank);

        for(auto score: this->levels[i]->getScores()) {
            if(this->scoreMap[score->getName()] == NULL) {
                this->scoreMap[score->getName()] = score;
            }
        }
    }
}


void LevelPicker::setRead(QString element, double read)
{
    this->scoreMap[element]->setRead(read);
}

Score* LevelPicker::getScore(QString element)
{
    return this->scoreMap[element];
}

QString LevelPicker::pick() {



}

