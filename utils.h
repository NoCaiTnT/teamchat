#ifndef UTILS_H
#define UTILS_H
#include <QPainter>
#include <QPainterPath>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QLabel>
class utils
{
public:
    utils();
    QPixmap getPixmapFromURL(const QString avatarURL);      //根据URL获得图像
};

#endif // UTILS_H
