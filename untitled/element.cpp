#include "element.h"
using namespace untitled;

QString Element::getTitle() const { return title; }

void Element::setTitle(const QString &value) { title = value; }

QString Element::getImagePath() const { return imagePath; }

void Element::setImagePath(const QString &value) { imagePath = value; }

QString Element::getLearnMorePath() const { return learnMorePath; }

void Element::setLearnMorePath(const QString &value) { learnMorePath = value; }

QString Element::getVerse() const { return verse; }

void Element::setVerse(const QString &value) { verse = value; }
