#pragma once

#include "models.h"
namespace untitled {

class Book : QObject {
  Q_OBJECT
public:
  explicit Book(QObject *parent = 0);

  QString getName() const;
  void setName(const QString &value);

  QString getOrder() const;
  void setOrder(const QString &value);

  QString getAbbr() const;
  void setAbbr(const QString &value);

  uchar getIndex() const;
  void setIndex(const uchar &value);

private:
  uchar index;
  QString order;
  QString name;
  QString abbr;
};
}
