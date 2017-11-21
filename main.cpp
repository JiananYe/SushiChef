#include <QDebug>
#include <QVector>
#include <QRect>
#include <QImage>
#include <QApplication>
#include <QWidget>
#include <QScreen>
#include <QDesktopWidget>
#include <windows.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

std::string image_window = "Source Image"; //test
std::string result_window = "Result window"; //test
int screenX = 0, screenY = 0, screenW = 640, screenH = 480;
int mouseX = 0, mouseY = 0;
std::string path = "X://GitHub/Project/SushiChef/images/";

class Match : public QRect{
    public:
        double matching_score;
};

QVector<Match> doMatching(cv::Mat img, cv::Mat templ, int max_matches) {

    cv::namedWindow( image_window, CV_WINDOW_AUTOSIZE ); //test
    cv::namedWindow( result_window, CV_WINDOW_AUTOSIZE ); //test

    cv::Mat result;
    cv::Mat img_display; //test
    QVector<Match> matches;
    img.copyTo( img_display ); //test

    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    result.create( result_rows, result_cols, CV_32FC1 );
    matchTemplate( img, templ, result, 5);
    while (true){

        double min_val; double max_val; cv::Point min_loc; cv::Point max_loc; cv::Point match_loc;
        minMaxLoc( result, &min_val, &max_val, &min_loc, &max_loc, cv::Mat() );
        match_loc = max_loc;

        if((max_val > 0.90) && (matches.size() != max_matches)){  //when the match has a value higher than 0.XX and matches to find hasnt been reached
            Match new_match;
            new_match.setLeft(match_loc.x);
            new_match.setTop(match_loc.y);
            new_match.setWidth(templ.cols);
            new_match.setHeight(templ.rows);
            new_match.matching_score = max_val;
            matches.append(new_match);

            qDebug() << "Matching number:" << matches.size() << new_match.left() << new_match.top() << new_match.matching_score;
            floodFill(result, cv::Point(match_loc.x,match_loc.y), cv::Scalar(0,0,0), 0, cv::Scalar(10,10,10));
            rectangle( img_display, match_loc, cv::Point( match_loc.x + templ.cols , match_loc.y + templ.rows ), cv::Scalar::all(0), 2, 8, 0 ); //test
            imshow( image_window, img_display ); //test
            imshow( result_window, result ); //test
            cv::waitKey(0); //Check Match by Match by pressing a button
        }
        else
        {
            if (matches.size() == max_matches){
                qDebug() << matches.size() << "matches found, exit searching";
            }
            else {
            qDebug() << "no more matches";
             }
        break;
        }
    }
    return matches;
}


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

void mouseClick(int x, int y){
    QCursor mouse;
    mouse.setPos(x + screenX,y + screenY);
    mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 1, 1, 0, 0);
}

void getPlayScreen() {
    QVector<Match> matches = doMatching(screenshot(), cv::imread(path + "topLeft.png", 1), 1);
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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getPlayScreen();
    doMatching(screenshotGame(), cv::imread(path + "topLeft.png", 1), 1);
    waitPosImage("playButton.png", 1);
    mouseClick(mouseX, mouseY);
    cv::waitKey(0);
    return 0;
}

