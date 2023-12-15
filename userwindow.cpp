#include "userwindow.h"

UserWindow::UserWindow(QWidget *parent)
    : QWidget{parent}
{
    InitUserInfoWidget();
}

void UserWindow::InitUserInfoWidget()
{
    userinfo_ = new User(this);
    userinfo_->move(50,50);
    titlebar_ = new MyTitleBar(this);
    titlebar_->move(0,0);
}
