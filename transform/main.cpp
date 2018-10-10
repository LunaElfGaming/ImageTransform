#include <opencv2/opencv.hpp>  
#include <iostream>  

using namespace cv;
using namespace std;

//Point trans()

Point trans1(Point p) {          //平移变换
	p.x += 30;
	p.y += 60;
	return p;
}

void translation(Mat img) {
	Mat res(img.rows + 60, img.cols + 30, CV_8UC1, Scalar(255));
	for (int i = 0;i < img.rows;i++) {
		for (int j = 0;j < img.cols;j++) {
			Point p;
			p.x = i;
			p.y = j;
			Point p2 = trans1(p);
			int grey = img.at<uchar>(p);
			res.at<uchar>(p2) = grey;

		}
	}
	namedWindow("Test1", CV_WINDOW_AUTOSIZE);
	imshow("Test1", res);
	imwrite("translation.png",res);
}


Point trans2_inv(Point p) {              //放大1.5倍变换的反变换，缩小1.5倍
	p.x = (int)(((double)p.x) / 1.5 + 0.5);
	p.y = (int)(((double)p.y) / 1.5 + 0.5);
	return p;
}

void expansion(Mat img) {
	Mat res(img.rows*1.5, img.cols*1.5, CV_8UC1, Scalar(255));
	
	for (int i = 0;i < img.rows*1.5;i++) {
		for (int j = 0;j < img.cols*1.5;j++) {
			Point p;
			p.x = i;
			p.y = j;
			Point p2 = trans2_inv(p);
			if (p2.x > img.cols)
				p2.x = img.cols;
			if (p2.y > img.rows)
				p2.y = img.rows;
			int grey = img.at<uchar>(p2);
			res.at<uchar>(p) = grey;

		}
	}
	namedWindow("Test2", CV_WINDOW_AUTOSIZE);
	imshow("Test2", res);
	imwrite("expansion1.png", res);

	Mat res2(img.rows*1.5, img.cols*1.5, CV_8UC1, Scalar(255));          //采用双线性插值
	for (double i = 0;i < img.rows*1.5;i++) {
		for (double j = 0;j < img.cols*1.5;j++) {
			double x, y, u, v;
			x = i/1.5;
			y = j/1.5;
			int xi = (int)x;
			int yj = (int)y;
			if (xi >= 0 && xi < img.cols - 1 && yj >= 0 && yj < img.rows - 1) {
				u = x - (double)xi;
				v = y - (double)yj;
				double grey1 = img.at<uchar>(xi, yj);
				double grey2 = img.at<uchar>(xi, yj + 1);
				double grey3 = img.at<uchar>(xi + 1, yj);
				double grey4 = img.at<uchar>(xi + 1, yj + 1);
				res2.at<uchar>(i, j) = (int)((1 - u)*(1 - v)*grey1 + (1 - u)*v*grey2 + u*(1 - v)*grey3 + u*v*grey4);

			}
		}
	}
	namedWindow("Test3", CV_WINDOW_AUTOSIZE);
	imshow("Test3", res2);
	imwrite("expansion2.png", res2);


}


Point trans3_inv(Point p) {         // 顺时针旋转30°的逆变换，逆时针30°
	Point p2;
	p.x -= 150;
	p2.x = (int)((double)p.x*0.866 + (double)p.y*0.5 + 0.5);
	p2.y = (int)(-(double)p.x*0.5 + (double)p.y*0.866 + 0.5);
	return p2;
}

void rotation(Mat img) {
	Mat res(img.rows+100, img.cols+150, CV_8UC1, Scalar(255));

	for (int i = 0;i < img.rows+150;i++) {
		for (int j = 0;j < img.cols+100;j++) {
			Point p;
			p.x = i;
			p.y = j;
			Point p2 = trans3_inv(p);
			if (p2.x >= 0 && p2.x < img.cols&&p2.y >= 0 && p2.y < img.rows) {
				int grey = img.at<uchar>(p2);
				res.at<uchar>(p) = grey;
			}
		}
	}

	Mat res2(img.rows + 100, img.cols + 150, CV_8UC1, Scalar(255));          //采用双线性插值
	for (double i = 0;i < img.rows + 100;i++) {
		for (double j = 0;j < img.cols + 150;j++) {
			double x, y, u, v;
			x = (i)*0.866 - (j-150)*0.5;
			y = (i)*0.5 + (j-150)*0.866;
			int xi = (int)x;
			int yj = (int)y;
			if (xi >= 0 && xi < img.cols-1&&yj >= 0 && yj < img.rows-1) {
				u = x - (double)xi;
				v = y - (double)yj;
				double grey1 = img.at<uchar>(xi, yj);
				double grey2 = img.at<uchar>(xi, yj + 1);
				double grey3 = img.at<uchar>(xi + 1, yj);
				double grey4 = img.at<uchar>(xi + 1, yj + 1);
				res2.at<uchar>(i, j) = (int)((1 - u)*(1 - v)*grey1 + (1 - u)*v*grey2 + u*(1 - v)*grey3 + u*v*grey4);

			}
		}
	}
	namedWindow("Test4", CV_WINDOW_AUTOSIZE);
	imshow("Test4", res);
	imwrite("rotation1.png", res);
	namedWindow("Test5", CV_WINDOW_AUTOSIZE);
	imshow("Test5", res2);
	imwrite("rotation2.png", res2);
}

int main() {
	Mat jpg;
	jpg = imread("./Lena.bmp", 0);
	//int row = jpg.rows;
	//int col = jpg.cols;
	//cout << row << " " << col << endl;
	//("Test", CV_WINDOW_AUTOSIZE);
	//imshow("Test", jpg);
	translation(jpg);
	expansion(jpg);
	rotation(jpg);
	

	waitKey(0);
	return 0;
}