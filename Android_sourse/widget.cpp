#include "widget.h"
#include "ui_widget.h"
#include<QMovie>
#include<QtSql>
#include<QMessageBox>
QString p;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loginpage");
    db.setUserName("root");
    db.setPassword("123");
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        return;
    }
    qDebug() << "Connected to database!";

    QMovie *movie =new QMovie(this);
    movie->setFileName(":/sourse_images/background .gif");
    movie->start();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnlogin_clicked()
{
    QString phone = ui->username_2->text();
    QString password = ui->password_2->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loginpage");
    db.setUserName("root");
    db.setPassword("123");
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        return;
    }
    qDebug() << "Connected to database!";


    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE phone = :phone AND password = :password");
    query.bindValue(":phone", phone);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::warning(this, "登录失败", "登录失败，请重试！");
        return;
    } else {
        if (!query.next()) {
            // 查询结果为空，用户名和密码不匹配，登录失败
            qDebug() << "Login failed!";
            QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重试！");
            return;
        } else {
            // 查询结果非空，用户名和密码匹配，登录成功
            qDebug() << "Login successful!";
            QMessageBox::information(this, "登录成功", "登录成功！");
             f= new first();
            this->close();
            f->show();
            p=ui->username_2->text();
        }
    }
}


void Widget::on_btnreg_clicked()
{
    QString phone = ui->username_3->text();
    QString password = ui->password_3->text();
    QString registrationDate=QDateTime::currentDateTime().toString("yyyy-MM-dd");
    // 执行 SQL 查询来验证用户名和密码
    QSqlQuery query;
    query.prepare("INSERT INTO users (phone, password,registration_date) VALUES (:phone, :password,:registration_date)");
    query.bindValue(":phone", phone);
    query.bindValue(":password", password);
    query.bindValue(":registration_date",registrationDate);

    if (!query.exec()) {
        qDebug() << "Failed to insert data:" << query.lastError().text();
        QMessageBox::warning(this, "注册失败", "用户名已存在，请重试！");
        return;
    } else {
        qDebug() << "Data inserted successfully!";
        QMessageBox::information(this, "注册成功", "请返回登录界面！");
        // 注册成功，跳转至登录界面

    }

    // 关闭数据库连接
    QSqlDatabase::database().close();
}

