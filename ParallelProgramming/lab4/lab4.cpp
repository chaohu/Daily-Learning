/*************************************************************************
	> File Name: lab4.c
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年07月13日 星期四 19时27分25秒
 ************************************************************************/

#include <stdio.h>
#include <mpi.h>
#include <opencv2/opencv.hpp>
using namespace cv;

void convolution(const Mat &img,Mat &result,int start,int end) {
	int i= 0,j = 0,k = 0;
	const int n = img.channels();
	printf("start:%d-end%d\n",start,end);
	for(i = start;i<=end;i++) {
		const uchar *previous = img.ptr<const uchar>(i-1);
		const uchar *current = img.ptr<const uchar>(i);
		const uchar *next = img.ptr<const uchar>(i+1);
		uchar *output = result.ptr<uchar>(i);
		for(j = 1;j < result.cols-1;j++) {
			for(k = 0;k<n;k++) {
				//锐化操作
				//output[j*n+k] = saturate_cast<uchar>(9*current[j*n+k] - previous[(j-1)*n+k] - previous[j*n+k] - previous[(j+1)*n+k] - current[(j-1)*n+k] - current[(j+1)*n+k] - next[(j-1)*n+k] - next[j*n+k] - next[(j+1)*n+k]);
				//边缘操作
				output[j*n+k] = saturate_cast<uchar>((-7)*current[j*n+k] + previous[(j-1)*n+k] + previous[j*n+k] + previous[(j+1)*n+k] + current[(j-1)*n+k] + current[(j+1)*n+k] + next[(j-1)*n+k] + next[j*n+k] + next[(j+1)*n+k]);
			}
		}
	}
}

int main(int argc,char *argv[]) {
	int my_rank = 0;
	int m = 0;

	Mat img = imread("home/huchao/Study/hehe/jpg");
	Mat result;

	if(img.empty()) {
		printf("open image failed\n");
		return -1;
	}
	result.create(img.size(),img.type());
	m = (img.rows-2)/10;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	if(my_rank <= 8) {
		convolution(img,result,1+my_rank*m,(my_rank+1)*m);
	}
	else if(my_rank == 9) {
		convolution(img,result,1+my_rank*m,img.rows-2);
	}

	MPI_Finalize();

	imwrite("/home/huchao/Study.pppp.jpg",result);
	return 0;
}
