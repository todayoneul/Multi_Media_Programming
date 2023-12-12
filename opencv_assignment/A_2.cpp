#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
    VideoCapture capture("data_source/ball.avi");
    if (!capture.isOpened()) {
        cerr << "\n -------------- The video file was not found. -----------------" << endl;
        return 0;
    }

    int width = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(capture.get(cv::CAP_PROP_FRAME_HEIGHT));
    Size size(width, height);

    Mat bkgImage = imread("data_source/ballBkg.jpg", cv::IMREAD_GRAYSCALE); 

    if (bkgImage.empty()) {
        cerr << "\n --------------Failed to load background image.----------------" << endl;
        return -1;
    }

    Mat grayImage, diffImage, frame;
    int nFrame = 0;
    int nThreshold = 50;

    for (;;) {
        capture >> frame;
        if (frame.empty())
            break;
        nFrame++;
        cout << "nFrame = " << nFrame << endl;

        cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);
        absdiff(grayImage, bkgImage, diffImage);
        

        threshold(diffImage, diffImage, nThreshold, 255, cv::THRESH_BINARY);

        imshow("grayImage", grayImage);
        imshow("diffImage", diffImage);


        char chKey = waitKey(10);
        if (chKey == 27)
            break;
    }

    destroyAllWindows();
    return 0;
}