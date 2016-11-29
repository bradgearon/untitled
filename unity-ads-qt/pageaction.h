#ifndef PAGEACTION_H
#define PAGEACTION_H

#include <QObject>

class PageAction : public QObject
{
    Q_OBJECT
public:
    explicit PageAction(QObject *parent = 0);

signals:

public slots:
    void read();
    void close();
    void loaded();
};

#endif // PAGEACTION_H
