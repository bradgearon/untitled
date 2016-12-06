#pragma once

#include "models.h"

namespace untitled {
class Element {
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
