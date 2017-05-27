#ifndef STREAMPROVIDER_H
#define STREAMPROVIDER_H

#include <QQuickImageProvider>

#ifdef iosflag
#include "vlc/vlc.h"
#endif

#ifdef androidflag
#endif

class StreamProvider : public QQuickImageProvider
{
public:
    explicit StreamProvider(QQuickImageProvider::ImageType type);
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

signals:

public slots:
};

QMutex mutex;
void videoPrerender(void *data, uint8_t **buff, int size);
void videoPostrender(void *data, uint8_t *buff, int width, int height, int pitch, int size, int64_t pts);

#endif // STREAMPROVIDER_H
