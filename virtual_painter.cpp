#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/////////////////////	     	Virtual Painter	        ///////////////////////

//Webcam
VideoCapture cap(0);					//Webcam Object, 0 For Laptop Webcam
Mat img;								//Main Cam Window
Mat imgHSV;								//For Hue saturated window, But we will not show that, just for easy color detection

vector<vector<int>> myColors {{22,61,154,45,163,255},		//For yellow 
								{68,72,156,102,126,255}};	//Green

vector<Scalar> myColorValues{ {0,0,255},					//red ,,, For Yellow it will do red
						{0,255,0}};							//Green

vector<vector<Point>> contours;								//Will be points of each shape or contours
vector<Vec4i> hierarchy;									

vector<vector<int>> newPoints;			//
Point myPoint;							//


Point getContours(Mat imgDil) {

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255,0,255),10);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	string objectType;
	float peri;					
	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);

		//cout << area << endl;
		if (area > 1000) {					//Removing noise //Only selecting which shape has area greater than 1000

			peri = arcLength(contours[i], true); //true for whether it is close area
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 10);  //Can write -1 instead of i to draw on each shape 
							//If you write contour instead of conPoly then it wiil draw whole shape instead of shape on shape
			cout << conPoly[i].size() << endl;	//counting the points
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;	//Because we want to start drawing from the center not from the upper left side of the square, But center of upper
			myPoint.y = boundRect[i].y;						

			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			
		}
	}
	return myPoint;
}


void findColor(Mat img) {

	
	cvtColor(img, imgHSV, COLOR_BGR2HSV); //Converting normal to HSV image

	for (int i = 0; i < myColors.size(); i++) {

		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);	//Lower Bound values of color
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);	//Upper bound values of color 
		Mat mask;
		//Will detect all the values or color which lies between upper and lower
		inRange(imgHSV, lower, upper, mask); //Input, lower range, Upper range, Masked Output
		//imshow(to_string(i), mask);

		myPoint = getContours(mask);
		if(myPoint.x!=0 && myPoint.y!=0)
			newPoints.push_back({myPoint.x,myPoint.y,i}); //Value of i is color
								//if i is 1 it is red from myColors vector
	}
	
} 

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues) {

	for (int i = 0; i < newPoints.size(); i++) {
		circle(img, Point((newPoints[i][0]),(newPoints[i][1])),10, myColorValues[newPoints[i][2]],FILLED);
	}
}

void main() {

	
	while (true) {

		cap.read(img);
		findColor(img);
		drawOnCanvas(newPoints, myColorValues);
		imshow("Image", img);
		waitKey(1);
	}

}

