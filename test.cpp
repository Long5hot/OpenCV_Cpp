#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

void test_func() {

    string path = "Resources/test.jpg";
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);

}