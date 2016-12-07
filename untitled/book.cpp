#include "book.h"
using namespace untitled;

Book::Book(QObject *parent) : QObject(parent) {}

QString Book::getName() const { return name; }

void Book::setName(const QString &value) { name = value; }

QString Book::getOrder() const { return order; }

void Book::setOrder(const QString &value) { order = value; }

QString Book::getAbbr() const { return abbr; }

void Book::setAbbr(const QString &value) { abbr = value; }

size_t Book::getIndex() const { return index; }

void Book::setIndex(const size_t value) { index = value; }
