#include "user.h"
#include "ui_user.h"

User::User(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::User)
{
    ui->setupUi(this);
    InitWidget();
    ConnectAll();
}

User::~User()
{
    delete ui;
}

void User::ConnectAll()
{
    connect(this, SIGNAL(UserStatusChanged(UserStatus)),this, SLOT(HandleUserStatusChanged(UserStatus)));          //用户状态改变处理
    connect(user_status_choose_, SIGNAL(clicked(bool)), this, SLOT(ShowUserStatusMenu()));                         //点击，出菜单
    connect(user_status_menu_, SIGNAL(triggered(QAction*)), this, SLOT(ChooseUserStatus(QAction*)));               //点击菜单项的处理
}

void User::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    //<-画笔，用于绘制头像和背景
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform); // 抗锯齿
    //画笔，用于绘制头像和背景->

    //<-绘制背景颜色
    // 设置渐变色
    QLinearGradient linear(QPointF(0, 0), QPointF(this->width(), this->height()));
    linear.setColorAt(0, COLOR_BACKGROUND_FROM);
    linear.setColorAt(1, COLOR_BACKGROUND_TO);
    // 设置显示模式
    linear.setSpread(QGradient::PadSpread);
    // 设置画刷填充
    painter.setBrush(linear);
    // 绘制背景
    painter.drawRect(0,0,this->width(),this->height());
    //绘制背景颜色->

    //<-绘制头像
    //绘制头像轮廓
    // QPen pen(QColor("#4CD964"),3,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
    // painter.setPen(pen);
    //不绘制头像轮廓
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
    //绘制头像形状
    QPainterPath path;
    // path.addEllipse(10, 10, 50, 50); //圆
    path.addRect(10, 10, 50, 50); //矩形
    painter.setClipPath(path);
    //绘制头像图片、位置
    painter.drawPixmap(10, 10, 50, 50, avatar_pixmap_);
    //设置绘制窗口
    painter.setClipRect(this->rect());
    //绘制
    painter.drawPath(path);
    //绘制头像->
}

void User::InitWidget()
{
    InitUserInfoWidget();       //初始化用户信息控件，包括头像、昵称、状态、状态选择

}

void User::InitUserInfoWidget()
{
    //<-设置昵称
    nickname_ = new QLabel(this->centralWidget());       //创建昵称Label控件
    SetControlTextFont(nickname_, 15, true);             //设置字体样式，字号15，加粗
    SetControlTextColor(nickname_, COLOR_NICKNAME);      //设置字体颜色
    SetControlText(nickname_, name_, true);              //设置字体文本，控件跟随字体长短改变
    nickname_->move(70, 12);                             //设置控件位置
    //设置昵称->

    //<-设置在线状态
    user_status_ = new QLabel(this->centralWidget());     //创建用户状态Label控件
    SetControlTextFont(user_status_, 10, false);          //设置字体样式，字号10
    SetControlTextColor(user_status_, COLOR_ONLINE);      //设置字体颜色，默认在线
    SetControlText(user_status_, "在线", false);           //设置字体文本，默认在线
    user_status_->move(70, 40);                           //设置控件位置
    //设置在线状态->

    //<-设置用户状态选择按钮
    user_status_choose_ = new QPushButton(this->centralWidget());                                 //创建用户状态选择PushButton控件
    user_status_choose_->setFixedSize(25,20);                                                     //设置按钮大小
    user_status_choose_->setStyleSheet(QString("border: none;color: %1").arg(COLOR_NICKNAME));    //设置按钮无边框、字体颜色
    SetControlTextFont(user_status_choose_, 13, true);                                            //设置字体样式，字号15，加粗
    SetControlText(user_status_choose_, "﹀", false);                                             //设置字体文本
    user_status_choose_->move(nickname_->x() + nickname_->width() + 5, nickname_->y() + 5);       //设置控件位置
    //设置用户状态选择按钮->

    //<-设置用户状态选择菜单
    user_status_menu_ = new QMenu(this->centralWidget());                                                                    //创建用户状态选择Menu控件
    user_choose_online_ = user_status_menu_->addAction(tr(user_status_menu_option_text_one_.toStdString().c_str()));         //添加 在线 选项
    user_choose_offline_ = user_status_menu_->addAction(tr(user_status_menu_option_text_two_.toStdString().c_str()));        //添加 离线 选项
    //设置用户状态选择菜单->

}

template <typename T>
void User::SetControlText(T *control, QString text, bool adjust)
{
    //设置控件text内容
    control->setText(text);
    //控件自适应调整（Label）
    if(adjust == true){
        control->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        control->adjustSize();
    }
}

template <typename T>
void User::SetControlTextFont(T *control, int fontSize, bool bold)
{
    QFont font = control->font();
    font.setPointSize(fontSize);
    font.setBold(bold);
    control->setFont(font);
}

template <typename T>
void User::SetControlTextColor(T *control, QString color)
{
    QPalette Palette = control->palette();
    Palette.setColor(QPalette::WindowText, color);
    control->setPalette(Palette);
}

void User::SetUserStatus(UserStatus nowstatus)
{
    status_ = nowstatus;
    emit UserStatusChanged(status_);
}

void User::SetAvatarFromUrl(const QString &newAvatarURL)
{
    avatar_url_ = newAvatarURL;
    avatar_pixmap_ = utils_.GetPixmapFromUrl(avatar_url_);
}

void User::HandleUserStatusChanged(UserStatus nowstatus)
{
    QString color = "";
    switch(nowstatus){
        case kONLINE:
            color = COLOR_ONLINE;
            SetControlText(user_status_, user_status_menu_option_text_one_, false);
            break;
        case kOFFLINE:
            color = COLOR_OFFLINE;
            SetControlText(user_status_, user_status_menu_option_text_two_, false);
            break;
    }
    SetControlTextColor(user_status_, color);

}

void User::ShowUserStatusMenu()
{
    user_status_menu_->exec(QCursor::pos());
}

void User::ChooseUserStatus(QAction *action)
{
    if(action == user_choose_online_){
        SetUserStatus(kONLINE);
    }else if(action == user_choose_offline_){
        SetUserStatus(kOFFLINE);
    }
}
