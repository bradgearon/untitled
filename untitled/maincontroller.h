#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "models.h"

#include "form1viewmodel.h"
#include "languagethingee.h"
#include "levelpicker.h"
#include "loadermoboberjigger.h"
#include "scorethingee.h"

#include <QQuickItem>
#include <QQuickWindow>

namespace untitled {

class MainController : public QObject {
  Q_OBJECT

private:
  QQuickItem *view;
  Config *config;
  Score *picked;
  Element *element;
  QVariant viewModelVariant;
  QMetaObject::Connection pickedConnection;
  QString isoLang;

  std::unique_ptr<Form1ViewModel> viewModel;
  std::unique_ptr<LevelPicker> picker;
  std::unique_ptr<LanguageThingee> languages;
  std::unique_ptr<ScoreThingee> scores;

public:
  MainController(QQuickItem *parent);
  void index();
  Q_INVOKABLE void show();
  bool isReady;
public slots:
  void onRead(double value);
  void onLearnMore();
  void onClose();
  void onReady();
  void onReadChanged();
};
}
#endif // MAINCONTROLLER_H
