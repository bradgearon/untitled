#ifndef CONFIG_H
#define CONFIG_H

#include "models.h"

namespace untitled {

class Config : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString more READ getMore WRITE setMore)
  Q_PROPERTY(bool rtl READ getRtl WRITE setRtl)
  Q_PROPERTY(QString url READ getUrl WRITE setUrl)
  Q_PROPERTY(QString content READ getContent WRITE setContent)
  Q_PROPERTY(QString remove READ getRemove WRITE setRemove)
  Q_PROPERTY(QString title READ getTitle WRITE setTitle)
  Q_PROPERTY(QString replace READ getReplace WRITE setReplace)
  Q_PROPERTY(bool useIds READ getUseIds WRITE setUseIds)
  Q_PROPERTY(bool useName READ getUseName WRITE setUseName)

private:
  /*
   * to generate properties from these
   * find: \s+(.+ )(.)(.+)\s*\=.+\;
   * replace: Q_PROPERTY\($1$2$3 READ get\U$2\E$3 WRITE set\U$2\E$3\)\n
   */
  QString more;
  bool rtl = false;
  QStringList version;
  QString url;

  QString content;
  QString remove;
  QString title;
  QString replace;
  bool useIds = false;
  bool useName = false;

public:
  explicit Config(QObject *parent = 0);

  QString getMore() const;
  void setMore(const QString &value);

  bool getRtl() const;
  void setRtl(bool value);

  QStringList getVersion() const;
  void setVersion(const QStringList &value);

  QString getUrl() const;
  void setUrl(const QString &value);

  QString getContent() const;
  void setContent(const QString &value);

  QString getRemove() const;
  void setRemove(const QString &value);

  QString getTitle() const;
  void setTitle(const QString &value);

  QString getReplace() const;
  void setReplace(const QString &value);

  bool getUseIds() const;
  void setUseIds(bool value);

  bool getUseName() const;
  void setUseName(bool value);
};
}
#endif // CONFIG_H
