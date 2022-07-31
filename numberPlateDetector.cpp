#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/objdetect.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/// /////////  Vehicle Number Plate detector  ///////

int main() {

	VideoCapture cap(0);  //0 for my laptop webcam  
	Mat img;

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/indian_license_plate.xml");

	if (plateCascade.empty())
		cout << "XML file not loaded" << endl;

	//To detect the faces and store them we need bounding boxes
	//bounding boxes basically are rectangles which are vector

	vector<Rect> plates;		//Vector of rectangles(Faces)



	while (true) {
		cap.read(img);
		

		plateCascade.detectMultiScale(img, plates, 1.1, 10);

	
		for (int i = 0; i < plates.size(); i++) {

			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("Resources/Plates/" + to_string(i) + ".png", imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("Image", img);	//To show the image
		waitKey(1);		//To hold the image 
		//0 because for infinite time
	}
}
