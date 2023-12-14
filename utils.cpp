#include "utils.h"

Utils::Utils() {}

QPixmap Utils::GetPixmapFromUrl(const QString avatarURL)
{
    QNetworkAccessManager manager;
    QEventLoop loop;

    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(avatarURL)));

    // 等待网络请求完成
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 处理错误情况
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Failed to download image:" << reply->errorString();
        return QPixmap();
    }

    // 读取图像数据并转换为QPixmap对象
    QByteArray data = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(data);

    // 返回QPixmap对象
    return pixmap;
}

