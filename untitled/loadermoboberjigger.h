#ifndef LOADERMOBOBERJIGGER_H
#define LOADERMOBOBERJIGGER_H

#include "models.h"
namespace untitled {
class LoaderMoboberJigger {
public:
  LoaderMoboberJigger();
  std::vector<std::unique_ptr<Level>> loadLevels();
  std::map<QString, Book *> loadBooks();
  Config *loadConfig(QString isoLang);
  Element *loadElement(QString name, QString version);

private:
  QJsonDocument loadJson(QString url);
  template <typename T> T *fromJson(QJsonObject jsonObject);
  template <typename T>
  std::vector<std::unique_ptr<T>> getList(QJsonArray array);
};
}
#endif // LOADERMOBOBERJIGGER_H
