#include "pageaction.h"

PageAction::PageAction(QObject *parent) : QObject(parent)
{

}

void PageAction::loaded() {
    qDebug("loaded ");
    sender()->dumpObjectInfo();
}

void PageAction::close() {
    qDebug("close");
}

void PageAction::read() {
    qDebug("read");
}

