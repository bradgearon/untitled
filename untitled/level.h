#pragma once

#include "models.h"

namespace untitled {

class Level : public QObject {
  Q_OBJECT
public:
  explicit Level(QObject *parent = 0);
  Level(QJsonObject level, double nextRank = 0);

  double getRank();
  double getReadTotal();
  const std::vector<std::unique_ptr<Score>> &getScores();

private:
  double rank = 0;
  double percentComplete = 0;

  std::vector<std::unique_ptr<Score>> scores;

  void setRank(double rank);

signals:

public slots:
};
}
