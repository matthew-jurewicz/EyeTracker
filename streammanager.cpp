#include "streammanager.h"

StreamManager::StreamManager(QObject *parent) : QObject(parent)
{
    buffer = new QByteArray;
    delim = QString("--frame\r\n");

    QNetworkAccessManager *manager = new QNetworkAccessManager(parent);
    reply = manager->get(QNetworkRequest(QUrl("http://192.168.4.1/stream")));
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void StreamManager::readyRead() {
    if(buffer->length() == 0)
        reply->read(delim.length());

    buffer->append(reply->readAll());
    idx = buffer->indexOf(delim);
    if(idx != -1) {
        process(buffer->left(idx));
        buffer = buffer->right(buffer->length() - idx - delim.length());
    }
}

void StreamManager::process(QByteArray data) {

}