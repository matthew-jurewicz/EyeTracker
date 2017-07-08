#ifndef STREAMMANAGER_H
#define STREAMMANAGER_H

#include <QObject>
#include <QNetworkReply>

#ifdef iosflag
#endif

#ifdef androidflag
#endif

using namespace cv;

class StreamManager : public QObject
{
    Q_OBJECT
public:
    explicit StreamManager(QObject *parent = 0);
    QNetworkReply *reply;
    QByteArray *buffer;
    QString delim;
    void process(QByteArray data);

signals:

public slots:
    void readyRead();
};

#endif // STREAMMANAGER_H
