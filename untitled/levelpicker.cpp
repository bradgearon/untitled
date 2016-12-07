#include "levelpicker.h"
using namespace untitled;

LevelPicker::LevelPicker(LoaderMoboberJigger loader) {
  levels = loader.loadLevels();
  scoreMap = std::map<QString, Score *>();
  setLevelsAndScores();
}

std::map<QString, Score *> LevelPicker::getScoreMap() const { return scoreMap; }

void LevelPicker::setReset() { rebuild = true; }

void LevelPicker::setLevelsAndScores() {
  for (auto &&level : levels) {
    for (auto &&score : level->getScores()) {
      if (scoreMap[score->getName()] == NULL) {
        scoreMap[score->getName()] = score.get();
      }
    }
  }
}

void LevelPicker::setRead(QString element, double read) {
  if (scoreMap.count(element) < 1) {
    return;
  }

  Score *thisScore = scoreMap[element];
  thisScore->setRead(read);
}

Score *LevelPicker::getScore(QString element) {
  return this->scoreMap[element];
}

void LevelPicker::rebuildRandom() {
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  gen = std::default_random_engine(seed);

  std::vector<double> intervals(this->scoreMap.size());
  std::iota(intervals.begin(), intervals.end(), 0);

  for (auto interval : intervals) {
    qDebug() << " interval " << interval;
  }

  std::vector<double> weights(this->scoreMap.size());
  scores = std::vector<Score *>(this->scoreMap.size());

  size_t i = 0;
  for (auto score : this->scoreMap) {
    scores[i++] = score.second;
  }

  std::sort(scores.begin(), scores.end(), [](Score *first, Score *second) {
    return first->getWeight() > second->getWeight();
  });

  i = 0;
  for (auto score : scores) {
    qDebug() << " score " << i << " " << score->getName() << " weight "
             << score->getWeight();
    weights[i++] = score->getWeight();
  }

  random = std::piecewise_constant_distribution<>(
      intervals.begin(), intervals.end(), weights.begin());
}

Score *LevelPicker::pick() {
  if (pickedConnection) {
    QObject::disconnect(pickedConnection);
  }

  if (rebuild) {
    rebuildRandom();
    rebuild = false;
  }

  double picked = random(gen);
  qDebug() << " picked " << picked;

  const auto score = scores[static_cast<size_t>(picked)];
  QObject::connect(score, &Score::readChanged, [this]() { this->setReset(); });

  return score;
}
