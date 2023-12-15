#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include "utils.h"
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <mytitlebar.h>
#include <QScreen>

QT_BEGIN_NAMESPACE
namespace Ui {
class User;
}
QT_END_NAMESPACE

enum UserStatus{
    kONLINE,
    kOFFLINE
};

#define COLOR_ONLINE "#4CD964"
#define COLOR_OFFLINE "#D71345"
#define COLOR_NICKNAME "#3366FF"
#define COLOR_BACKGROUND_FROM "#082E54"
#define COLOR_BACKGROUND_TO "#000000"

class User : public QMainWindow
{
    Q_OBJECT

signals:
    void UserStatusChanged(UserStatus nowstatus);               //用户状态改变信号

private slots:
    void HandleUserStatusChanged(UserStatus nowstatus);         //根据用户状态设置昵称的颜色
    void ShowUserStatusMenu();                                  //显示用户在线状态菜单
    void ChooseUserStatus(QAction* action);                     //选择用户状态

    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

public:
    User(QWidget *parent = nullptr);
    ~User();

    //methods
    void SetAvatarFromUrl(const QString &newAvatarURL);     //从URL中获取头像

private:
    //variables
    Utils utils_;                                       //工具类
    UserStatus status_;                                 //用户状态
    QString avatar_url_;                                //头像URL
    QString name_ = "NoCai";                            //昵称
    QPixmap avatar_pixmap_;                             //头像图像
    QAction *user_choose_online_;                       //用户选择在线动作
    QAction *user_choose_offline_;                      //用户选择离线动作
    QString user_status_menu_option_text_one_ = "在线";  //用户状态菜单选项文本1
    QString user_status_menu_option_text_two_ = "离线";  //用户状态菜单选项文本2

    //control
    Ui::User *ui;
    QLabel *nickname_;                          //昵称
    QLabel *user_status_;                       //用户状态
    QMenu *user_status_menu_;                   //状态菜单
    QPushButton *user_status_choose_;           //用户状态选择按钮
    MyTitleBar *titlebar_;

    //overrided methods
    void paintEvent(QPaintEvent *event);        //绘制头像

    //methods
    void ConnectAll();                          //信号与槽连接
    void InitWidget();                          //初始化所有控件/布局
    void InitTitlebar();
    void InitUserInfoWidget();                  //初始化用户信息相关控件
    void SetUserStatus(UserStatus nowstatus);   //设置用户状态

    template <typename T>
    void SetControlTextFont(T* control, int fontSize, bool bold);             //设置标签的字体大小
    template <typename T>
    void SetControlTextColor(T* control, QString color);                      //设置标签的颜色
    template <typename T>
    void SetControlText(T* control, QString text, bool adjust);               //设置标签的内容

};
#endif // USER_H
