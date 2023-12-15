#include "user.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    User w;
    w.SetAvatarFromUrl("https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fsafe-img.xhscdn.com%2Fbw1%2F4d40b566-1f0a-4f8d-bc97-c513df8775b3%3FimageView2%2F2%2Fw%2F1080%2Fformat%2Fjpg&refer=http%3A%2F%2Fsafe-img.xhscdn.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1704014893&t=cafa323998f8c19a9d7aa9656551e890");      //设置头像路径
    w.show();
    return a.exec();
}
