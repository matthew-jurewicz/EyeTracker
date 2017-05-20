#include "messagedialog.h"

MessageDialog::MessageDialog(QObject *parent) : QObject(parent)
{
    dlog = new QQuickView;
    dlog->setSource(QUrl("qrc:/message_dialog.qml"));
    QQuickItem::connect(dlog->rootObject(), SIGNAL(okClicked()), this, SLOT(okClicked()));
    dlog->show();
}

void MessageDialog::okClicked() {
    dlog->hide();
}
