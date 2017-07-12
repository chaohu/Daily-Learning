/*************************************************************************
	> File Name: lab3.c
	> Author: huchao
	> Mail: hnhuchao1@163.com 
	> Created Time: 2017年07月11日 星期二 17时20分40秒
 ************************************************************************/

#include <stdio.h>
#include <mpi.h>

int main(int argc,char *argv[]) {
	int A[10] = {0,0,0,0,0,0,0,0,0,0};
	int B[10] = {0,1,2,3,4,5,6,7,8,9};
	int C[10] = {0,1,2,3,4,5,6,7,8,9};

	int my_rank = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	if(my_rank <= 9) {
		A[my_rank] = B[my_rank] + C[my_rank];
		printf("result:%d\n",A[my_rank]);
	}
	MPI_Finalize();

	return 0;
}
