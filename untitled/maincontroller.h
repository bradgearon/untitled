#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "models.h"

#include "form1viewmodel.h"
#include "languagethingee.h"
#include "levelpicker.h"
#include "loadermoboberjigger.h"
#include "platformthingee.h"
#include "scorethingee.h"

#include "ganalytics.h"

#include <QQuickItem>
#include <QQuickWindow>

namespace untitled {

class MainController : public QObject {
  Q_OBJECT

private:
  bool isReady;
  QQuickItem *view;
  Config *config;
  Score *picked;
  Element *element;
  QVariant viewModelVariant;
  QMetaObject::Connection pickedConnection;
  QString isoLang;

  std::unique_ptr<PlatformThingee> platformThingee;
  std::unique_ptr<Form1ViewModel> viewModel;
  std::unique_ptr<LevelPicker> picker;
  std::unique_ptr<LanguageThingee> languages;
  std::unique_ptr<ScoreThingee> scores;
  std::unique_ptr<GAnalytics> analytics;

public:
  MainController(QQuickItem *parent);
  void setPlatformThingee(PlatformThingee *value);
  void setTrackingCode(QString ga);
  void index();

public slots:
  void onShow();
  void onRead(double value);
  void onLearnMore();
  void onClose();
  void onReady();
  void onReadChanged();
};
}
#endif // MAINCONTROLLER_H
