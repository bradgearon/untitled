#pragma once

#include <chrono>
#include <memory>

#include <QDataStream>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QSaveFile>
#include <QtSql>

namespace untitled {
class Level;
class Score;
}

#include "level.h"
#include "score.h"

#include "book.h"
#include "levelpicker.h"

using namespace untitled;
