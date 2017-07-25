/*************************************************************************
	> File Name: lab2.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年07月12日 星期三 16时30分12秒
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

struct _con_arg {
	Mat *img;
	Mat *result;
	int start;
	int end;
};

void *convolution(void *con_arg) {
	int i = 0,j = 0,k = 0;
	struct _con_arg *temp = (struct _con_arg*)con_arg;
	const int n = temp->img->channels();
	//printf("start:%d-end:%d\n",temp->start,temp->end);
	for(i = temp->start;i <= temp->end;i++) {
		const uchar *previous = temp->img->ptr<const uchar>(i-1);
		const uchar *current = temp->img->ptr<const uchar>(i);
		const uchar *next = temp->img->ptr<const uchar>(i+1);
		uchar *output = temp->result->ptr<uchar>(i);
		for(j = 1;j < temp->result->cols - 1;j++) {
			for(k = 0; k < n; k++) {
				//锐化操作
				//output[j*n+k] = saturate_cast<uchar>(9*current[j*n+k] - previous[(j-1)*n+k] - previous[j*n+k] - previous[(j+1)*n+k] - current[(j-1)*n+k] - current[(j+1)*n+k] - next[(j-1)*n+k] - next[j*n+k] - next[(j+1)*n+k]);
				//边缘操作
				output[j*n+k] = saturate_cast<uchar>((-7)*current[j*n+k] + previous[(j-1)*n+k] + previous[j*n+k] + previous[(j+1)*n+k] + current[(j-1)*n+k] + current[(j+1)*n+k] + next[(j-1)*n+k] + next[j*n+k] + next[(j+1)*n+k]);
			}
		}
	}
}

int main() {
	int i = 0;
	int m = 0;
	clock_t start,end;
	pthread_t t_id[10];
	struct _con_arg con_arg[10];
	Mat img = imread("/home/huchao/Study/hehe.jpg");
	Mat result;

	if(img.empty()) {
		cout<<"open img failed";
		return -1;
	}
	result.create(img.size(),img.type());
	m = ceil((img.rows-2)/10.0);
	
	start = clock();
	for(i = 0;i < 10;i++) {
		con_arg[i].img = &img;
		con_arg[i].result = &result;
		con_arg[i].start = 1+i*m;
		if(i == 9) con_arg[i].end = img.rows-2;
		else con_arg[i].end = (i+1)*m;
		if(pthread_create(&t_id[i],NULL,convolution,&con_arg[i])) {
			cout<<"线程创建出错\n";
		}
	}
	
	for(i = 0;i < 10;i++) {
		if(pthread_join(t_id[i],NULL) != 0) {
			cout<<"线程出错\n";
		}
	}
	end = clock();
	printf("time=%fs\n",((double)(end-start)/CLOCKS_PER_SEC));

	//result.row(0).setTo(Scalar(0,0,0));
	//result.row(result.rows-1).setTo(Scalar(0,0,0));
	//result.col(0).setTo(Scalar(0,0,0));
	//result.col(result.cols-1).setTo(Scalar(0,0,0));
	
	imwrite("/home/huchao/Study/pppp.jpg",result);
	return 0;
}
