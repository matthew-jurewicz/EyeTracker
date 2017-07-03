#include "streamprovider.h"

StreamProvider::StreamProvider(QQuickImageProvider::ImageType type) : QQuickImageProvider(type)
{
    byteCount = 0;
    image = QImage(1000, 1000, QImage::Format_Grayscale8);

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    reply = manager->get(QNetworkRequest(QUrl("http://192.168.4.1/stream")));
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void StreamProvider::readyRead() {

}

QImage StreamProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    return image;
}
