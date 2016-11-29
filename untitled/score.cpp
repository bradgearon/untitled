#include "score.h"

Score::Score()
{

}

QString Score::getName() const
{
    return name;
}

void Score::setName(const QString &value)
{
    name = value;
}

double Score::getRank() const
{
    return rank;
}

void Score::setRank(double value)
{
    rank = value;
}

double Score::getWeight() const
{
    return weight;
}

void Score::setWeight(double value)
{
    weight = value;
}

Level *Score::getLevel() const
{
    return level;
}

void Score::setLevel(Level *value)
{
    level = value;
}

double Score::getValue() const
{
    return value;
}

void Score::setValue(double value)
{
    this->value = value;
    onValueUpdated(value);
}
