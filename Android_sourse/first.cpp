#include "first.h"
#include "ui_first.h"
#include<QtSql>
extern QString p;
first::first(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::first)
    , currentIndex(0)
{
    ui->setupUi(this);

    // 设置 QTimer 定时切换图像
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &first::showNextImage);
    timer->start(4000);

    // 创建透明度效果
    currentEffect = new QGraphicsOpacityEffect(ui->changeimage->widget(currentIndex));
    ui->changeimage->widget(currentIndex)->setGraphicsEffect(currentEffect);
    currentEffect->setOpacity(1.0);

    nextEffect = new QGraphicsOpacityEffect();
    nextEffect->setOpacity(0.0);

    // 设置 QPropertyAnimation 动画
    currentAnimation = new QPropertyAnimation(currentEffect, "opacity");
    nextAnimation = new QPropertyAnimation(nextEffect, "opacity");

    // 连接按钮信号到槽函数
    connect(ui->previousButton, &QPushButton::clicked, this, &first::showPreviousImage);
    connect(ui->nextButton, &QPushButton::clicked, this, &first::showNextImage);
}

void first::setHeadimage(QString imgpath)
{
    ui->labheadimage->setStyleSheet(imgpath);
}

void first::loadData()
{

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE phone = "+p);// 修改为你的表名和条件

    if (query.exec() && query.next())
    {
        ui->username->setText(query.value("username").toString());
        ui->phone->setText(query.value("phone").toString());
        ui->email->setText(query.value("email").toString());
        ui->car_plate->setText(query.value("car_plate").toString());
    } else {
        qDebug() << "Load Data Error: " << query.lastError().text();
    }
}
first::~first()
{
    delete ui;
}

void first::on_btnchange_clicked()
{
    cginfo=new changeinfo();
    this->hide();
    cginfo->show();
}


void first::on_tabWidget_currentChanged(int index)
{
    if (index == 2) {
        loadData();
    }
}

void first::showNextImage() {
    int nextIndex = (currentIndex + 1) % ui->changeimage->count();

    // 设置动画的开始和结束值
    currentAnimation->setDuration(1500);
    currentAnimation->setStartValue(1.0);
    currentAnimation->setEndValue(0.0);

    nextAnimation->setDuration(1500);
    nextAnimation->setStartValue(0.0);
    nextAnimation->setEndValue(1.0);

    // 应用透明度效果
    ui->changeimage->widget(nextIndex)->setGraphicsEffect(nextEffect);

    // 切换到下一个图像
    ui->changeimage->setCurrentIndex(nextIndex);

    // 启动动画
    currentAnimation->start();
    nextAnimation->start();

    currentIndex = nextIndex;
}

void first::showPreviousImage() {
    int nextIndex = (currentIndex - 1 + ui->changeimage->count()) % ui->changeimage->count();

    // 设置动画的开始和结束值
    currentAnimation->setDuration(1500);
    currentAnimation->setStartValue(1.0);
    currentAnimation->setEndValue(0.0);

    nextAnimation->setDuration(1500);
    nextAnimation->setStartValue(0.0);
    nextAnimation->setEndValue(1.0);

    // 应用透明度效果
    ui->changeimage->widget(nextIndex)->setGraphicsEffect(nextEffect);

    // 切换到上一个图像
    ui->changeimage->setCurrentIndex(nextIndex);

    // 启动动画
    currentAnimation->start();
    nextAnimation->start();

    currentIndex = nextIndex;
}

void first::animationFinished() {
    // 动画完成后，重置透明度效果
    currentEffect->setOpacity(1.0);
    nextEffect->setOpacity(0.0);
}






