#include "score.h"

Score::Score(Level *level) : QObject() {
  qDebug() << "creating score";
  this->level = level;
  connect(this, &Score::readChanged, &Score::onReadChanged);
}

QString Score::getName() const { return name; }

void Score::setName(const QString &value) { name = value; }

double Score::getRank() const { return rank; }

void Score::setRank(double value) { rank = value; }

double Score::getWeight() const { return weight; }

void Score::setWeight(double value) { weight = value; }

double Score::getRead() const { return read; }

void Score::setRead(double read) {
  this->read = read;
  emit readChanged(read);
}

double Score::getNextDifference() const { return nextDifference; }

void Score::setNextDifference(double value) { nextDifference = value; }

void Score::onReadChanged(double read) {
  double readTotal = level->getReadTotal();
  auto count = level->getScores().size();
  auto percentComplete = readTotal / count;

  auto subtractFromWeight = read * getNextDifference();
  auto addToWeight = read * percentComplete;

  qDebug() << " " << read << " " << percentComplete << " " << addToWeight << " "
           << subtractFromWeight << " " << readTotal << " a "
           << getNextDifference();

  setWeight(getRank() + addToWeight - subtractFromWeight);

  qDebug() << "weight for element " << getName() << " now " << getWeight()
           << " in rank " << getRank() << " read " << readTotal
           << " percent complete: " << percentComplete;
}
