#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include "utils.h"
#include <QLabel>
#include <QMenu>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class User;
}
QT_END_NAMESPACE

enum UserStatus{
    ONLINE,
    OFFLINE
};

#define ONLINEColor "#4CD964"
#define OFFLINEColor "#D71345"

class User : public QMainWindow
{
    Q_OBJECT

signals:
    void userStatusChanged(UserStatus nowstatus);               //用户状态改变信号

private slots:
    void handleUserStatusChanged(UserStatus nowstatus);         //根据用户状态设置昵称的颜色
    void showUserStatusMenu();                                  //显示用户在线状态菜单
    void chooseUserStatus(QAction* action);                     //选择用户状态

public:
    User(QWidget *parent = nullptr);
    ~User();

    //methods
    void setAvatarFromURL(const QString &newAvatarURL);     //从URL中获取头像

private:
    //variables
    utils utils;                            //工具类
    UserStatus status;                      //用户状态
    QString avatarURL;                      //头像URL
    QString name = "NoCai";                 //昵称
    QPixmap avatarPixmap;                   //头像图像
    QAction *userChooseOnline;              //用户选择在线动作
    QAction *userChooseOffline;             //用户选择离线动作

    //control
    Ui::User *ui;
    QLabel *nickname;                       //昵称
    QLabel *userStatus;                     //用户状态
    QMenu *userStatusMenu;                  //状态菜单
    QPushButton *userStatusChoose;          //用户状态选择按钮

    //methods
    void connectAll();                      //信号与槽连接
    void paintEvent(QPaintEvent *event);    //绘制头像
    void initWidget();                      //初始化所有控件/布局
    void initUserInfoWidget();              //初始化用户信息相关控件
    void setLabelText(QLabel* label, QString text, bool adjust);     //设置标签的内容
    void setLabelFont(QLabel* label, int fontSize, bool bold);       //设置标签的字体大小
    void setLabelColor(QLabel* label, QString color);                //设置标签的颜色
    void setUserStatus(UserStatus nowstatus);  //设置用户状态
};
#endif // USER_H
