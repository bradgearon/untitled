
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
    if(scoreMap.count(element) < 1) {
        return;
    }

    scoreMap[element]->setRead(read);
    rebuild = true;
}

Score* LevelPicker::getScore(QString element)
{
    return this->scoreMap[element];
}

void LevelPicker::rebuildRandom() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen = std::default_random_engine(seed);

    std::vector<double> intervals(this->scoreMap.size());
    std::iota(intervals.begin(), intervals.end(), 0);

    for(auto interval: intervals) {
        qDebug() << " interval " << interval;
    }

    std::vector<double> weights(this->scoreMap.size());
    scores = std::vector<Score *>(this->scoreMap.size());

    size_t i = 0;
    for(auto score: this->scoreMap) {
        scores[i++] = score.second;
    }

    std::sort(scores.begin(), scores.end(), [](Score * first, Score * second) {
        return first->getWeight() > second->getWeight();
    });

    i = 0;
    for(auto score: scores) {
        qDebug() << " score " << i << " " << score->getName() << " weight " << score->getWeight();
        weights[i++] = score->getWeight();
    }

    random = std::piecewise_constant_distribution<>(
                intervals.begin(), intervals.end(), weights.begin());
}


Score* LevelPicker::pick() {
    if(rebuild) {
        rebuildRandom();
        rebuild = false;
    }

    double picked = random(gen);
    qDebug() << " picked " << picked;
    return scores[static_cast<size_t>(picked)];
}

