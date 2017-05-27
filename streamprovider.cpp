#include "streamprovider.h"

StreamProvider::StreamProvider(QQuickImageProvider::ImageType type) : QQuickImageProvider(type)
{
    char *options = QString("#transcode{vcodec=mp1v}:smem{video-prerender-callback=%1,video-postrender-callback=%2}")
            .arg((long long int)(intptr_t)(void*)&videoPrerender).arg((long long int)(intptr_t)(void*)&videoPostrender).toLatin1().data();
}

QImage StreamProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {

}

void videoPrerender(void *data, uint8_t **buff, int size) {
    mutex.lock();
    uint8_t *temp = (uint8_t*)malloc(size);
    *buff = temp;
}

void videoPostrender(void *data, uint8_t *buff, int width, int height, int pitch, int size, int64_t pts) {
    mutex.unlock();
}
