#ifndef SCORE_H
#define SCORE_H

#include "level.h"

#include <QObject>
#include <QString>

class Score : public QObject
{
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

    double getValue() const;
    void setValue(double value);

    double getNextDifference() const;
    void setNextDifference(double value);

private:
    QString name;
    double rank;
    double weight;
    double value;
    double nextDifference;
    Level *level;

signals:

public slots:
    void onValueUpdated(double value);
};


#endif // SCORE_H
