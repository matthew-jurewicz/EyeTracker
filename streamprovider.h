#ifndef STREAMPROVIDER_H
#define STREAMPROVIDER_H

#include <QQuickImageProvider>
#include <QNetworkReply>

#ifdef iosflag
#endif

#ifdef androidflag
#endif

class StreamProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    explicit StreamProvider(QQuickImageProvider::ImageType type);
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    QNetworkReply *reply;
    quint8 byteCount;
    QImage image;

signals:

public slots:
    void readyRead();
};

#endif // STREAMPROVIDER_H
