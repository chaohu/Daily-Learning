#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

void conWithCuda(const Mat *img, Mat *result, size_t size);

__global__ void conKernel(const uchar *img, uchar *result, const int *_size, const int *_rows, const int *_cols) {
	int t = threadIdx.x;
	int i = 0,j = 0,k = 0,n = 3;
	int size = *_size;
	int rows = *_rows;
	int cols = *_cols;
	int start = 1 + t * (rows-2) / size;
	int end = (t+1 == size) ? rows-2 : (t+1)*(rows-2)/size;
	int temp = 0;

	for(i = start;i <= end;i++) {
		const uchar *previous = img+(i-1)*cols*3;
		const uchar *current = img+i*cols*3;
		const uchar *next = img+(i+1)*cols*3;
		uchar *output = result+i*cols*3;
		for(j = 1;j < cols-1;j++) {
			for(k = 0;k < n;k++) {
				//锐化操作
				//output[j*n+k] = saturate_cast<uchar>(9*current[j*n+k] - previous[(j-1)*n+k] - previous[j*n+k] - previous[(j+1)*n+k] - current[(j-1)*n+k] - current[(j+1)*n+k] - next[(j-1)*n+k] - next[j*n+k] - next[(j+1)*n+k]);
				//边缘操作
				temp = (-7)*current[j*n+k] + previous[(j-1)*n+k] + previous[j*n+k] + previous[(j+1)*n+k] + current[(j-1)*n+k] + current[(j+1)*n+k] + next[(j-1)*n+k] + next[j*n+k] + next[(j+1)*n+k];
				if(temp < 0) output[j*n+k] = 0;
				else if(temp > 255) output[j*n+k] = 255;
				else output[j*n+k] = (uchar)temp;
			}
		} 
	}
}

int main() {
	int size = 10;
	Mat img = imread("hehe.jpg");
	Mat result;

	if(img.empty()) {
		printf("open image failed\n");
		return -1;
	}
	result.create(img.size(),img.type());

	// converlution in parallel.
	conWithCuda(&img, &result, size);
	imwrite("pppp.jpg",result);
	// cudaThreadExit must be called before exiting in order for profiling and
	// tracing tools such as Nsight and Visual Profiler to show complete traces.
	cudaThreadExit();
	return 0;
}

// Helper function for using CUDA to convolution in parallel.
void conWithCuda(const Mat *img, Mat *result, size_t size) {
	int *dev_size = 0;
	int *dev_rows = 0;
	int *dev_cols = 0;
	uchar *dev_img = 0;
	uchar *dev_result = 0;
	// Choose which GPU to run on, change this on a multi-GPU system.
	cudaSetDevice(0);
	// Allocate GPU buffers for three vectors (two input, one output)    .
	cudaMalloc((void**)&dev_size, sizeof(int));
	cudaMalloc((void**)&dev_rows, sizeof(int));
	cudaMalloc((void**)&dev_cols, sizeof(int));
	cudaMalloc((void**)&dev_img, img->rows * img->cols * sizeof(uchar) * 3);
	cudaMalloc((void**)&dev_result, img->rows * img->cols * sizeof(uchar) *3);
	// Copy input vectors from host memory to GPU buffers.
	cudaMemcpy(dev_size, &size, sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_rows, &(img->rows), sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_cols, &(img->cols), sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_img, img->ptr<uchar>(0), img->rows * img->cols * sizeof(uchar) * 3, cudaMemcpyHostToDevice);
	// Launch a kernel on the GPU with one thread for each element.
	conKernel<<<1, size>>>(dev_img, dev_result, dev_size, dev_rows, dev_cols);
	// cudaThreadSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	cudaThreadSynchronize();
	// Copy output vector from GPU buffer to host memory.
	cudaMemcpy(result->ptr<uchar>(0), dev_result, img->rows * img->cols * sizeof(uchar) * 3, cudaMemcpyDeviceToHost);
	cudaFree(dev_size);
	cudaFree(dev_rows);
	cudaFree(dev_cols);
	cudaFree(dev_img);
	cudaFree(dev_result);
}
