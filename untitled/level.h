#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QObject *parent = 0);
    Level(QJsonObject level);

    int32_t getRank();
    std::vector<QString> getElements();

private:
    int32_t rank;
    std::vector<QString> elements;

    void setRank(int32_t rank);
    void setElements(std::vector<QString> elements);

signals:

public slots:
};

#endif // LEVEL_H
