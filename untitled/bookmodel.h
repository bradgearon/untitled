#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QObject>

class BookModel : public QObject {
  Q_OBJECT
public:
  explicit BookModel(QObject *parent = 0);

signals:

public slots:
};

#endif // BOOKMODEL_H
