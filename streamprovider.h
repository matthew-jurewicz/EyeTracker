#ifndef STREAMPROVIDER_H
#define STREAMPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>

class StreamProvider : public QQuickImageProvider
{
    Q_OBJECT
public:
    explicit StreamProvider(QQuickImageProvider::ImageType type);
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

signals:

public slots:
};

#endif // STREAMPROVIDER_H
