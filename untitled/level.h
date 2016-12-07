#pragma once

#include "models.h"

namespace untitled {

class Level : public QObject {
  Q_OBJECT
  Q_PROPERTY(double rank READ getRank WRITE setRank)
  Q_PROPERTY(double readTotal READ getReadTotal)

public:
  explicit Level(QObject *parent = 0);

  double getRank();
  double getReadTotal();
  std::vector<std::unique_ptr<Score>> &getScores();

private:
  double rank = 0;
  double percentComplete = 0;

  std::vector<std::unique_ptr<Score>> scores;

  void setRank(double rank);

signals:

public slots:
};
}
