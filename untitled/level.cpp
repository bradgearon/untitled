#include "level.h"
#include <QDebug>

Level::Level(QObject *parent) : QObject(parent) {

}

Level::Level(QJsonObject level) : Level() {
    setRank(level["rank"].toInt(0));
    QJsonArray elements = level["elements"].toArray();

    auto length = static_cast<u_int>(elements.count());
    this->elements = std::vector<QString>(length);

    for(auto i = 0; i < elements.count(); i++) {
        this->elements[static_cast<u_int>(i)] = elements[i].toString();
    }

}

int32_t Level::getRank()
{
    return this->rank;
}

void Level::setRank(int32_t rank)
{
    this->rank = rank;
}

void Level::setElements(std::vector<QString> elements)
{
    this->elements = elements;
}

std::vector<QString> Level::getElements()
{
    return this->elements;
}
