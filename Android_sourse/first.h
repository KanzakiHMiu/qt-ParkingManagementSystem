#ifndef FIRST_H
#define FIRST_H
#include <QWidget>
#include"changeinfo.h"
#include<QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

namespace Ui {
class first;
}

class first : public QWidget
{
    Q_OBJECT

public:
    explicit first(QWidget *parent = nullptr);
    void setHeadimage(QString imgpath);
    void loadData();
    ~first();

private slots:
    void on_btnchange_clicked();

    void on_tabWidget_currentChanged(int index);

    void showNextImage();

    void showPreviousImage();

    void animationFinished();

private:
    Ui::first *ui;
    changeinfo *cginfo;
    QTimer *timer;
    int currentIndex;
    QPropertyAnimation *currentAnimation;
    QPropertyAnimation *nextAnimation;
    QGraphicsOpacityEffect *currentEffect;
    QGraphicsOpacityEffect *nextEffect;
};

#endif // FIRST_H
