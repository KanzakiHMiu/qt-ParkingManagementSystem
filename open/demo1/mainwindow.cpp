#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int j = 0;
int erroo=0;
int errot=0;
namespace fs = experimental::filesystem;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    //Mat image=imread("C:/opencv/photoss/31408194fcc24328b6d61b04123f2ad4.png");//一定要使用绝对路径，其他可以回报错
    Mat image=imread("D:/VehicleLicense/VehicleLicense/Infer/test08.png");
    //Mat image=imread("D:/CBLPRD-330k/000000004.jpg");
    //readJpgFiles("D:/CBLPRD-330k",100) ;qDebug()<<"act1_error: "<<erroo<<"act2_error: "<<errot;
    // namedWindow( "Display window", WINDOW_AUTOSIZE );
     imshow( "Display window", image );
      Mat texs1=act1(image);
     Mat texs2=Get_License_ROI(texs1);
      Mat texs3=cutCut(texs2);

    // imshow("t2",texs2);
    // Mat texs3=Horizon_Cut(texs2);
    // imshow("t3",texs3);
    Remove_Vertial_Border(texs3);//使用遍历行切割

      //vector<Rect> tt =Remove_cahr(texs2,texs1);//使用连通域切割

    qDebug()<<chuan("C:/opencv/save",21);
}

QStringList MainWindow::readJpgFiles(const QString& folderPath, int maxFiles) {
    QStringList jpgFiles;
    QDir dir(folderPath);

    // 设置过滤以仅获取 .jpg 文件
    dir.setNameFilters(QStringList() << "*.jpg");
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot); // 排除 . 和 ..

    // 遍历文件夹
    const auto fileInfos = dir.entryInfoList();
    for (const QFileInfo& fileInfo : fileInfos) {
        // 将文件名添加到列表中
        jpgFiles.append(fileInfo.fileName());

        // 如果达到最大文件数，则停止
        if (jpgFiles.size() >= maxFiles) {
            break;
        }
        QString filePath = folderPath + "/" + fileInfo.fileName();

        // 读取图像并处理
        Mat image = imread(filePath.toStdString());
        if (image.empty()) {
            qDebug()<<"aaaa";
            continue;
        }

        Mat texs1=act1(image);
        if (texs1.empty()) {
            qDebug() << "Processing of image resulted in empty Mat. Exiting function.";erroo++;
            continue;
        }
        imshow("t1",texs1);
        Mat texs2=Get_License_ROI(texs1);
        if (texs2.empty()) {
            qDebug() << "Processing of image resulted in empty Mat. Exiting function.";errot++;
            continue;
        }
        imshow("t2",texs2);
        // Mat texs3=Horizon_Cut(texs2);
        // imshow("t3",texs3);
        Remove_cahr(texs2,texs1);

        // for (int i = 0; i < t.size(); i++)
        // {
        //     Mat str = texs2(Range(0,texs2.rows),Range(t[i][0],t[i][1]));
        //     if (str.empty()) {
        //         qDebug() << "Processing of image resulted in empty Mat. Exiting function.";
        //         continue;
        //     }
        //     imshow(to_string(i),str);

        //     j++;
        //     QString t_s = QString::number(j);
        //     string s = string((const char *)t_s.toLocal8Bit());
        //     imwrite("C:/opencv/save/save"+s+".jpg",str);
        // }
    }

    return jpgFiles;
}




MainWindow::~MainWindow()
{
    delete ui;
}

Mat MainWindow::act1(cv::Mat image)
{
    Mat img_HSV = image.clone();//复制
    Mat img_t = image.clone();


    Mat img2_gauss;
    Mat img2_gray,dst_x,abs_X;
    //高斯去噪
    GaussianBlur(img_HSV, img2_gauss, Size(3, 3), 0);


    cvtColor(img2_gauss, img2_gray, COLOR_BGR2GRAY);


    Sobel(img2_gray, dst_x, CV_16S, 1, 0);           //梯度算子
    convertScaleAbs(dst_x, abs_X);                //将CV_16S型的输出图像转变成CV_8U型的图像
    imshow("tests1",dst_x);
    Mat img_temo = abs_X;
    threshold(img_temo, img_temo, 0, 255, THRESH_OTSU);     //用这个函数，自适应阀值图像灰度大于阈值
    imshow("tests",img_temo);


    // 闭操作,封闭轮廓
    Mat kernelY;
    Mat kernelX = getStructuringElement(MORPH_RECT, Size(17, 5));  //构造一个矩形
    morphologyEx(img_temo, img_temo, MORPH_CLOSE, kernelX);
imshow("tests-",img_temo);
    //用矩形来封闭
    kernelX = getStructuringElement(MORPH_RECT,Size(80, 1));
    kernelY = getStructuringElement(MORPH_RECT,Size(1, 20));




dilate(img_temo, img_temo, kernelX);                      //图像膨胀
erode(img_temo, img_temo, kernelX);//图像腐蚀

    dilate(img_temo, img_temo, kernelX);
morphologyEx(img_temo, img_temo, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(2,2)));


    erode(img_temo, img_temo, kernelY);
    dilate(img_temo, img_temo, kernelY);

    erode(img_temo, img_temo, kernelX);//图像腐蚀
    dilate(img_temo, img_temo, kernelX);                      //图像膨胀

    // 平滑去噪处理，使边缘检测更准确
    GaussianBlur(img_temo, img_temo, Size(15, 0), 1);
    imshow("carr",img_temo);


    vector<vector<Point>> contours;
    vector<Vec4i> vec_4f;
    // 从二值化后的img图中提取所有轮廓
    findContours(img_temo, contours, vec_4f, RETR_TREE, CHAIN_APPROX_SIMPLE);
    //在原图image上绘制所有轮廓(红色)
       drawContours(image, contours, -1, Scalar(0, 0, 255), 1);
       imshow("car_num",image);
    //筛选

    Mat chepai;
    int j = 0;
    vector<vector<Point>>contours_1;
    Rect rect_1;
    for (int i = 0; i < contours.size(); i++)
    {

        //计算轮廓的垂直边界最小矩形
        Rect rect = boundingRect(contours[i]);
        int x = rect.x;
        int y = rect.y;
        int area = rect.height * rect.width;
        if ((rect.width > (rect.height * 2.3) )&& area> 20000/*&& area< 60000*/)//选择符合范围的矩形框
        {
            chepai = img_HSV(Rect(rect.x,rect.y,rect.width,rect.height));  //区域提取
            //将提取出来的区域拿绿色矩形围起来
            //rectangle(chepai,Point(rect.x,rect.y),Point(rect.x + rect.width, rect.y + rect.height),Scalar(0,255,0),1);
            rect_1 = rect;
            contours_1.push_back(contours[i]);
        }
    }
    if (chepai.empty()) {
        qDebug() << "Processing of image resulted in empty Mat. Exiting function.1";
        return chepai; // Return empty list and exit function
    }
    imshow("test0",chepai);
    //    drawContours(img_t, contours_1, -1, Scalar(0, 0, 255), 1);
    //    imshow("sda",chepai);
    //对倾斜车牌进行处理操作
    //    vector<Point> cnt = contours_1[contours_1.size() - 1];
    //    Vec4f d;
    //    fitLine(cnt,d,DIST_L2,0,0.01,0.01);
    //    double k = d[1] / d[0];
    //    double b = d[2] - d[3] * k;

    //    double w = img_t.size().width;
    //    double h = img_t.size().height;
    //    double lefty = b;
    //    double righty = k*w+b;
    //    double a = atan(k);
    //    a = a*180/3.1415926;


    //    Mat m = getRotationMatrix2D(Point(w/2,h/2),a,0.8);
    //    Mat dst;
    //    warpAffine(img_t,dst,m,Size((int(w*0.9)),(int(h*0.9))));
    //    dst = do_line(dst);
    //    if(dst.empty()){
    //       return chepai;
    //    }
    return chepai;
}


Mat MainWindow::Get_License_ROI(Mat src)
{

    //GaussianBlur(src,src, Size(3, 3), 0);

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //--------------------------------锐化----------------
    // 创建拉普拉斯滤波器核
    // Mat kernelrh = (Mat_<float>(3, 3) <<
    //                     0, -1, 0,
    //                 -1, 5, -1,
    //                 0, -1, 0);

    // // 对灰度图像进行滤波
    // filter2D(src,src, CV_8U, kernelrh);
    //------------------------------------------------------------------------









    imshow("aa",gray);
    Mat thresh;
    threshold(gray, thresh, 0, 255, THRESH_OTSU);

    //使用形态学开操作去除一些小轮廓
    Mat kernel = getStructuringElement(MORPH_RECT, Size(2,2));
    Mat open;
    morphologyEx(thresh, open, MORPH_OPEN, kernel);


    //PixelCounter()是我自己写的函数，查找黑白点个数
    int black = PixelCounter(open,2);
    int white = PixelCounter(open,1);
    qDebug()<<"黑像素点"<<black<<"白像素点"<<white;
    if(black < white){
        threshold(open, open, 0, 255, THRESH_OTSU|THRESH_BINARY_INV);
    }
    imshow("asc",open);
    Mat kernelX = getStructuringElement(MORPH_RECT,Size(2,2));
    Mat kernelY = getStructuringElement(MORPH_RECT,Size(2,2));

   //erode(open,open, kernelX);//图像腐蚀
//dilate(open,open, kernelY);                      //图像膨胀
    //---------------------------------------------canny-----------------------------------
    // Mat edges;
    // Canny(open, edges, 50, 150); // 进行Canny边缘检测

    // vector<vector<Point>> contours;
    // findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // 查找轮廓

    // Mat result = open.clone();
    // for (int i = 0; i < contours.size(); i++) {
    //     Rect rect = boundingRect(contours[i]); // 获取轮廓外接矩形
    //     rectangle(result, rect, Scalar(255), 2); // 在原图上绘制矩形以显示分割的数字
    // }

    // imshow("Original Image", open);
    // imshow("Canny Edges", edges);
    // imshow("Separated Digits", result);

    //-------------------------------------------------------------------------------------

    return open;
}
int MainWindow::PixelCounter(Mat open, int ee)
{
    int ss = 0; // 初始化 ss 为 0
    int ww=0;
    for (int i = 0; i < open.rows; i++) { // 遍历行
        for (int n = 0; n < open.cols; n++) { // 遍历列
                if (open.at<uchar>(i, n) == 0) { // 如果像素值为 0
                    ss++;
                }
                else if (open.at<uchar>(i, n) != 0) { // 如果像素值不为 0
                   ww++;
                }

        }
    }
    if(ee==2)
    return ss;
    else if(ee==1)
        return ww;
}
Mat MainWindow::Horizon_Cut(Mat image){
    Mat temp = image.clone();
    int rows = temp.rows;
    int cols = temp.cols;

    QVector<int> white_n;
    for(int row = 0;row < rows;row++){
        int tem = 0;
        for(int col = 0;col < cols;col++){
            if(temp.at<uchar>(row, col)  > 0){
                tem++;
            }
        }
        white_n.append(tem);
    }

    int mid = 0;
    for(int i = 0;i < rows/2;i++){
        mid += white_n[i];
    }
    mid = mid/(rows/2 + 1);

    int i_0;
    int i_1;
    for(int i = rows/2 ;i >= 2; i--){
        if(white_n[i] < mid){
            i_0 = i;
            break;
        }
    }
    for(int i = rows/2;i < rows; i++){
        if(white_n[i] < mid){
            i_1 = i;
            break;
        }
    }
    Mat t_est = temp(Range(i_0,i_1),Range(0,cols));


    return t_est;
}


QVector<QVector<int> > MainWindow::Remove_Vertial_Border(Mat image)
{
Mat deeo=image.clone();
    cv::Mat outputImage;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(6, 1));
    cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1,5));
    cv::dilate(image, image, kernel);
    cv::erode(image, image, kernel2);
cv::dilate(image, image, kernel2);


    imshow("deeo2",image);
    //这里是使用了遍历行查找存在的黑-》白和白-》黑的区间来分割，虽然我后来觉得不好
    Mat temp = image.clone();
    int rows = temp.rows;
    int cols = temp.cols;

    QVector<int> white_n;
    for(int col = 0;col < cols;col++){
        int tem = 0;
        for(int row = 0;row < rows;row++){
            if(temp.at<uchar>(row, col)  > 0){
                tem++;
            }
        }
        white_n.append(tem);
    }
    QVector<QVector<int> > region1;
    QVector<int> reg;
    int flag = 0;
    if(white_n[0] != 0){
        reg.append(0);
    }
    for(int i = 0;i<cols - 1;i++){

        if(white_n[i] ==0 && white_n[i + 1] !=0){
            reg.append(i);
        }
        if(white_n[i] !=0 && white_n[i + 1] ==0){
            reg.append(i + 1);
        }
        if(reg.size() == 2){
            if(reg[1] - reg[0] > 8){
                region1.append(reg);
                reg.clear();
            }else{
                reg.clear();
            }
        }

        if(reg.size()==1&&i==cols-2)
        {
            if(cols-1 - reg[0] > 8){
                reg.append(cols-1);
                region1.append(reg);
                reg.clear();
            }else{
                reg.clear();
            }
        }

    }

    auto t=region1;
    int j = 0;
    for (int i = 0; i < t.size(); i++)
    {
        Mat str = deeo(Range(0,deeo.rows),Range(t[i][0],t[i][1]));

        imshow(to_string(i),str);

        j++;
        QString t_s = QString::number(j);
        string s = string((const char *)t_s.toLocal8Bit());

        int width = str.cols;
        int height = str.rows;
        int Sizeh = 0;
        int Sizew = 0;
        if(height>width)
            Sizew=(height-width)/2;
        // 添加黑色边框
        Mat ts=str.clone();
        copyMakeBorder(ts,ts, Sizeh, Sizeh, Sizew, Sizew, BORDER_CONSTANT, Scalar(0));

int whiteArea = countNonZero(ts); // 统计白色区域的像素个数
        if(whiteArea>1000)
        imwrite("C:/opencv/save/save"+s+".jpg",ts);
    }
    return region1;



}

vector<Rect>MainWindow::Remove_cahr(Mat image,Mat imag)
{


    vector<vector<Point>> contours;

    findContours(image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    drawContours(imag, contours, -1, Scalar(255, 0, 0), 2);
    vector<Rect> filteredRects;  // 存储符合条件的矩形的容器

    for (int i = 0; i < contours.size(); i++) {
        Rect rect = boundingRect(contours[i]);
        if(rect.height * rect.width > 80 && rect.height > rect.width * 1.3 && rect.height < rect.width * 5) {
            // 将符合条件的矩形存入容器
            filteredRects.push_back(rect);
        }
    }

    // 使用lambda表达式来定义自定义排序规则，按照Rect的x值进行排序
    sort(filteredRects.begin(), filteredRects.end(), [](const Rect& a, const Rect& b) {
        return a.x < b.x;
    });

    // 现在，filteredRects中存储了所有符合条件的矩形对象，并按照x值进行排序

    for (const Rect& rect : filteredRects) {
        // 获取当前矩形的坐标和尺寸
        int x = rect.x;
        int y = rect.y;
        int width = rect.width;
        int height = rect.height;

        // 确保矩形在图像范围内
        x = std::max(0, x);
        y = std::max(0, y);
        width = std::min(width, image.cols - x);
        height = std::min(height, image.rows - y);

        // 从原图像中提取当前矩形区域
        Mat roi = image(Rect(x, y, width, height));
        Mat roii=roi.clone();
        int Sizeh = 0;
int Sizew = 7;
        if(height>width)
    Sizew=(height-width)/2;
        // 添加黑色边框

        copyMakeBorder(roii, roii, Sizeh, Sizeh, Sizew, Sizew, BORDER_CONSTANT, Scalar(0));


        // 显示提取的矩形区域
        imshow("ROI"+to_string(j), roii);
        j++;
        // 对提取的矩形区域进行其他操作
        imwrite("C:/opencv/save/save"+to_string(j)+".jpg",roii);
        //waitKey(0);
    }



    imshow("chontou",image);
    imshow("contoures",imag);










    return filteredRects;
}

QString MainWindow::chuan(const QString& folderPath, int maxFiles)
{
    QStringList jpgFiles;
    QDir dir(folderPath);
    double mx=0;
    QString mn;
    QString ed=":";
    // 设置过滤以仅获取 .jpg 文件
    dir.setNameFilters(QStringList() << "*.jpg");
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot); // 排除 . 和 ..

    // 遍历文件夹
    const auto fileInfos = dir.entryInfoList();
    for (const QFileInfo& fileInfo : fileInfos) {
        // 将文件名添加到列表中
        jpgFiles.append(fileInfo.fileName());

        QString filePath = folderPath + "/" + fileInfo.fileName();

        // 读取图像并处理
        Mat image1 = imread(filePath.toStdString());
        if (image1.empty()) {
            qDebug()<<"aaaa1";
            continue;
        }



        //-------------------------------------------------------------------遍历模版文件---------------------------------------------------------------------
        QStringList Files2;
        QDir dir2("D:/VehicleLicense/VehicleLicense/Data");

        QStringList folderList2 = dir2.entryList(QDir::Dirs | QDir::NoDotAndDotDot); // 获取文件夹列表，不包括"."和".."
        // 遍历文件夹
        const auto fileInfos2 = dir2.entryInfoList();
        for (const QFileInfo& fileInfo2 : fileInfos2) {
            // 将文件名添加到列表中
            Files2.append(fileInfo2.fileName());


            QString filePath2 = "D:/VehicleLicense/VehicleLicense/Data/" + fileInfo2.fileName();
            qDebug()<<filePath2;
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~遍历文件中的图片~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            QStringList jpgFiles3;
            QDir dir3(filePath2);

            // 设置过滤以仅获取 .jpg 文件
            dir3.setNameFilters(QStringList() << "*.jpg");
            dir3.setFilter(QDir::Files | QDir::NoDotAndDotDot); // 排除 . 和 ..

            // 遍历文件夹
            const auto fileInfos3 = dir3.entryInfoList();

            for (const QFileInfo& fileInfo3 : fileInfos3) {
                // 将文件名添加到列表中
                jpgFiles3.append(fileInfo3.fileName());
                // 如果达到最大文件数，则停止
                if (jpgFiles3.size() >= maxFiles) {
                    break;
                }
                QString filePath3 = filePath2 + "/" + fileInfo3.fileName();
                   qDebug()<<filePath3;
                // 读取图像并处理
                Mat image2 = imread(filePath3.toStdString());
                if (image2.empty()) {
                    qDebug()<<"aaaa3";
                    continue;
                }
                double mxx=do_read(image2,image1);
                qDebug()<<mxx;
                if(mxx>mx)
                {

                    mx=mxx;
                    mn=fileInfo2.fileName();
                    qDebug()<<"aaaccc";
                }


            }
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        }
        //----------------------------------------------------------------------------------------------------------------------------------------------
        if(ed==":")
        {
           mn = switchFunction( mn.toStdString());

        }
        ed=ed+mn;
        mn=NULL;
        mx=0;

}

    return ed;
}


double MainWindow::do_read(Mat temo,Mat temp){
    int height = temo.size().height;
    int width = temo.size().width;

    Mat image = temp.clone();
    cv::resize(image, image, cv::Size(width, height)); // 将temp图片缩放到和temo相同的尺寸
    imshow("sf",image);
    //waitKey(0);
    Mat result;

    matchTemplate(image, temo, result, cv::TM_CCOEFF);
    //求解最大值
    double minValue, maxValue;
    Point minLocation, maxLocation;
    Point matchLocation;
    minMaxLoc(result, &minValue, &maxValue, &minLocation, &maxLocation);
    return maxValue;
}

QString MainWindow::switchFunction(const std::string& key) {
    static const std::unordered_map<std::string, std::string> map = {
        {"A", "A"},
        {"B", "B"},
        {"C", "C"},
        {"D", "D"},
        {"E", "E"},
        {"F", "F"},
        {"G", "G"},
        {"H", "H"},
        {"I", "I"},
        {"J", "J"},
        {"K", "K"},
        {"L", "L"},
        {"M", "M"},
        {"N", "N"},
        {"O", "O"},
        {"P", "P"},
        {"Q", "Q"},
        {"R", "R"},
        {"S", "S"},
        {"T", "T"},
        {"U", "U"},
        {"V", "V"},
        {"W", "W"},
        {"X", "X"},
        {"Y", "Y"},
        {"Z", "Z"},
        {"yun", "云"},
        {"cuan", "川"},
        {"hei", "黑"},
        {"zhe", "浙"},
        {"ning", "宁"},
        {"jin", "津"},
        {"gan", "赣"},
        {"hu", "沪"},
        {"liao", "辽"},
        {"jl", "吉"},
        {"qing", "青"},
        {"zang", "藏"},
        {"e1", "鄂"},
        {"meng", "蒙"},
        {"gan1", "甘"},
        {"qiong", "琼"},
        {"shan", "陕"},
        {"min", "闽"},
        {"su", "苏"},
        {"xin", "新"},
        {"wan", "皖"},
        {"jing", "京"},
        {"xiang", "湘"},
        {"gui", "贵"},
        {"yu1", "渝"},
        {"yu", "豫"},
        {"ji", "冀"},
        {"yue", "粤"},
        {"gui1", "桂"},
        {"sx", "晋"},
        {"lu", "鲁"},
        {"0", "0"},
        {"1", "1"},
        {"2", "2"},
        {"3", "3"},
        {"4", "4"},
        {"5", "5"},
        {"6", "6"},
        {"7", "7"},
        {"8", "8"},
        {"9", "9"}
    };

    auto it = map.find(key);
    if (it != map.end()) {

        return QString::fromStdString(it->second);
    } else {
        return "Key not found";
    }
}
Mat MainWindow::cutCut(Mat gray)
{Mat deeo=gray.clone();

    cv::Mat outputImage;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2,2));
    cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1,2));
    cv::erode(gray, gray, kernel2);
    cv::morphologyEx(gray,gray, cv::MORPH_CLOSE, kernel);
    imshow("deeo1",gray);
    // 二值化处理
    cv::Mat thresh;
    cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY);

    // 查找连通域
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 筛选面积在20到100之间的连通域
    std::vector<std::vector<cv::Point>> filtered_contours;
    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);
        if (area >= 450 && area <= 12000) {
            filtered_contours.push_back(contour);
        }
    }

    // 找出最左边和最右边的两个连通域
    std::sort(filtered_contours.begin(), filtered_contours.end(), [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
        return cv::minAreaRect(a).center.x < cv::minAreaRect(b).center.x;
    });

    std::vector<std::vector<cv::Point>> ll=filtered_contours;
    std::sort(ll.begin(), ll.end(), [](const std::vector<cv::Point>& a, const std::vector<cv::Point>& b) {
        return cv::minAreaRect(a).center.y < cv::minAreaRect(b).center.y;
    });




    cv::Rect leftmost_rect = cv::boundingRect(filtered_contours[0]);
    cv::Rect rightmost_rect = cv::boundingRect(filtered_contours[filtered_contours.size() - 1]);

    cv::Rect leftmost_rec = cv::boundingRect(ll[0]);
    cv::Rect rightmost_rec = cv::boundingRect(ll[ll.size() - 1]);

    // 获取最左连通域的左上角和最右连通域的右下角位置
    cv::Point left_top(leftmost_rect.x, leftmost_rec.y-4);
    cv::Point right_bottom(rightmost_rect.x + rightmost_rect.width,rightmost_rec.y + rightmost_rec.height );

    // 计算提取区域的矩形框
    cv::Rect extract_rect(left_top, right_bottom);

    // 使用矩形框在灰度图像上进行裁剪
    cv::Mat extracted_region = deeo(extract_rect).clone();
    int newWidth = extracted_region.cols + 2;
    int newHeight = extracted_region.rows + 2;

    // 创建一个新的图像，初始值为黑色
    cv::Mat region = cv::Mat::zeros(newHeight, newWidth, extracted_region.type());

    // 将原始图像复制到新图像的边界
    extracted_region.copyTo(region(cv::Rect(1, 1, extracted_region.cols, extracted_region.rows)));

    // 显示结果图像
    cv::imshow("Extracted Region", region);

    return region;
}






