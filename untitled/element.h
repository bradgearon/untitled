#pragma once

#include "models.h"

namespace untitled {
class Element : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString verse READ getVerse WRITE setVerse)
  Q_PROPERTY(QString title READ getTitle WRITE setTitle)
  Q_PROPERTY(QString imagePath READ getImagePath WRITE setImagePath)
  Q_PROPERTY(QString learnMorePath READ getLearnMorePath WRITE setLearnMorePath)

private:
  QString verse;
  QString title;
  QString imagePath;
  QString learnMorePath;

public:
  QString getVerse() const;
  void setVerse(const QString &value);
  QString getTitle() const;
  void setTitle(const QString &value);
  QString getImagePath() const;
  void setImagePath(const QString &value);
  QString getLearnMorePath() const;
  void setLearnMorePath(const QString &value);
};
}
