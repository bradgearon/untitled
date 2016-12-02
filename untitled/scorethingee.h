#ifndef SCORETHINGEE_H
#define SCORETHINGEE_H
#include "models.h"

namespace untitled {

class ScoreThingee {

private:
  std::unique_ptr<QSaveFile> saveFile;
  QJsonObject getCookieValue();
  LevelPicker *picker;

  void readSave();
  void readCookie();

public:
  ScoreThingee(LevelPicker *picker);
  void saveScores();
  void readScores();
};
}
#endif // SCORETHINGEE_H
