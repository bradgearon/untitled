#pragma once

#include "models.h"
namespace untitled {

class Form1ViewModel : public QObject {
  Q_OBJECT

  Q_PROPERTY(bool isRtl READ getIsRtl)
  Q_PROPERTY(QString imageName READ getImageName)
  Q_PROPERTY(QString verse READ getVerse)
  Q_PROPERTY(QString title READ getTitle)
  Q_PROPERTY(QString more READ getMore)

private:
  Score *score;
  Element *element;
  Config *config;

public:
  explicit Form1ViewModel(QObject *parent = 0);
  Form1ViewModel(Score *score, Config *config, Element *element);

  bool getIsRtl() const;
  QString getImageName() const;
  QString getVerse() const;
  QString getTitle() const;
  QString getMore() const;

  void setConfig(Config *value);
  void setElement(Element *value);
  void setScore(Score *value);

signals:
  void show();
  void close();
  void learnMore();
  void read(double value);
  void ready();
};
}
