/*************************************************************************
	> File Name: lab4.cpp
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年07月13日 星期四 19时27分25秒
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <opencv2/opencv.hpp>
using namespace cv;

void convolution(Mat *img,Mat *result,int start,int end) {
	int i= 0,j = 0,k = 0;
	const int n = img->channels();
	//printf("start:%d-end%d\n",start,end);
	for(i = start;i <= end;i++) {
		const uchar *previous = img->ptr<const uchar>(i-1);
		const uchar *current = img->ptr<const uchar>(i);
		const uchar *next = img->ptr<const uchar>(i+1);
		uchar *output = result->ptr<uchar>(i);
		for(j = 1;j < result->cols-1;j++) {
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
	int my_rank = 0,comm_sz = 0;
	int i = 0,m = 0,count1 = 0,count2 = 0,count3 = 0;
	clock_t start,end;

	Mat img = imread("/home/huchao/Study/hehe.jpg");
	Mat temp,result;

	if(img.empty()) {
		printf("open image failed\n");
		return -1;
	}
	result.create(img.size(),img.type());
	temp.create(img.size(),img.type());
	m = (img.rows-2)/10;

	count1 = img.cols*sizeof(uchar)*3;
	count2 = m*count1;
	count3 = (img.rows-2-9*m)*count1;

	start = clock();
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	if(my_rank != 0) {
		if(my_rank == 10) {
			convolution(&img,&temp,1+(my_rank-1)*m,img.rows-2);
			MPI_Send(temp.data +(1+(my_rank-1)*m)*count1,count3,MPI_CHAR,0,my_rank,MPI_COMM_WORLD);
			//printf("send%d\n",my_rank);
		}
		else {
			convolution(&img,&temp,1+(my_rank-1)*m,my_rank*m);
			MPI_Send(temp.data +(1+(my_rank-1)*m)*count1,count2,MPI_CHAR,0,my_rank,MPI_COMM_WORLD);
			//printf("send%d\n",my_rank);
		}
	}
	else if(my_rank == 0) {
		for(i = 0;i <= 8;i++) {
			MPI_Recv(result.data+(1+i*m)*count1,count2,MPI_CHAR,i+1,i+1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			//printf("recv%d\n",i+1);
		}
		MPI_Recv(result.data+(1+i*m)*count1,count3,MPI_CHAR,i+1,i+1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		//printf("recv%d\n",i+1);
		end = clock();
		printf("time=%fs\n",((double)(end-start)/CLOCKS_PER_SEC));
		imwrite("/home/huchao/Study/pppp.jpg",result);
	}

	MPI_Finalize();

	return 0;
}
