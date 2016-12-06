#pragma once

namespace untitled {
class Level;
class Score;
}

#include <QDebug>

#include <QDesktopServices>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QWindow>
#include <QtCore>

#include <QDataStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QSaveFile>
#include <QtSql>

#include <chrono>
#include <functional>
#include <future>
#include <memory>

#include "level.h"
#include "score.h"

#include "book.h"
#include "levelpicker.h"
