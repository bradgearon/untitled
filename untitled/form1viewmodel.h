#pragma once

#include "models.h"
namespace untitled {

class Form1ViewModel : public QObject {
  Q_OBJECT

  Q_PROPERTY(bool isRtl READ getIsRtl WRITE setIsRtl)
  Q_PROPERTY(QString imageName READ getImageName WRITE setImageName)
  Q_PROPERTY(QString verse READ getVerse WRITE setVerse)
  Q_PROPERTY(QString title READ getTitle WRITE setTitle)
  Q_PROPERTY(QString more READ getMore WRITE setMore)

private:
  Score *score;

  bool isRtl;
  QString imageName;
  QString title;
  QString verse;
  QString more;

public:
  explicit Form1ViewModel(QObject *parent = 0);
  Form1ViewModel(QJsonObject viewModel);

  bool getIsRtl() const;
  void setIsRtl(bool value);

  QString getImageName() const;
  void setImageName(const QString &value);

  QString getVerse() const;
  void setVerse(const QString &value);

  QString getTitle() const;
  void setTitle(const QString &value);

  void setScore(Score *value);

  // controller observes things on here
  // when value is updated
  // controller updates it

  // how does a score get updated?
  // does this have reference to a score? yes

  QString getMore() const;
  void setMore(const QString &value);

signals:
  void close();
  void learnMore();
  void read(double value);
  void ready();

public slots:
  void onRead(double value);
  void onLearnMore();
  void onClose();
  void onReady();
};
}
