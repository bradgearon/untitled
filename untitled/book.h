#pragma once

#include "models.h"
namespace untitled {

class Book : public QObject {
  Q_OBJECT
  Q_PROPERTY(uchar index READ getIndex WRITE setIndex)
  Q_PROPERTY(QString ord READ getOrder WRITE setOrder)
  Q_PROPERTY(QString name READ getName WRITE setName)
  Q_PROPERTY(QString abbr READ getAbbr WRITE setAbbr)

public:
  explicit Book(QObject *parent = 0);

  QString getName() const;
  void setName(const QString &value);

  QString getOrder() const;
  void setOrder(const QString &value);

  QString getAbbr() const;
  void setAbbr(const QString &value);

  size_t getIndex() const;
  void setIndex(size_t value);

private:
  size_t index = 0;
  QString order;
  QString name;
  QString abbr;
};
}
