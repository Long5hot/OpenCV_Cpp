#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//Step-1 Preprocessing of the image, Finding edges of the image
//Step-2 Get Contours -Finding Biggest 
//Step-3 Warping of image


Mat imgOriginal, imgGray, imgCanny, imgThreshold, imgDil, imgBlur, imgWarp, final_image;
vector<Point> initialPoints, docPoints; 
vector<vector<Point>> contours;								//Will be points of each shape or contours
vector<Vec4i> hierarchy;

float w = 480, h = 640;

Mat preProcessing(Mat img) {
	
	cvtColor(img, imgGray, COLOR_BGR2GRAY);  //input image, Output image , filter

	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0); //(7,7) and 5 show how much blur you want

	//Canny Edge detector
	Canny(imgBlur, imgCanny, 25, 75);	//Threshold_1 and Threshold_2 are the values for edge detection 
																	// Lesser the value more the edges in picture

	//dialate the image :: Increase the thickness of image
	//Erold the image	:: Decrease the thickness of image

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); //This creates kernel which we can use for dilation
																		 //Increase the size will dilate more and erode more
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);
	return imgDil;
}


vector<Point> getContours(Mat imgDil) {

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255,0,255),10);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point> biggest;
	string objectType;
	float peri;
	int area, maxArea=0;
	

	for (int i = 0; i < contours.size(); i++) {
		area = contourArea(contours[i]);

		//cout << area << endl;
		if (area > 1000) {					//Removing noise //Only selecting which shape has area greater than 1000

			peri = arcLength(contours[i], true); //true for whether it is close area
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			
			if (area > maxArea && conPoly[i].size() == 4) {
				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);  //Can write -1 instead of i to draw on each shape 
							//If you write contour instead of conPoly then it wiil draw whole shape instead of shape on shape

				biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;				//Finding The biggest area or biggest contour
			}
			//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 10);  //Can write -1 instead of i to draw on each shape 
							//If you write contour instead of conPoly then it wiil draw whole shape instead of shape on shape

			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color) {

	for (int i = 0; i < points.size(); i++) {
		circle(imgOriginal, points[i], 10, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

vector<Point> reorder(vector<Point> points) {

	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;

	for (int i = 0; i < 4; i++) {
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);  //3

	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float wt, float hgt)
{

	Point2f src[4] = { points[0], points[1], points[2], points[3] }; //Points of King Card  //Find this points from paint (Pixel points)

	Point2f dst[4] = { {0.0f,0.0f},{wt,0.0f}, {0.0f,hgt},{wt,hgt} };   //Warped straight King Card 

	Mat matrix = getPerspectiveTransform(src, dst);	//Transformation matrix 
	warpPerspective(img, imgWarp, matrix, Point(wt, hgt));
	return imgWarp;
}
void main() {

	string path = "Resources/paper.jpg";
	imgOriginal = imread(path);	
	//Resizing bcoz size of the image is big, But will do again normal
	//resize(imgOriginal, imgOriginal, Size(), 0.5,0.5);


	//Preprocessing
	imgThreshold = preProcessing(imgOriginal);
	//Get Contours - Biggest
	initialPoints = getContours(imgThreshold);
	//drawPoints(initialPoints, Scalar(0,0,255));
	//Reordering
	docPoints = reorder(initialPoints);
	//drawPoints(docPoints, Scalar(0, 255, 0));
	
	//Warp
	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//Crop
	int cropvalue=5;
	Rect roi(cropvalue, cropvalue, (w - (2 * cropvalue)), (h - (2 * cropvalue)));
	Mat imgCrop = imgWarp(roi);

	
	cvtColor(imgCrop, final_image, COLOR_BGR2GRAY);
	adaptiveThreshold(final_image,final_image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,71,7);
	imshow("Image", imgOriginal);	//To show the image
	
	imshow("Final Image", final_image);
	waitKey(0);		//To hold the image 
	//0 because for infinite time

}