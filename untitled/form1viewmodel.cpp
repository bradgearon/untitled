#include "form1viewmodel.h"
using namespace untitled;

Form1ViewModel::Form1ViewModel(QObject *parent) : QObject(parent) {}

Form1ViewModel::Form1ViewModel(QJsonObject modelJson) : Form1ViewModel() {
  const auto meta = metaObject();
  int count = meta->propertyCount();
  for (auto i = 0; i < count; i++) {
    auto property = meta->property(i);
    if (modelJson.contains(property.name())) {
      setProperty(property.name(), modelJson[property.name()].toVariant());
    }
  }
}

bool Form1ViewModel::getIsRtl() const { return isRtl; }

void Form1ViewModel::setIsRtl(bool value) { isRtl = value; }

QString Form1ViewModel::getImageName() const { return imageName; }

void Form1ViewModel::setImageName(const QString &value) { imageName = value; }

QString Form1ViewModel::getVerse() const { return verse; }

void Form1ViewModel::setVerse(const QString &value) { verse = value; }

QString Form1ViewModel::getTitle() const { return title; }

void Form1ViewModel::setTitle(const QString &value) { title = value; }

void Form1ViewModel::setScore(Score *value) { score = value; }

void untitled::Form1ViewModel::onRead(double value) {
  emit read(value);
  qDebug() << "onRead: " << value;
}

void untitled::Form1ViewModel::onLearnMore() {
  emit learnMore();
  qDebug() << "onLearnMore ";
}

void untitled::Form1ViewModel::onClose() {
  emit close();
  qDebug() << " on close";
}

void untitled::Form1ViewModel::onShow() {
  emit show();
  qDebug() << " on show";
}
