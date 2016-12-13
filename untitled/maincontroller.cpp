#include "maincontroller.h"

using namespace untitled;

void MainController::setPlatformThingee(PlatformThingee *value) {
  platformThingee = std::unique_ptr<PlatformThingee>(value);
}

MainController::MainController(QQuickItem *parent) : QObject() {
  view = parent;
  LoaderMoboberJigger loader;

  picker = std::make_unique<LevelPicker>(loader);
  languages = std::make_unique<LanguageThingee>(loader);
  scores = std::make_unique<ScoreThingee>(picker.get());

  scores->readScores();
  scores->saveScores();

  auto locale = QLocale::system();
  isoLang = locale.name().split("_")[0];

  config = languages->setConfig(isoLang);
}

void MainController::index() {
  picked = picker->pick();
  element = languages->getElementByName(picked->getName());

  viewModel = std::make_unique<Form1ViewModel>(picked, config, element);

  connect(viewModel.get(), &Form1ViewModel::close, this,
          &MainController::onClose);

  connect(viewModel.get(), &Form1ViewModel::ready, this,
          &MainController::onReady);

  connect(viewModel.get(), &Form1ViewModel::read, this,
          &MainController::onRead);

  connect(viewModel.get(), &Form1ViewModel::learnMore, this,
          &MainController::onLearnMore);

  pickedConnection = QObject::connect(picked, &Score::readChanged, this,
                                      &MainController::onReadChanged);

  viewModelVariant = QVariant::fromValue(viewModel.get());
  view->setProperty("model", viewModelVariant);
}

void MainController::onRead(double value) {
  picked->setRead(value);
  qDebug() << "main controller on read: " << value;
}

void MainController::onLearnMore() {
  QDesktopServices::openUrl(element->getLearnMorePath());
  qDebug() << "main controller onLearnMore";
}

void MainController::onClose() {
  qDebug() << " on close";

  platformThingee->hide();

  // using namespace std::chrono_literals;
  // std::this_thread::sleep_for(5s);
  picked = picker->pick();

  if (pickedConnection) {
    QObject::disconnect(pickedConnection);
  }

  pickedConnection = QObject::connect(picked, &Score::readChanged, this,
                                      &MainController::onReadChanged);

  auto element = languages->getElementByName(picked->getName());

  viewModel->setElement(element);
  viewModel->setScore(picked);

  view->setProperty("model", viewModelVariant);
}

void MainController::onReady() {
  isReady = true;

  qDebug() << "main controller on ready";
}

void MainController::onReadChanged() {
  qDebug() << "main controller on read changed";
  scores->saveScores();
}

void MainController::show() {
  qDebug() << "main controller on show";

  platformThingee->show();
}