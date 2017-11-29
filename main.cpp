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
#ifdef __linux
    #include <X11/extensions/XTest.h>
#else
    #include <windows.h>
#endif

//std::string image_window = "Source Image"; //test
//std::string result_window = "Result window"; //test
int screen_x = 0, screen_y = 0, screen_w = 640, screen_h = 480;
int mouse_x = 0, mouse_y = 0;
int cali_roll_request = 0, maki_request = 0, onigiri_request = 0, salmon_roll_request = 0, shrimp_request = 0, unagi_request = 0, dragon_request = 0, combo_request = 0;
int order_count = 0;
int rice_count = 10, roe_count = 10, nori_count = 10, salmon_count = 5, shrimp_count = 5, unagi_count = 5;
int dish_y = 0, dish_1x = 0, dish_2x = 0, dish_3x = 0, dish_4x = 0, dish_5x = 0, dish_6x = 0;
bool failed = false;
bool win = false;

class Match : public QRect{
    public:
        double matching_score;
};

QVector<Match> doMatching(cv::Mat img, cv::Mat templ, int max_matches, float matching_percentage = 0.95) {

//    cv::namedWindow( image_window, CV_WINDOW_AUTOSIZE ); //test
//    cv::namedWindow( result_window, CV_WINDOW_AUTOSIZE ); //test

    cv::Mat result;
    cv::Mat img_display; //test
    QVector<Match> matches;
    img.copyTo( img_display ); //test

    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    result.create( result_rows, result_cols, CV_32FC1 );
    if (templ.empty())
            qDebug() << "fuck das tpl ist scheisse";
    if (img.empty())
            qDebug()<< "fuck das img ist scheisse";
    matchTemplate( img, templ, result, 5);
    while (true){

        double min_val; double max_val; cv::Point min_loc; cv::Point max_loc; cv::Point match_loc;
        minMaxLoc( result, &min_val, &max_val, &min_loc, &max_loc, cv::Mat() );
        match_loc = max_loc;

        if((max_val > matching_percentage) && (matches.size() != max_matches)){  //when the match has a value higher than 0.XX and matches to find hasnt been reached
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
//            cv::waitKey(0); //Check Match by Match by pressing a button
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

#ifdef __linux
    std::string file_type = ".PNG";
    std::string path = "/media/jianan/0AD4D5A9D4D59773/Projects/SushiChef-master/images/";

    void mouseClick(int x, int y){
        QCursor mouse;
        mouse.setPos(x + screen_x,y + screen_y);

        Display *dpy = XOpenDisplay (NULL);
        XTestFakeButtonEvent (dpy, 1, True,  0);
        XTestFakeButtonEvent (dpy, 1, False, 0);
        XCloseDisplay (dpy);
    }
#else
    std::string file_type = ".png";
    std::string path = "X://GitHub/Project/SushiChef/images/";
    void mouseClick(int x, int y){
        QCursor mouse;
        mouse.setPos(x + screen_x,y + screen_y);
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 1, 1, 0, 0);
    }
#endif

cv::Mat screenshotRect(int x, int y, int w, int h) {
    QRect shotRect(x, y, w, h);
    QImage desk = qApp->screens().at(0)->grabWindow(
    QDesktopWidget().winId(),
    shotRect.left(),
    shotRect.top(),
    shotRect.width(),
    shotRect.height()).toImage();
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
    QRect shotRect(screen_x, screen_y, screen_w, screen_h);
   // qDebug() << screen_x << screen_y << screen_w << screen_h;
    QImage desk = qApp->screens().at(0)->grabWindow(
    QDesktopWidget().winId(),
    shotRect.left(),
    shotRect.top(),
    shotRect.width(),
    shotRect.height()).toImage();
    desk = desk.convertToFormat( QImage::Format_RGB888 );
    desk = desk.rgbSwapped();
    return cv::Mat( desk.height(), desk.width(),
                    CV_8UC3,
                    const_cast<uchar*>(desk.bits()),
                    static_cast<size_t>(desk.bytesPerLine())
                    ).clone();
}

void getPlayScreen() {
    QVector<Match> matches = doMatching(screenshot(), cv::imread(path + "topLeft" + file_type, 1), 1);
    if (matches.size() > 0) {
        screen_x = matches[0].left();
        screen_y = matches[0].top();
    } else {
        qDebug() << "Sushi Go Round not found";
        exit(0);
    }
}

void waitPosImage(std::string templ_name, int max_matches) {
    QVector<Match> matches;
    do {
        QVector<Match> matches_temp = doMatching(screenshotGame(), cv::imread(path + templ_name), max_matches);
        matches = matches_temp;
    } while(matches.size() < 1);
    mouse_x = matches[0].left();
    mouse_y = matches[0].top();
}

void waitPosImageClick(std::string templ_name, int max_matches, float matching_percentage = 0.95) {
    QVector<Match> matches;
    do {
        QVector<Match> matches_temp = doMatching(screenshotGame(), cv::imread(path + templ_name), max_matches, matching_percentage);
        matches = matches_temp;
    } while(matches.size() < 1);
    qDebug() << "click on" << QString::fromStdString(templ_name)  << matches[0].left() << matches[0].top();
    mouseClick(matches[0].left(), matches[0].top());
    QThread::msleep(10);
}

void start() {
    waitPosImageClick("playButton" + file_type, 1);
    waitPosImageClick("continue" + file_type, 1);
    waitPosImageClick("continue2" + file_type, 1);
    waitPosImageClick("skip" + file_type, 1);
    waitPosImageClick("continue" + file_type, 1);
}

void winCheck() {
   cv::Mat screen = screenshotGame();
   QVector<Match> failed_match = doMatching(screen, cv::imread(path + "failed" + file_type), 6);
   QVector<Match> win_match = doMatching(screen, cv::imread(path + "win" + file_type), 6);
   if (failed_match.size() == 1) {
       failed = true;
   }
   if (win_match.size() == 1) {
       win = true;
   }
}

void getDishesPos() {
        QVector<Match> table = doMatching(screenshotGame(), cv::imread(path + "table" + file_type), 6);
        if (table.size() == 6) {
            dish_y = table[0].top();
            dish_1x = table[0].left() + 40;
            dish_2x = table[1].left() + 40;
            dish_3x = table[2].left() + 40;
            dish_4x = table[3].left() + 40;
            dish_5x = table[4].left() + 40;
            dish_6x = table[5].left() + 40;
        }
        qDebug() << "getting dishes"<< dish_y << dish_1x << dish_2x << dish_3x << dish_4x << dish_5x << dish_6x;
}

void getDishes() {
    qDebug() << "getting dishes"<< dish_y << dish_1x << dish_2x << dish_3x << dish_4x << dish_5x << dish_6x;
    mouseClick(dish_1x, dish_y);
    mouseClick(dish_2x, dish_y);
    mouseClick(dish_3x, dish_y);
    mouseClick(dish_4x, dish_y);
    mouseClick(dish_5x, dish_y);
    mouseClick(dish_6x, dish_y);
}

void getOrder(int min_orders = 1) {
    do {
        qDebug() << "getting Orders";
        cv::Mat screen = screenshotGame();
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
        getDishes();
        winCheck();
    } while (order_count < min_orders && win == false && failed == false);
}

void orderSupplies() {
    qDebug() << "order supplies";
    if (rice_count < 2) {
        waitPosImageClick("order" + file_type, 1);
        waitPosImageClick("riceMenu" + file_type, 1);
        mouseClick(screen_x, screen_y);
        QThread::msleep(50);
        waitPosImageClick("riceOrder" + file_type, 1);
        waitPosImageClick("standardDelivery" + file_type, 1);
        rice_count = rice_count + 10;
    }
    if (roe_count < 2) {
        waitPosImageClick("order" + file_type, 1);
        waitPosImageClick("toppingMenu" + file_type, 1, 0.98);
        mouseClick(screen_x, screen_y);
        QThread::msleep(50);
        waitPosImageClick("roeOrder" + file_type, 1);
        waitPosImageClick("standardDelivery" + file_type, 1);
        roe_count = roe_count + 10;
    }
    if (nori_count < 1) {
        waitPosImageClick("order" + file_type, 1);
        waitPosImageClick("toppingMenu" + file_type, 1);
        mouseClick(screen_x, screen_y);
        QThread::msleep(50);
        waitPosImageClick("noriOrder" + file_type, 1);
        waitPosImageClick("standardDelivery" + file_type, 1);
        nori_count = nori_count + 10;
    }
    if (salmon_count < 2) {
        waitPosImageClick("order" + file_type, 1);
        waitPosImageClick("toppingMenu" + file_type, 1);
        mouseClick(screen_x, screen_y);
        QThread::msleep(50);
        waitPosImageClick("salmonOrder" + file_type, 1, 0.98);
        waitPosImageClick("standardDelivery" + file_type, 1);
        salmon_count = salmon_count + 5;
    }
    if (shrimp_count < 2) {
        waitPosImageClick("order" + file_type, 1);
        waitPosImageClick("toppingMenu" + file_type, 1);
        mouseClick(screen_x, screen_y);
        QThread::msleep(50);
        waitPosImageClick("shrimpOrder" + file_type, 1, 0.98);
        waitPosImageClick("standardDelivery" + file_type, 1);
        shrimp_count = shrimp_count + 5;
    }
    if (unagi_count < 2) {
        waitPosImageClick("order" + file_type, 1);
        waitPosImageClick("toppingMenu" + file_type, 1);
        mouseClick(screen_x, screen_y);
        QThread::msleep(50);
        waitPosImageClick("unagiOrder" + file_type, 1, 0.98);
        waitPosImageClick("standardDelivery" + file_type, 1);
        unagi_count = unagi_count + 5;
    }
}

void makeSushi() {
    qDebug() << "making sushi";
    if (combo_request > 0) {
        getDishes();
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
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (dragon_request > 0) {
        getDishes();
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
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (unagi_request > 0) {
        getDishes();
        for (int a = 0; a < unagi_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("unagiDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("unagiDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, unagi_count = unagi_count - 2;
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (shrimp_request > 0) {
        getDishes();
        for (int a = 0; a < shrimp_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("shrimpDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("shrimpDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, shrimp_count = shrimp_count - 2;
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (salmon_roll_request > 0) {
        getDishes();
        for (int a = 0; a < salmon_roll_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("salmonDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("salmonDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, salmon_count = salmon_count - 2;
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (cali_roll_request > 0) {
        getDishes();
        for (int a = 0; a < cali_roll_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("roeDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, roe_count = roe_count - 1;
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (maki_request > 0) {
        getDishes();
        for (int a = 0; a < maki_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("roeDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("roeDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 1, nori_count = nori_count -1, roe_count = roe_count - 2;
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
    if (onigiri_request > 0) {
        getDishes();
        for (int a = 0; a < onigiri_request; a = a + 1) {
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("noriDesk" + file_type, 1);
            waitPosImageClick("riceDesk" + file_type, 1);
            waitPosImageClick("bambusRoll" + file_type, 1);
            waitPosImage("bambusRollEmpty" + file_type, 1);
            rice_count = rice_count - 2, nori_count = nori_count -1;
            orderSupplies();
            for(int a = 0; a < 5; a = a + 1) {
            getDishes();
            QThread::msleep(100);
            }
        }
    }
        onigiri_request = 0;
        maki_request = 0;
        cali_roll_request = 0;
        salmon_roll_request = 0;
        shrimp_request = 0;
        unagi_request = 0;
        dragon_request = 0;
        combo_request = 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getPlayScreen();
    doMatching(screenshotGame(), cv::imread(path + "topLeft" + file_type, 1), 1);
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
            rice_count = 10, nori_count = 10, roe_count = 10, salmon_count = 5, unagi_count = 5, shrimp_count = 5;
            win = false;
            waitPosImageClick("continue3" + file_type, 1);
            QThread::msleep(200);
            waitPosImageClick("continue3" + file_type, 1);
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

