#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img = cv::imread("../res/img1.jpg");
    Mat *gray;
    int windowsSize = 3;
    cvtColor(img, *gray, COLOR_RGB2GRAY);

    Mat minSSD = Mat::zeros(img.rows, img.cols, CV_64FC1);

    double ssdRight, ssdRightDown, ssdDown, ssdLeftUp;
    for (int i = windowsSize / 2 + 1; i < img.cols - windowsSize / 2 - 1; ++i) {
        for (int j = windowsSize / 2 + 1; j < img.rows - windowsSize / 2 - 1; ++j) {
            Mat window = (*gray)(Rect(i - windowsSize / 2, j - windowsSize / 2, windowsSize, windowsSize));
            Mat windowRight = (*gray)(Rect(i - windowsSize / 2 + 1, j - windowsSize / 2, windowsSize, windowsSize));
            Mat windowRightDown = (*gray)(
                    Rect(i - windowsSize / 2 + 1, j - windowsSize / 2 + 1, windowsSize, windowsSize));
            Mat windowDown = (*gray)(Rect(i - windowsSize / 2, j - windowsSize / 2 + 1, windowsSize, windowsSize));
            Mat windowLeftUp = (*gray)(
                    Rect(i - windowsSize / 2 - 1, j - windowsSize / 2 + 1, windowsSize, windowsSize));
            ssdRight = sum((window - windowRight).mul(window - windowRight))[0];
            ssdRightDown = sum((window - windowRightDown).mul(window - windowRightDown))[0];
            ssdDown = sum((window - windowDown).mul(window - windowDown))[0];
            ssdLeftUp = sum((window - windowLeftUp).mul(window - windowLeftUp))[0];
            minSSD.at<double>(j, i) = min(ssdRight, min(ssdRightDown, min(ssdDown, ssdLeftUp)));
        }
    }

    for (int i = windowsSize / 2; i <= img.cols - windowsSize / 2 - 1; ++i) {
        for (int j = windowsSize / 2 + 1; j <= img.rows - windowsSize / 2 - 1; ++j) {
            if (minSSD.at<double>(j, i) > minSSD.at<double>(j - 1, i)
                && minSSD.at<double>(j, i) > minSSD.at<double>(j, i - 1)
                && minSSD.at<double>(j, i) > minSSD.at<double>(j, i + 1)
                && minSSD.at<double>(j, i) > minSSD.at<double>(j + 1, i)) {
//                cout << "(" << i << ", " << j << ") = " << minSSD.at<double>(j, i) << endl;
                circle(img, Point(i, j), 1, Scalar(0, 0, 255), -1);
            }
        }
    }

    imwrite("../res/result.jpg", img);
    imshow("hi", img);
    waitKey();
    return 0;


}