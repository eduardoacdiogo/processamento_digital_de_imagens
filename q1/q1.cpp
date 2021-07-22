#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main(){
	Mat img;
  	Vec3b val;
  	//Ponto inicial e final
  	Point p1, p2;
  	//Leitura do arquivo
  	img = imread("biel.png", IMREAD_GRAYSCALE);
  	imshow("original", img);
  	if (!img.data){
        	std::cout << "Arquivo não foi aberto" << std::endl;
        	return -1;
        }
        //coleta de dados do usuário
        cout << "Digite as Coordenadas do primeiro ponto" << endl;
        cin >> p1.x;
        cin >> p1.y;
        
        cout << "Digite as Coordenadas do segundo ponto" << endl;
        cin >> p2.x;
        cin >> p2.y;
        
        for(int i = p1.x; i < p2.x;i++){
        	for(int j = p1.y; j < p2.y; j++){
        		img.at<uchar>(i,j) = 255 - img.at<uchar>(i,j);
        	}
        }
        
        namedWindow("Negativo", WINDOW_AUTOSIZE);
        imshow("negativo", img);
        
        waitKey();
  	
	return 0;
}
