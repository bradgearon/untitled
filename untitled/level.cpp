#include "models.h"
#include <QDebug>

Level::Level(QObject *parent) : QObject(parent) {}

Level::Level(QJsonObject level, double nextRank) : Level() {
  setRank(level["rank"].toDouble(0));

  double nextDifference = getRank() - nextRank;

  QJsonArray elements = level["elements"].toArray();
  auto length = static_cast<size_t>(elements.count());
  this->scores = std::vector<Score *>(length);

  size_t i = 0;
  for (auto element : elements) {
    Score *score = new Score();

    // todo: connect Score::onValueUpdated to updateWhateverItis
    score->setName(element.toString());
    score->setRank(getRank());
    score->setWeight(getRank());
    score->setLevel(this);
    score->setNextDifference(nextDifference);

    scores[i] = score;
    i++;
  }
}

double Level::getRank() { return this->rank; }

void Level::setRank(double rank) { this->rank = rank; }

void Level::setScores(std::vector<Score *> scores) { this->scores = scores; }

std::vector<Score *> Level::getScores() { return this->scores; }

double Level::getReadTotal() {
  return std::accumulate(
      scores.begin(), scores.end(), 0,
      [](double sum, Score *score) { return sum + score->getRead(); });
}
