#include "streammanager.h"

StreamManager::StreamManager(QObject *parent) : QObject(parent)
{
    byteCount = 0;

    QNetworkAccessManager *manager = new QNetworkAccessManager(parent);
    reply = manager->get(QNetworkRequest(QUrl("http://192.168.4.1/stream")));
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void StreamManager::readyRead() {
    if(byteCount == 0) {
        QChar ch = ' ';
        while(!ch.isDigit())
            ch = reply->read(1).data()[0];

        QString s = "";
        while(ch.isDigit()) {
            s.append(ch);
            ch = reply->read(1).data()[0];
        }

        byteCount = s.toInt();
        //eat newlines
        reply->read(3);
    }

    if(reply->bytesAvailable() >= byteCount) {
        process(reply->read(byteCount));
        byteCount = 0;
    }
}

void StreamManager::process(QByteArray data) {
    QImage test(data.data(), 320, 240, QImage::Format_RGB888);

    Mat img(320, 240, CV_8U, data.data());
    cvtColor(img, img, CV_BGR2GRAY);
    GaussianBlur(img, img, Size(9, 9), 2, 2);

    QVector<Vec3f> circles;
    HoughCircles(img, circles.toStdVector(), CV_HOUGH_GRADIENT, 1, img.rows / 8, 200, 100, 0, 0);
    Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
}
