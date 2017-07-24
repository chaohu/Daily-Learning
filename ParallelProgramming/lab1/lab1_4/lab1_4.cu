#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

void addWithCuda(int *c, const int *a, const int *b, size_t size);

__global__ void addKernel(int *c, const int *a, const int *b) {
	int i = threadIdx.x;
	c[i] = a[i] + b[i];
}

int main() {
	const int arraySize = 10;
	const int a[arraySize] = {0,1,2,3,4,5,6,7,8,9};
	const int b[arraySize] = {0,1,2,3,4,5,6,7,8,9};
	int c[arraySize] = {0,0,0,0,0,0,0,0,0,0};

	// Add vectors in parallel.
	addWithCuda(c, a, b, arraySize);
	printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",c[0], c[1], c[2], c[3], c[4]);
	// cudaThreadExit must be called before exiting in order for profiling and
	// tracing tools such as Nsight and Visual Profiler to show complete traces.
	cudaThreadExit();
	return 0;
}

// Helper function for using CUDA to add vectors in parallel.
void addWithCuda(int *c, const int *a, const int *b, size_t size) {
	int *dev_a = 0;
	int *dev_b = 0;
	int *dev_c = 0;
	// Choose which GPU to run on, change this on a multi-GPU system.
	cudaSetDevice(0);
	// Allocate GPU buffers for three vectors (two input, one output)    .
	cudaMalloc((void**)&dev_c, size * sizeof(int));
	cudaMalloc((void**)&dev_a, size * sizeof(int));
	cudaMalloc((void**)&dev_b, size * sizeof(int));
	printf("%d\n",cudaStatus);
	// Copy input vectors from host memory to GPU buffers.
	cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
	// Launch a kernel on the GPU with one thread for each element.
	addKernel<<<1, size>>>(dev_c, dev_a, dev_b);
	// cudaThreadSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	cudaThreadSynchronize();
	// Copy output vector from GPU buffer to host memory.
	cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
	cudaFree(dev_c);
	cudaFree(dev_a);
	cudaFree(dev_b);
}
