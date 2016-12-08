#include "form1viewmodel.h"
using namespace untitled;

void Form1ViewModel::setConfig(Config *value) { config = value; }

void Form1ViewModel::setElement(Element *value) { element = value; }

void Form1ViewModel::setScore(Score *value) { score = value; }

Form1ViewModel::Form1ViewModel(QObject *parent) : QObject(parent) {}

Form1ViewModel::Form1ViewModel(Score *score, Config *config, Element *element)
    : Form1ViewModel() {
  this->score = score;
  this->config = config;
  this->element = element;
}

QString Form1ViewModel::getMore() const { return config->getMore(); }

bool Form1ViewModel::getIsRtl() const { return config->getRtl(); }

QString Form1ViewModel::getImageName() const { return element->getImagePath(); }

QString Form1ViewModel::getVerse() const { return element->getVerse(); }

QString Form1ViewModel::getTitle() const { return element->getTitle(); }
