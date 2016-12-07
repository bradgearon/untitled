#include "config.h"
using namespace untitled;

Config::Config(QObject *parent) : QObject(parent) {}

QString Config::getMore() const { return more; }

void Config::setMore(const QString &value) { more = value; }

bool Config::getRtl() const { return rtl; }

void Config::setRtl(bool value) { rtl = value; }

QVariant Config::getVersion() const { return version; }

void Config::setVersion(const QVariant &value) { version = value; }

QString Config::getUrl() const { return url; }

void Config::setUrl(const QString &value) { url = value; }

QString Config::getContent() const { return content; }

void Config::setContent(const QString &value) { content = value; }

QString Config::getRemove() const { return remove; }

void Config::setRemove(const QString &value) { remove = value; }

QString Config::getTitle() const { return title; }

void Config::setTitle(const QString &value) { title = value; }

QString Config::getReplace() const { return replace; }

void Config::setReplace(const QString &value) { replace = value; }

bool Config::getUseIds() const { return useIds; }

void Config::setUseIds(bool value) { useIds = value; }

bool Config::getUseName() const { return useName; }

void Config::setUseName(bool value) { useName = value; }
