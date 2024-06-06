#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <experimental/filesystem>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Mat act1(cv::Mat image);
    QString act2(Mat image);
    Mat Get_License_ROI(Mat src);
    int PixelCounter(Mat open,int ee);
    Mat Horizon_Cut(Mat image);
    QVector<QVector<int> > Remove_Vertial_Border(Mat image);
    vector<Rect>Remove_cahr(Mat image,Mat imag);
    QStringList readJpgFiles(const QString&, int);
    Mat texs_act(Mat);
    QString chuan(const QString& folderPath, int maxFiles);
    double do_read(Mat temo,Mat temp);
    QString switchFunction(const std::string& key);
    Mat cutCut(Mat image);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
