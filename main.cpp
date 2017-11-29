#include <QDebug>
#include <QVector>
#include <QRect>
#include <QImage>
#include <QApplication>
#include <QWidget>
#include <QScreen>
#include <QDesktopWidget>
#include <QThread>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef __linux
    #include <X11/extensions/XTest.h>
#else
    #include <windows.h>
#endif
//std::string image_window = "Source Image"; //test
//std::string result_window = "Result window"; //test
<<<<<<< HEAD
<<<<<<< HEAD
int screen_x = 0, screen_y = 0, screen_w = 640, screen_h = 480;
int mouse_x = 0, mouse_y = 0;
int cali_roll_request = 0, maki_request = 0, onigiri_request = 0, salmon_roll_request = 0, shrimp_request = 0, unagi_request = 0, dragon_request = 0, combo_request = 0;
int order_count = 0;
int rice_count = 10, roe_count = 10, nori_count = 10, salmon_count = 5, shrimp_count = 5, unagi_count = 5;
int dish_y = 0, dish_1x = 0, dish_2x = 0, dish_3x = 0, dish_4x = 0, dish_5x = 0, dish_6x = 0;
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
//std::string image_window = "Source Image"; //test
//std::string result_window = "Result window"; //test
>>>>>>> parent of 97edcd1... nameconvention
=======
//std::string image_window = "Source Image"; //test
//std::string result_window = "Result window"; //test
>>>>>>> parent of 97edcd1... nameconvention
=======
//std::string image_window = "Source Image"; //test
//std::string result_window = "Result window"; //test
>>>>>>> parent of 97edcd1... nameconvention
int screenX = 0, screenY = 0, screenW = 640, screenH = 480;
int mouseX = 0, mouseY = 0;
int cRollRequest = 0, makeRequest = 0, onigiriRequest = 0, sRollRequest = 0, shrimpRequest = 0, unagiRequest = 0, dragonRequest = 0, comboRequest = 0;
int orderCount = 0;
int riceCount = 10, roeCount = 10, noriCount = 10, salmonCount = 5, shrimpCount = 5, unagiCount = 5;
int dishY = 0, dish1X = 0, dish2X = 0, dish3X = 0, dish4X = 0, dish5X = 0, dish6X = 0;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
bool failed = false;
bool win = false;
=======
boolean failed = false;
boolean win = false;
std::string path = "X://GitHub/Project/SushiChef/images/";
>>>>>>> parent of 97edcd1... nameconvention
=======
boolean failed = false;
boolean win = false;
std::string path = "X://GitHub/Project/SushiChef/images/";
>>>>>>> parent of 97edcd1... nameconvention
=======
boolean failed = false;
boolean win = false;
std::string path = "X://GitHub/Project/SushiChef/images/";
>>>>>>> parent of 97edcd1... nameconvention
=======
boolean failed = false;
boolean win = false;
std::string path = "X://GitHub/Project/SushiChef/images/";
>>>>>>> parent of 97edcd1... nameconvention

class Match : public QRect{
    public:
        double matching_score;
};

QVector<Match> doMatching(cv::Mat img, cv::Mat templ, int max_matches, float matching_percent = 0.95) {

//    cv::namedWindow( image_window, CV_WINDOW_AUTOSIZE ); //test
//    cv::namedWindow( result_window, CV_WINDOW_AUTOSIZE ); //test

    cv::Mat result;
//    cv::Mat img_display; //test
    QVector<Match> matches;
//    img.copyTo( img_display ); //test

    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    result.create( result_rows, result_cols, CV_32FC1 );
    matchTemplate( img, templ, result, 5);
    while (true){

        double min_val; double max_val; cv::Point min_loc; cv::Point max_loc; cv::Point match_loc;
        minMaxLoc( result, &min_val, &max_val, &min_loc, &max_loc, cv::Mat() );
        match_loc = max_loc;

        if((max_val > matching_percent) && (matches.size() != max_matches)){  //when the match has a value higher than 0.XX and matches to find hasnt been reached
            Match new_match;
            new_match.setLeft(match_loc.x);
            new_match.setTop(match_loc.y);
            new_match.setWidth(templ.cols);
            new_match.setHeight(templ.rows);
            new_match.matching_score = max_val;
            matches.append(new_match);

            qDebug() << "Matching number:" << matches.size() << new_match.left() << new_match.top() << new_match.matching_score;
            floodFill(result, cv::Point(match_loc.x,match_loc.y), cv::Scalar(0,0,0), 0, cv::Scalar(10,10,10));
//            rectangle( img_display, match_loc, cv::Point( match_loc.x + templ.cols , match_loc.y + templ.rows ), cv::Scalar::all(0), 2, 8, 0 ); //test
//            imshow( image_window, img_display ); //test
//            imshow( result_window, result ); //test
            cv::waitKey(0); //Check Match by Match by pressing a button
        }
        else
        {
            if (matches.size() == max_matches){
                qDebug() << matches.size() << "matches found, exit searching";
            }
            else {
            // qDebug() << "no more matches";
             }
        break;
        }
    }
    return matches;
}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef __linux
<<<<<<< HEAD
    std::string file_type = ".PNG";
=======
    std::string endung = ".PNG";
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
    std::string path = "/media/jianan/0AD4D5A9D4D59773/Projects/SushiChef-master/images/";

    void mouseClick(int x, int y){
        QCursor mouse;
<<<<<<< HEAD
        mouse.setPos(x + screen_x,y + screen_y);
=======
        mouse.setPos(x + screenX,y + screenY);
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad

        Display *dpy = XOpenDisplay (NULL);
        XTestFakeButtonEvent (dpy, 1, True,  0);
        XTestFakeButtonEvent (dpy, 1, False, 0);
        XCloseDisplay (dpy);
    }
#else
<<<<<<< HEAD
    std::string file_type = ".png";
    std::string path = "X://GitHub/Project/SushiChef/images/";
    void mouseClick(int x, int y){
        QCursor mouse;
        mouse.setPos(x + screen_x,y + screen_y);
=======
    std::string endung = ".png"
    std::string path = "X://GitHub/Project/SushiChef/images/";
    void mouseClick(int x, int y){
        QCursor mouse;
        mouse.setPos(x + screenX,y + screenY);
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 1, 1, 0, 0);
    }
#endif
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention

cv::Mat screenshotRect(int x, int y, int w, int h) {
    QRect shot_rect(x, y, w, h);
    QImage desk = qApp->screens().at(0)->grabWindow(
    QDesktopWidget().winId(),
    shot_rect.left(),
    shot_rect.top(),
    shot_rect.width(),
    shot_rect.height()).toImage();
    desk = desk.convertToFormat( QImage::Format_RGB888 );
    desk = desk.rgbSwapped();
    return cv::Mat( desk.height(), desk.width(),
                    CV_8UC3,
                    const_cast<uchar*>(desk.bits()),
                    static_cast<size_t>(desk.bytesPerLine())
                    ).clone();
}

cv::Mat screenshot() {
    QImage desk = qApp->screens().at(0)->grabWindow(
    QDesktopWidget().winId()
    ).toImage();
    desk = desk.convertToFormat( QImage::Format_RGB888 );
    desk = desk.rgbSwapped();
    return cv::Mat( desk.height(), desk.width(),
                    CV_8UC3,
                    const_cast<uchar*>(desk.bits()),
                    static_cast<size_t>(desk.bytesPerLine())
                    ).clone();
}

cv::Mat screenshotGame() {
    QRect shot_rect(screenX, screenY, screenW, screenH);
   // qDebug() << screenX << screenY << screenW << screenH;
    QImage desk = qApp->screens().at(0)->grabWindow(
    QDesktopWidget().winId(),
    shot_rect.left(),
    shot_rect.top(),
    shot_rect.width(),
    shot_rect.height()).toImage();
    desk = desk.convertToFormat( QImage::Format_RGB888 );
    desk = desk.rgbSwapped();
    return cv::Mat( desk.height(), desk.width(),
                    CV_8UC3,
                    const_cast<uchar*>(desk.bits()),
                    static_cast<size_t>(desk.bytesPerLine())
                    ).clone();
}

void getPlayScreen() {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    QVector<Match> matches = doMatching(screenshot(), cv::imread(path + "topLeft" + file_type, 1), 1);
=======
    QVector<Match> matches = doMatching(screenshot(), cv::imread(path + "topLeft" + endung, 1), 1);
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
    QVector<Match> matches = doMatching(screenshot(), cv::imread(path + "topLeft.png", 1), 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
    QVector<Match> matches = doMatching(screenshot(), cv::imread(path + "topLeft.png", 1), 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
    QVector<Match> matches = doMatching(screenshot(), cv::imread(path + "topLeft.png", 1), 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
    QVector<Match> matches = doMatching(screenshot(), cv::imread(path + "topLeft.png", 1), 1);
>>>>>>> parent of 97edcd1... nameconvention
    if (matches.size() > 0) {
        screenX = matches[0].left();
        screenY = matches[0].top();
    } else {
        qDebug() << "Sushi Go Round not found";
        exit(0);
    }
}

void waitPosImage(std::string templName, int max_matches) {
    QVector<Match> matches;
    do {
        QVector<Match> matches_temp = doMatching(screenshotGame(), cv::imread(path + templName), max_matches);
        matches = matches_temp;
    } while(matches.size() < 1);
    mouseX = matches[0].left();
    mouseY = matches[0].top();
}

void waitPosImageClick(std::string templName, int max_matches, float matching_percent = 0.95) {
    QVector<Match> matches;
    do {
        QVector<Match> matches_temp = doMatching(screenshotGame(), cv::imread(path + templName), max_matches, matching_percent);
        matches = matches_temp;
    } while(matches.size() < 1);
    qDebug() << "click on" << QString::fromStdString(templName)  << matches[0].left() << matches[0].top();
    mouseClick(matches[0].left(), matches[0].top());
    QThread::msleep(10);
}

void start() {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    waitPosImageClick("playButton" + file_type, 1);
    waitPosImageClick("continue" + file_type, 1);
    waitPosImageClick("continue2" + file_type, 1);
    waitPosImageClick("skip" + file_type, 1);
    waitPosImageClick("continue" + file_type, 1);
=======
    waitPosImageClick("playButton" + endung, 1);
    waitPosImageClick("continue" + endung, 1);
    waitPosImageClick("continue2" + endung, 1);
    waitPosImageClick("skip" + endung, 1);
    waitPosImageClick("continue" + endung, 1);
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
    waitPosImageClick("playButton.png", 1);
    waitPosImageClick("continue.png", 1);
    waitPosImageClick("continue2.png", 1);
    waitPosImageClick("skip.png", 1);
    waitPosImageClick("continue.png", 1);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
}

void winCheck() {
   cv::Mat screen = screenshotGame();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
   QVector<Match> failed_match = doMatching(screen, cv::imread(path + "failed" + file_type), 6);
   QVector<Match> win_match = doMatching(screen, cv::imread(path + "win" + file_type), 6);
   if (failed_match.size() == 1) {
=======
   QVector<Match> failedMatch = doMatching(screen, cv::imread(path + "failed" + endung), 6);
   QVector<Match> winMatch = doMatching(screen, cv::imread(path + "win" + endung), 6);
   if (failedMatch.size() == 1) {
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
   QVector<Match> failedMatch = doMatching(screen, cv::imread(path + "failed.png"), 6);
   QVector<Match> winMatch = doMatching(screen, cv::imread(path + "win.png"), 6);
   if (failedMatch.size() == 1) {
>>>>>>> parent of 97edcd1... nameconvention
=======
   QVector<Match> failedMatch = doMatching(screen, cv::imread(path + "failed.png"), 6);
   QVector<Match> winMatch = doMatching(screen, cv::imread(path + "win.png"), 6);
   if (failedMatch.size() == 1) {
>>>>>>> parent of 97edcd1... nameconvention
=======
   QVector<Match> failedMatch = doMatching(screen, cv::imread(path + "failed.png"), 6);
   QVector<Match> winMatch = doMatching(screen, cv::imread(path + "win.png"), 6);
   if (failedMatch.size() == 1) {
>>>>>>> parent of 97edcd1... nameconvention
=======
   QVector<Match> failedMatch = doMatching(screen, cv::imread(path + "failed.png"), 6);
   QVector<Match> winMatch = doMatching(screen, cv::imread(path + "win.png"), 6);
   if (failedMatch.size() == 1) {
>>>>>>> parent of 97edcd1... nameconvention
       failed = true;
   }
   if (winMatch.size() == 1) {
       win = true;
   }
}

void getDishesPos() {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        QVector<Match> table = doMatching(screenshotGame(), cv::imread(path + "table" + file_type), 6);
=======
        QVector<Match> table = doMatching(screenshotGame(), cv::imread(path + "table" + endung), 6);
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
        QVector<Match> table = doMatching(screenshotGame(), cv::imread(path + "table.png"), 6);
>>>>>>> parent of 97edcd1... nameconvention
=======
        QVector<Match> table = doMatching(screenshotGame(), cv::imread(path + "table.png"), 6);
>>>>>>> parent of 97edcd1... nameconvention
=======
        QVector<Match> table = doMatching(screenshotGame(), cv::imread(path + "table.png"), 6);
>>>>>>> parent of 97edcd1... nameconvention
=======
        QVector<Match> table = doMatching(screenshotGame(), cv::imread(path + "table.png"), 6);
>>>>>>> parent of 97edcd1... nameconvention
        if (table.size() == 6) {
            dishY = table[0].top();
            dish1X = table[0].left() + 40;
            dish2X = table[1].left() + 40;
            dish3X = table[2].left() + 40;
            dish4X = table[3].left() + 40;
            dish5X = table[4].left() + 40;
            dish6X = table[5].left() + 40;
        }
        qDebug() << "getting dishes"<< dishY << dish1X << dish2X << dish3X << dish4X << dish5X << dish6X;
}

void getDishes() {
    qDebug() << "getting dishes"<< dishY << dish1X << dish2X << dish3X << dish4X << dish5X << dish6X;
    mouseClick(dish1X, dishY);
    mouseClick(dish2X, dishY);
    mouseClick(dish3X, dishY);
    mouseClick(dish4X, dishY);
    mouseClick(dish5X, dishY);
    mouseClick(dish6X, dishY);
}

void getOrder(int minOrders = 1) {
    do {
        qDebug() << "getting Orders";
        cv::Mat screen = screenshotGame();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        QVector<Match> cali_roll_requestMatch = doMatching(screen, cv::imread(path + "cali_roll_request" + file_type), 6);
        QVector<Match> maki_requestMatch = doMatching(screen, cv::imread(path + "maki_request" + file_type), 6);
        QVector<Match> onigiri_requestMatch = doMatching(screen, cv::imread(path + "onigiri_request" + file_type), 6);
        QVector<Match> salmon_roll_requestMatch = doMatching(screen, cv::imread(path + "salmon_roll_request" + file_type), 6);
        QVector<Match> shrimp_requestMatch = doMatching(screen, cv::imread(path + "shrimp_request" + file_type), 6);
        QVector<Match> unagi_requestMatch = doMatching(screen, cv::imread(path + "unagi_request" + file_type), 6);
        QVector<Match> dragon_requestMatch = doMatching(screen, cv::imread(path + "dragon_request" + file_type), 6);
        QVector<Match> combo_requestMatch = doMatching(screen, cv::imread(path + "combo_request" + file_type), 6);
        cali_roll_request = cali_roll_requestMatch.size(), maki_request = maki_requestMatch.size(), shrimp_request = shrimp_requestMatch.size(),
        onigiri_request = onigiri_requestMatch.size(), salmon_roll_request = salmon_roll_requestMatch.size(), unagi_request = unagi_requestMatch.size(),
        dragon_request = dragon_requestMatch.size(), combo_request = combo_requestMatch.size();
        order_count = cali_roll_requestMatch.size() + maki_requestMatch.size() + onigiri_requestMatch.size() + salmon_roll_requestMatch.size() +
        shrimp_requestMatch.size() + unagi_requestMatch.size() + dragon_requestMatch.size() + combo_requestMatch.size();
=======
        QVector<Match> cRollRequestMatch = doMatching(screen, cv::imread(path + "cRollRequest" + endung), 6);
        QVector<Match> makeRequestMatch = doMatching(screen, cv::imread(path + "makeRequest" + endung), 6);
        QVector<Match> onigiriRequestMatch = doMatching(screen, cv::imread(path + "onigiriRequest" + endung), 6);
        QVector<Match> sRollRequestMatch = doMatching(screen, cv::imread(path + "sRollRequest" + endung), 6);
        QVector<Match> shrimpRequestMatch = doMatching(screen, cv::imread(path + "shrimpRequest" + endung), 6);
        QVector<Match> unagiRequestMatch = doMatching(screen, cv::imread(path + "unagiRequest" + endung), 6);
        QVector<Match> dragonRequestMatch = doMatching(screen, cv::imread(path + "dragonRequest" + endung), 6);
        QVector<Match> comboRequestMatch = doMatching(screen, cv::imread(path + "comboRequest" + endung), 6);
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        QVector<Match> cRollRequestMatch = doMatching(screen, cv::imread(path + "cRollRequest.png"), 6);
        QVector<Match> makeRequestMatch = doMatching(screen, cv::imread(path + "makeRequest.png"), 6);
        QVector<Match> onigiriRequestMatch = doMatching(screen, cv::imread(path + "onigiriRequest.png"), 6);
        QVector<Match> sRollRequestMatch = doMatching(screen, cv::imread(path + "sRollRequest.png"), 6);
        QVector<Match> shrimpRequestMatch = doMatching(screen, cv::imread(path + "shrimpRequest.png"), 6);
        QVector<Match> unagiRequestMatch = doMatching(screen, cv::imread(path + "unagiRequest.png"), 6);
        QVector<Match> dragonRequestMatch = doMatching(screen, cv::imread(path + "dragonRequest.png"), 6);
        QVector<Match> comboRequestMatch = doMatching(screen, cv::imread(path + "comboRequest.png"), 6);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        cRollRequest = cRollRequestMatch.size(), makeRequest = makeRequestMatch.size(), shrimpRequest = shrimpRequestMatch.size(),
        onigiriRequest = onigiriRequestMatch.size(), sRollRequest = sRollRequestMatch.size(), unagiRequest = unagiRequestMatch.size(),
        dragonRequest = dragonRequestMatch.size(), comboRequest = comboRequestMatch.size();
        orderCount = cRollRequestMatch.size() + makeRequestMatch.size() + onigiriRequestMatch.size() + sRollRequestMatch.size() +
        shrimpRequestMatch.size() + unagiRequestMatch.size() + dragonRequestMatch.size() + comboRequestMatch.size();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        getDishes();
        winCheck();
    } while (orderCount < minOrders && win == false && failed == false);
}

void orderSupplies() {
    qDebug() << "order supplies";
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    if (rice_count < 2) {
        waitPosImageClick("order" + file_type, 1);
        waitPosImageClick("riceMenu" + file_type, 1);
        mouseClick(screen_x, screen_y);
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
    if (riceCount < 2) {
        waitPosImageClick("order.png", 1);
        waitPosImageClick("riceMenu.png", 1);
        mouseClick(screenX, screenY);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        QThread::msleep(50);
        waitPosImageClick("riceOrder.png", 1);
        waitPosImageClick("standardDelivery.png", 1);
        riceCount = riceCount + 10;
    }
    if (roeCount < 2) {
        waitPosImageClick("order.png", 1);
        waitPosImageClick("toppingMenu.png", 1, 0.98);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("roeOrder.png", 1);
        waitPosImageClick("standardDelivery.png", 1);
        roeCount = roeCount + 10;
    }
    if (noriCount < 1) {
        waitPosImageClick("order.png", 1);
        waitPosImageClick("toppingMenu.png", 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("noriOrder.png", 1);
        waitPosImageClick("standardDelivery.png", 1);
        noriCount = noriCount + 10;
    }
    if (salmonCount < 2) {
        waitPosImageClick("order.png", 1);
        waitPosImageClick("toppingMenu.png", 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("salmonOrder.png", 1, 0.98);
        waitPosImageClick("standardDelivery.png", 1);
        salmonCount = salmonCount + 5;
    }
    if (shrimpCount < 2) {
        waitPosImageClick("order.png", 1);
        waitPosImageClick("toppingMenu.png", 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("shrimpOrder.png", 1, 0.98);
        waitPosImageClick("standardDelivery.png", 1);
        shrimpCount = shrimpCount + 5;
    }
    if (unagiCount < 2) {
        waitPosImageClick("order.png", 1);
        waitPosImageClick("toppingMenu.png", 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        waitPosImageClick("unagiOrder" + file_type, 1, 0.98);
        waitPosImageClick("standardDelivery" + file_type, 1);
        unagi_count = unagi_count + 5;
=======
    if (riceCount < 2) {
        waitPosImageClick("order" + endung, 1);
        waitPosImageClick("riceMenu" + endung, 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("riceOrder" + endung, 1);
        waitPosImageClick("standardDelivery" + endung, 1);
        riceCount = riceCount + 10;
    }
    if (roeCount < 2) {
        waitPosImageClick("order" + endung, 1);
        waitPosImageClick("toppingMenu" + endung, 1, 0.98);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("roeOrder" + endung, 1);
        waitPosImageClick("standardDelivery" + endung, 1);
        roeCount = roeCount + 10;
    }
    if (noriCount < 1) {
        waitPosImageClick("order" + endung, 1);
        waitPosImageClick("toppingMenu" + endung, 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("noriOrder" + endung, 1);
        waitPosImageClick("standardDelivery" + endung, 1);
        noriCount = noriCount + 10;
    }
    if (salmonCount < 2) {
        waitPosImageClick("order" + endung, 1);
        waitPosImageClick("toppingMenu" + endung, 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("salmonOrder" + endung, 1, 0.98);
        waitPosImageClick("standardDelivery" + endung, 1);
        salmonCount = salmonCount + 5;
    }
    if (shrimpCount < 2) {
        waitPosImageClick("order" + endung, 1);
        waitPosImageClick("toppingMenu" + endung, 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("shrimpOrder" + endung, 1, 0.98);
        waitPosImageClick("standardDelivery" + endung, 1);
        shrimpCount = shrimpCount + 5;
    }
    if (unagiCount < 2) {
        waitPosImageClick("order" + endung, 1);
        waitPosImageClick("toppingMenu" + endung, 1);
        mouseClick(screenX, screenY);
        QThread::msleep(50);
        waitPosImageClick("unagiOrder" + endung, 1, 0.98);
        waitPosImageClick("standardDelivery" + endung, 1);
        unagiCount = unagiCount + 5;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
        waitPosImageClick("unagiOrder.png", 1, 0.98);
        waitPosImageClick("standardDelivery.png", 1);
        unagiCount = unagiCount + 5;
>>>>>>> parent of 97edcd1... nameconvention
=======
        waitPosImageClick("unagiOrder.png", 1, 0.98);
        waitPosImageClick("standardDelivery.png", 1);
        unagiCount = unagiCount + 5;
>>>>>>> parent of 97edcd1... nameconvention
=======
        waitPosImageClick("unagiOrder.png", 1, 0.98);
        waitPosImageClick("standardDelivery.png", 1);
        unagiCount = unagiCount + 5;
>>>>>>> parent of 97edcd1... nameconvention
=======
        waitPosImageClick("unagiOrder.png", 1, 0.98);
        waitPosImageClick("standardDelivery.png", 1);
        unagiCount = unagiCount + 5;
>>>>>>> parent of 97edcd1... nameconvention
    }
}

void makeSushi() {
    qDebug() << "making sushi";
    if (comboRequest > 0) {
        getDishes();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        for (int a = 0; a < combo_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("unagiDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("roeDesk" + file_type, 1);
            waitPosImageClick("salmonDesk" + file_type, 1);
            waitPosImageClick("shrimpDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 2, nori_count = nori_count -1, unagi_count = unagi_count - 1, salmon_count = salmon_count - 1, shrimp_count = shrimp_count - 1, roe_count = roe_count - 1;
=======
        for (int a = 0; a < comboRequest; a = a + 1) {
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("unagiDesk" + endung, 1);
            waitPosImageClick("noriDesk" + endung, 1);
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("roeDesk" + endung, 1);
            waitPosImageClick("salmonDesk" + endung, 1);
            waitPosImageClick("shrimpDesk" + endung, 1);
            waitPosImageClick("bambusRoll" + endung, 1);
            waitPosImage("bambusRollEmpty" + endung, 1);
            riceCount = riceCount - 2, noriCount = noriCount -1, unagiCount = unagiCount - 1, salmonCount = salmonCount - 1, shrimpCount = shrimpCount - 1, roeCount = roeCount - 1;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        for (int a = 0; a < comboRequest; a = a + 1) {
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("unagiDesk.png", 1);
            waitPosImageClick("noriDesk.png", 1);
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("roeDesk.png", 1);
            waitPosImageClick("salmonDesk.png", 1);
            waitPosImageClick("shrimpDesk.png", 1);
            waitPosImageClick("bambusRoll.png", 1);
            waitPosImage("bambusRollEmpty.png", 1);
            riceCount = riceCount - 2, noriCount = noriCount -1, unagiCount = unagiCount - 1, salmonCount = salmonCount - 1, shrimpCount = shrimpCount - 1, roeCount = roeCount - 1;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (dragonRequest > 0) {
        getDishes();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        for (int a = 0; a < dragon_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("unagiDesk" + file_type, 1);
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("roeDesk" + file_type, 1);
            waitPosImageClick("unagiDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 2, nori_count = nori_count -1, unagi_count = unagi_count - 2, roe_count = roe_count - 1;
=======
        for (int a = 0; a < dragonRequest; a = a + 1) {
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("unagiDesk" + endung, 1);
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("noriDesk" + endung, 1);
            waitPosImageClick("roeDesk" + endung, 1);
            waitPosImageClick("unagiDesk" + endung, 1);
            waitPosImageClick("bambusRoll" + endung, 1);
            waitPosImage("bambusRollEmpty" + endung, 1);
            riceCount = riceCount - 2, noriCount = noriCount -1, unagiCount = unagiCount - 2, roeCount = roeCount - 1;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        for (int a = 0; a < dragonRequest; a = a + 1) {
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("unagiDesk.png", 1);
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("noriDesk.png", 1);
            waitPosImageClick("roeDesk.png", 1);
            waitPosImageClick("unagiDesk.png", 1);
            waitPosImageClick("bambusRoll.png", 1);
            waitPosImage("bambusRollEmpty.png", 1);
            riceCount = riceCount - 2, noriCount = noriCount -1, unagiCount = unagiCount - 2, roeCount = roeCount - 1;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (unagiRequest > 0) {
        getDishes();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        for (int a = 0; a < unagi_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("unagiDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("unagiDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, unagi_count = unagi_count - 2;
=======
        for (int a = 0; a < unagiRequest; a = a + 1) {
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("unagiDesk" + endung, 1);
            waitPosImageClick("noriDesk" + endung, 1);
            waitPosImageClick("unagiDesk" + endung, 1);
            waitPosImageClick("bambusRoll" + endung, 1);
            waitPosImage("bambusRollEmpty" + endung, 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, unagiCount = unagiCount - 2;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        for (int a = 0; a < unagiRequest; a = a + 1) {
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("unagiDesk.png", 1);
            waitPosImageClick("noriDesk.png", 1);
            waitPosImageClick("unagiDesk.png", 1);
            waitPosImageClick("bambusRoll.png", 1);
            waitPosImage("bambusRollEmpty.png", 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, unagiCount = unagiCount - 2;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (shrimpRequest > 0) {
        getDishes();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        for (int a = 0; a < shrimp_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("shrimpDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("shrimpDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, shrimp_count = shrimp_count - 2;
=======
        for (int a = 0; a < shrimpRequest; a = a + 1) {
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("shrimpDesk" + endung, 1);
            waitPosImageClick("noriDesk" + endung, 1);
            waitPosImageClick("shrimpDesk" + endung, 1);
            waitPosImageClick("bambusRoll" + endung, 1);
            waitPosImage("bambusRollEmpty" + endung, 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, shrimpCount = shrimpCount - 2;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        for (int a = 0; a < shrimpRequest; a = a + 1) {
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("shrimpDesk.png", 1);
            waitPosImageClick("noriDesk.png", 1);
            waitPosImageClick("shrimpDesk.png", 1);
            waitPosImageClick("bambusRoll.png", 1);
            waitPosImage("bambusRollEmpty.png", 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, shrimpCount = shrimpCount - 2;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (sRollRequest > 0) {
        getDishes();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        for (int a = 0; a < salmon_roll_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("salmonDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("salmonDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, salmon_count = salmon_count - 2;
=======
        for (int a = 0; a < sRollRequest; a = a + 1) {
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("salmonDesk" + endung, 1);
            waitPosImageClick("noriDesk" + endung, 1);
            waitPosImageClick("salmonDesk" + endung, 1);
            waitPosImageClick("bambusRoll" + endung, 1);
            waitPosImage("bambusRollEmpty" + endung, 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, salmonCount = salmonCount - 2;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        for (int a = 0; a < sRollRequest; a = a + 1) {
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("salmonDesk.png", 1);
            waitPosImageClick("noriDesk.png", 1);
            waitPosImageClick("salmonDesk.png", 1);
            waitPosImageClick("bambusRoll.png", 1);
            waitPosImage("bambusRollEmpty.png", 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, salmonCount = salmonCount - 2;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (cRollRequest > 0) {
        getDishes();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        for (int a = 0; a < cali_roll_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("roeDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, roe_count = roe_count - 1;
=======
        for (int a = 0; a < cRollRequest; a = a + 1) {
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("noriDesk" + endung, 1);
            waitPosImageClick("roeDesk" + endung, 1);
            waitPosImageClick("bambusRoll" + endung, 1);
            waitPosImage("bambusRollEmpty" + endung, 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, roeCount = roeCount - 1;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        for (int a = 0; a < cRollRequest; a = a + 1) {
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("noriDesk.png", 1);
            waitPosImageClick("roeDesk.png", 1);
            waitPosImageClick("bambusRoll.png", 1);
            waitPosImage("bambusRollEmpty.png", 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, roeCount = roeCount - 1;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (makeRequest > 0) {
        getDishes();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        for (int a = 0; a < maki_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("roeDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("roeDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, roe_count = roe_count - 2;
=======
        for (int a = 0; a < makeRequest; a = a + 1) {
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("roeDesk" + endung, 1);
            waitPosImageClick("noriDesk" + endung, 1);
            waitPosImageClick("roeDesk" + endung, 1);
            waitPosImageClick("bambusRoll" + endung, 1);
            waitPosImage("bambusRollEmpty" + endung, 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, roeCount = roeCount - 2;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        for (int a = 0; a < makeRequest; a = a + 1) {
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("roeDesk.png", 1);
            waitPosImageClick("noriDesk.png", 1);
            waitPosImageClick("roeDesk.png", 1);
            waitPosImageClick("bambusRoll.png", 1);
            waitPosImage("bambusRollEmpty.png", 1);
            riceCount = riceCount - 1, noriCount = noriCount -1, roeCount = roeCount - 2;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (onigiriRequest > 0) {
        getDishes();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        for (int a = 0; a < onigiri_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 2, nori_count = nori_count -1;
=======
        for (int a = 0; a < onigiriRequest; a = a + 1) {
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("noriDesk" + endung, 1);
            waitPosImageClick("riceDesk" + endung, 1);
            waitPosImageClick("bambusRoll" + endung, 1);
            waitPosImage("bambusRollEmpty" + endung, 1);
            riceCount = riceCount - 2, noriCount = noriCount -1;
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
        for (int a = 0; a < onigiriRequest; a = a + 1) {
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("noriDesk.png", 1);
            waitPosImageClick("riceDesk.png", 1);
            waitPosImageClick("bambusRoll.png", 1);
            waitPosImage("bambusRollEmpty.png", 1);
            riceCount = riceCount - 2, noriCount = noriCount -1;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
=======
>>>>>>> parent of 97edcd1... nameconvention
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
        onigiriRequest = 0;
        makeRequest = 0;
        cRollRequest = 0;
        sRollRequest = 0;
        shrimpRequest = 0;
        unagiRequest = 0;
        dragonRequest = 0;
        comboRequest = 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getPlayScreen();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    doMatching(screenshotGame(), cv::imread(path + "topLeft" + file_type, 1), 1);
=======
    doMatching(screenshotGame(), cv::imread(path + "topLeft" + endung, 1), 1);
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
    doMatching(screenshotGame(), cv::imread(path + "topLeft.png", 1), 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
    doMatching(screenshotGame(), cv::imread(path + "topLeft.png", 1), 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
    doMatching(screenshotGame(), cv::imread(path + "topLeft.png", 1), 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
    doMatching(screenshotGame(), cv::imread(path + "topLeft.png", 1), 1);
>>>>>>> parent of 97edcd1... nameconvention
    start();
    QThread::msleep(200);
    getDishesPos();
    getOrder(3);
    do {
        getOrder();
        makeSushi();
        winCheck();
        for (int a = 0; a < 20; a = a + 1) {
        getDishes();
        QThread::msleep(350);
        }
    } while (failed == false and win == false);
    do {
        if (win == true) {
            riceCount = 10, noriCount = 10, roeCount = 10, salmonCount = 5, unagiCount = 5, shrimpCount = 5;
            win = false;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
            waitPosImageClick("continue3" + file_type, 1);
            QThread::msleep(200);
            waitPosImageClick("continue3" + file_type, 1);
=======
            waitPosImageClick("continue3" + endung, 1);
            QThread::msleep(200);
            waitPosImageClick("continue3" + endung, 1);
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
=======
            waitPosImageClick("continue3.png", 1);
            QThread::msleep(200);
            waitPosImageClick("continue3.png", 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
            waitPosImageClick("continue3.png", 1);
            QThread::msleep(200);
            waitPosImageClick("continue3.png", 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
            waitPosImageClick("continue3.png", 1);
            QThread::msleep(200);
            waitPosImageClick("continue3.png", 1);
>>>>>>> parent of 97edcd1... nameconvention
=======
            waitPosImageClick("continue3.png", 1);
            QThread::msleep(200);
            waitPosImageClick("continue3.png", 1);
>>>>>>> parent of 97edcd1... nameconvention
            getOrder(3);
            do {
                getOrder();
                makeSushi();
                for (int a = 0; a < 20; a = a + 1) {
                getDishes();
                QThread::msleep(350);
                }
            } while (failed == false and win == false);
        }
    } while (win == true);
    cv::waitKey(0);
    return 0;
}

