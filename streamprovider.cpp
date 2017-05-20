#include "streamprovider.h"

#ifdef iosflag
#endif

#ifdef androidflag
#endif

StreamProvider::StreamProvider(QQuickImageProvider::ImageType type) : QQuickImageProvider(type)
{

}

QImage StreamProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {

}
