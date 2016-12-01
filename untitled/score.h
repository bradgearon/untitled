#pragma once
#include "models.h"

namespace untitled {
class Level;

class Score : public QObject {
  Q_OBJECT
public:
  explicit Score(QObject *parent = 0);

  QString getName() const;
  void setName(const QString &value);

  double getRank() const;
  void setRank(double value);

  double getWeight() const;
  void setWeight(double value);

  Level *getLevel() const;
  void setLevel(Level *value);

  double getRead() const;
  void setRead(double read);

  double getNextDifference() const;
  void setNextDifference(double value);

public slots:
  void onReadChanged(double read);

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
