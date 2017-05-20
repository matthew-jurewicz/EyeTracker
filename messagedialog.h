#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QObject>
#include <QQuickView>
#include <QQuickItem>

class MessageDialog : public QObject
{
    Q_OBJECT
public:
    explicit MessageDialog(QObject *parent = 0);
    QQuickView *dlog;

signals:

public slots:
    void okClicked();
};

#endif // MESSAGEDIALOG_H
