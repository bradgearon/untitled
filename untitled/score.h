#pragma once
#include "models.h"

namespace untitled {

class Score : public QObject {
  Q_OBJECT
  Q_PROPERTY(double rank READ getRank WRITE setRank)
  Q_PROPERTY(double weight READ getWeight WRITE setWeight)
  Q_PROPERTY(double read READ getRead WRITE setRead)
  Q_PROPERTY(
      double nextDifference READ getNextDifference WRITE setNextDifference)

public:
  explicit Score(QObject *parent = 0);
  Score(Level *level);

  QString getName() const;
  void setName(const QString &value);

  double getRank() const;
  void setRank(double value);

  double getWeight() const;
  void setWeight(double value);

  double getRead() const;
  void setRead(double read);

  double getNextDifference() const;
  void setNextDifference(double value);

public slots:
  void onReadChanged(double read, double previous = 0);

signals:
  void readChanged(double read);

private:
  double rank = 0;
  double weight = 0;
  double read = 0;
  double nextDifference = 0;

  QString name;

  Level *level;
};
}
