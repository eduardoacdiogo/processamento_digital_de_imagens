#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){

	Mat img, img_eq, hist, hist_eq;
	int nbins = 64;

	float range[] = {0, 256};
	const float *histrange = { range };

	img= imread("hist.jpeg",IMREAD_GRAYSCALE);
	if(!img.data)
    		cout << "nao abriu a imagem" << endl;

	equalizeHist( img, img_eq );
	bool uniform = true;
	bool acummulate = false;

	int histw = nbins, histh = nbins / 2;
	Mat hist_img(histh, histw, CV_8UC1, Scalar(0, 0, 0));
	Mat hist_img_eq(histh, histw, CV_8UC1, Scalar(0, 0, 0));

	calcHist(&img, 1, 0, Mat(), hist, 1, &nbins, &histrange, uniform, acummulate);
	calcHist(&img_eq, 1, 0, Mat(), hist_eq, 1, &nbins, &histrange, uniform, acummulate);

	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX, -1, Mat());
	normalize(hist_eq, hist_eq, 0, hist_img.rows, NORM_MINMAX, -1, Mat());

	hist_img.setTo(Scalar(0));
	hist_img_eq.setTo(Scalar(0));

	for(int i=0; i<nbins; i++){
  	line(hist_img, Point(i, histh), Point(i, 32 - cvRound(hist.at<float>(i))), Scalar(255, 255, 255), 1, 8, 0);
  	line(hist_img_eq, Point(i, histh), Point(i, 32 - cvRound(hist_eq.at<float>(i))), Scalar(255, 255, 255), 1, 8, 0);}

	hist_img.copyTo(img(Rect(15, 15, nbins, histh)));
	hist_img_eq.copyTo(img_eq(Rect(15, 15, nbins, histh)));

	namedWindow("original",WINDOW_NORMAL);
	namedWindow("equalizado",WINDOW_NORMAL);

	imshow( "original", img );
	imshow( "equalizado", img_eq );

	waitKey();
	return 0;
}
