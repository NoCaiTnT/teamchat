#include "user.h"
#include "ui_user.h"

User::User(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::User)
{
    ui->setupUi(this);
    initWidget();
    connectAll();
}

User::~User()
{
    delete ui;
}

void User::connectAll()
{
    connect(this, SIGNAL(userStatusChanged(UserStatus)),this, SLOT(handleUserStatusChanged(UserStatus)));
    connect(userStatusChoose, SIGNAL(clicked(bool)), this, SLOT(showUserStatusMenu()));
    connect(userStatusMenu, SIGNAL(triggered(QAction*)), this, SLOT(chooseUserStatus(QAction*)));
}

void User::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, Qt::white);
    this->setPalette(palette);

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform); // 抗锯齿

    // QPen pen(QColor("#4CD964"),3,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);         //轮廓
    // painter.setPen(pen);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    QPainterPath path;
    // path.addEllipse(10, 10, 50, 50); //圆
    path.addRect(10, 10, 50, 50); //矩形

    painter.setClipPath(path);

    // QPixmap pixMap = this->avatarPixmap;

    painter.drawPixmap(10, 10, 50, 50, avatarPixmap);

    painter.setClipRect(this->rect());
    painter.drawPath(path);

}

void User::initWidget()
{
    initUserInfoWidget();

}

void User::initUserInfoWidget()
{
    //设置昵称
    nickname = new QLabel(this->centralWidget());
    setLabelFont(nickname, 15, true);
    setLabelColor(nickname, "#3366ff");
    setLabelText(nickname, name, true);
    nickname->move(70, 12);

    // 设置在线状态
    userStatus = new QLabel(this->centralWidget());
    setLabelFont(userStatus, 10, false);
    setLabelColor(userStatus, ONLINEColor);
    setLabelText(userStatus, "在线", true);
    userStatus->move(70, 40);

    //设置用户状态按钮和菜单
    userStatusChoose = new QPushButton(this->centralWidget());
    userStatusChoose->setText("﹀");
    userStatusChoose->setFixedSize(25,20);
    userStatusChoose->move(nickname->x() + nickname->width() + 5, nickname->y() + 3);
    userStatusMenu = new QMenu(this->centralWidget());
    userChooseOnline = userStatusMenu->addAction(tr("在线"));
    userChooseOffline = userStatusMenu->addAction(tr("离线"));
}

void User::setLabelText(QLabel *label, QString text, bool adjust)
{
    label->setText(text);
     if(adjust == true){
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        label->adjustSize();
     }
}

void User::setLabelFont(QLabel *label, int fontSize, bool bold)
{
    QFont labelFont = label->font();          //字体（大小）
    labelFont.setPointSize(fontSize);
    labelFont.setBold(bold);
    label->setFont(labelFont);
}

void User::setLabelColor(QLabel *label, QString color)
{
    QPalette Palette = label->palette();
    Palette.setColor(QPalette::WindowText, color);
    label->setPalette(Palette);
}

void User::setUserStatus(UserStatus nowstatus)
{
    status = nowstatus;
    emit userStatusChanged(status);
}

void User::setAvatarFromURL(const QString &newAvatarURL)
{
    avatarURL = newAvatarURL;
    avatarPixmap = utils.getPixmapFromURL(avatarURL);
}

void User::handleUserStatusChanged(UserStatus nowstatus)
{
    QString color = "";
    switch(nowstatus){
        case ONLINE:
            color = ONLINEColor;
            setLabelText(userStatus, "在线", false);
            break;
        case OFFLINE:
            color = OFFLINEColor;
            setLabelText(userStatus, "离线", false);
            break;
    }
    setLabelColor(userStatus, color);

}

void User::showUserStatusMenu()
{
    userStatusMenu->exec(QCursor::pos());
}

void User::chooseUserStatus(QAction *action)
{
    if(action == userChooseOnline){
        setUserStatus(ONLINE);
    }else if(action == userChooseOffline){
        setUserStatus(OFFLINE);
    }
}
