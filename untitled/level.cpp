#include "level.h"
using namespace untitled;

Level::Level(QObject *parent) : QObject(parent) {
  qDebug() << "creating level";
  this->scores = std::vector<std::unique_ptr<Score>>();
}

double Level::getRank() { return this->rank; }

void Level::setRank(double rank) { this->rank = rank; }

std::vector<std::unique_ptr<Score>> &Level::getScores() { return this->scores; }

double Level::getReadTotal() {
  double total = std::accumulate(scores.begin(), scores.end(), 0.0,
                                 [](double sum, auto &&score) {
                                   auto current = sum + score->getRead();
                                   return current;
                                 });
  qDebug() << " total read: " << total;
  return total;
}
