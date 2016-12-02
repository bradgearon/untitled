#include "level.h"

Level::Level(QObject *parent) : QObject(parent) {}

Level::Level(QJsonObject level, double nextRank) : Level() {
  qDebug() << "creating level";
  setRank(level["rank"].toDouble(0));

  double nextDifference = getRank() - nextRank;

  QJsonArray elements = level["elements"].toArray();
  auto length = static_cast<size_t>(elements.count());
  this->scores = std::vector<std::unique_ptr<Score>>(length);

  size_t i = 0;
  for (auto element : elements) {
    auto score = std::make_unique<Score>(this);

    // todo: connect Score::onValueUpdated to updateWhateverItis
    score->setName(element.toString());
    score->setRank(getRank());
    score->setWeight(getRank());
    score->setNextDifference(nextDifference);

    scores[i] = std::move(score);
    i++;
  }
}

double Level::getRank() { return this->rank; }

void Level::setRank(double rank) { this->rank = rank; }

const std::vector<std::unique_ptr<Score>> &Level::getScores() {
  return this->scores;
}

double Level::getReadTotal() {
  return std::accumulate(
      scores.begin(), scores.end(), 0,
      [](double sum, auto &&score) { return sum + score->getRead(); });
}
