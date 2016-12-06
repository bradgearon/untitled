#pragma once
#include "models.h"

namespace untitled {

class LevelPicker {
protected:
  std::vector<std::unique_ptr<Level>> levels;
  std::map<QString, Score *> scoreMap;
  std::vector<Score *> scores;

private:
  std::default_random_engine gen;
  std::piecewise_constant_distribution<> random;
  QMetaObject::Connection pickedConnection;

  bool rebuild = true;

  void setLevelsAndScores(QJsonArray json);
  void rebuildRandom();

public:
  LevelPicker(QJsonArray levels);
  void setRead(QString element, double read);
  Score *pick();
  Score *getScore(QString element);
  std::map<QString, Score *> getScoreMap() const;
  void setReset();
};
}
