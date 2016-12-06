#pragma once

#include "levelpicker.h"

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
