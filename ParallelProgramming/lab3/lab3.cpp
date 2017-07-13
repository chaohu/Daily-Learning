/*************************************************************************
	> File Name: lab3.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年07月12日 星期三 16时30分12秒
 ************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
	int i = 0;
	Mat img = imread("/home/huchao/Study/hehe.jpg");
	Mat result;

	if(img.empty()) {
		cout<<"open img failed";
		return -1;
	}

	result.create(img.size(),img.type());
	
	const int rows = img.rows;
	const int cols = img.cols;
	const int n = img.channels();
	cout<<rows<<"\t"<<cols<<"\n";
	
	#pragma omp parallel for
	for(i = 1;i < rows - 1;i++) {
		const uchar *previous = img.ptr<const uchar>(i-1);
		const uchar *current = img.ptr<const uchar>(i);
		const uchar *next = img.ptr<const uchar>(i+1);
		uchar *output = result.ptr<uchar>(i);
		for(int j = 1;j < cols - 1;j++) {
			for(int k = 0; k < n; k++) {
				//锐化操作
				//output[j*n+k] = saturate_cast<uchar>(9*current[j*n+k] - previous[(j-1)*n+k] - previous[j*n+k] - previous[(j+1)*n+k] - current[(j-1)*n+k] - current[(j+1)*n+k] - next[(j-1)*n+k] - next[j*n+k] - next[(j+1)*n+k]);
				//边缘操作
				output[j*n+k] = saturate_cast<uchar>((-7)*current[j*n+k] + previous[(j-1)*n+k] + previous[j*n+k] + previous[(j+1)*n+k] + current[(j-1)*n+k] + current[(j+1)*n+k] + next[(j-1)*n+k] + next[j*n+k] + next[(j+1)*n+k]);
			}
		}
		printf("rows:%d\n",i);
	}

	//result.row(0).setTo(Scalar(0,0,0));
	//result.row(result.rows-1).setTo(Scalar(0,0,0));
	//result.col(0).setTo(Scalar(0,0,0));
	//result.col(result.cols-1).setTo(Scalar(0,0,0));

	imwrite("/home/huchao/Study/pppp.jpg",result);

	return 0;
}
