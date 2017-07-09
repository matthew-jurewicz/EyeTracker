#include "streammanager.h"

StreamManager::StreamManager(QObject *parent) : QObject(parent)
{
    delim = QString("--frame\r\nContent-Type: image/jpeg\r\n\r\n");

    QNetworkAccessManager *manager = new QNetworkAccessManager(parent);
    reply = manager->get(QNetworkRequest(QUrl("http://192.168.4.1/stream")));
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void StreamManager::readyRead() {
    if(buffer.length() == 0)
        reply->read(delim.length());

    buffer.append(reply->readAll());
    qint64 idx = buffer.indexOf(delim);
    if(idx != -1) {
        process(buffer.left(idx));
        buffer = buffer.right(buffer.length() - idx - delim.length());
    }
}

void StreamManager::process(QByteArray data) {
    Mat img(320, 240, CV_8U, data.data());
    cvtColor(img, img, CV_BGR2GRAY);
    GaussianBlur(img, img, Size(9, 9), 2, 2);

    QVector<Vec3f> circles;
    HoughCircles(img, circles.toStdVector(), CV_HOUGH_GRADIENT, 1, img.rows / 8, 200, 100, 0, 0);
    Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
}
