
/**
*   CS6023: GPU Programming 
*   Assignment 2
*   
*   Please don't change any existing code in this file.
*
*   Please add necessary memory APIs for your implementation. Use cudaFree() 
*   to free up memory as soon as you're done with an allocation. 
*   This will ensure that you don't run out of memory while running
*   large test cases. Use the minimum required memory for your 
*   implementation. DO NOT change the kernel configuration parameters.
*/

#include <chrono>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cuda.h>

using namespace std;

using std::cin;
using std::cout;

typedef long long ll;

__global__ void dKernel(long int *h_mat,long int *h_filter, long int *h_ans,int k){
   
    int mid = k/2;
    int rowUp = blockIdx.x - mid;
    int rowDown = blockIdx.x + mid;
    int colLeft = threadIdx.x - mid;
    int colRight = threadIdx.x + mid;
    long int sum=0;
    int f1=0;
    int f2=0;
    if(rowUp < 0){
      rowUp = 0;
      f1 = mid - blockIdx.x;
    }
    if(rowDown >= gridDim.x){
      rowDown = gridDim.x-1;
    }
    if(colLeft < 0){
      colLeft =0;
      f2 = mid - threadIdx.x;
    }
   if(colRight >= blockDim.x){
    colRight = blockDim.x-1;
   }
    for(int i = rowUp,k1=f1 ; i<=rowDown ; i++,k1++){
      for(int j= colLeft,k2=f2; j<=colRight ; j++,k2++){
        {
          sum += h_mat[i*blockDim.x+j] * h_filter[k1* k + k2 ];
        }
      }
    }
    h_ans[blockIdx.x * blockDim.x+threadIdx.x] = sum;
}
int main(int argc, char** argv) {

    int m,n,k;
    cin>>m>>n>>k; 
    long int* h_mat = new long int[m * n];
    long int* h_filter = new long int[k * k];
    long int* h_ans = new long int[m * n];

    for (long int i = 0; i < m * n; i++) {
        cin>>h_mat[i];
    }

    for (long int i = 0; i < k * k; i++) {
        cin>>h_filter[i];
    }

    /**
     * 
     * DO NOT CHANGE ANYTHING ABOVE THIS LINE
     * 
    **/

    /****************************************************Start Here***********************************************************/
    
    long int * gpuH_mat;
    long int * gpuH_filter;
    long int * gpuH_ans;

    cudaMalloc(&gpuH_mat,m*n*sizeof(long int));
    cudaMalloc(&gpuH_filter,k*k*sizeof(long int));
    cudaMalloc(&gpuH_ans,m*n*sizeof(long int));

    cudaMemcpy(gpuH_mat,h_mat,m*n*sizeof(long int),cudaMemcpyHostToDevice);
    cudaMemcpy(gpuH_filter,h_filter,k*k*sizeof(long int),cudaMemcpyHostToDevice);

    auto start = std::chrono::high_resolution_clock::now();//keep it just before the kernel launch

    dKernel<<<m,n>>>(gpuH_mat,gpuH_filter,gpuH_ans,k);
    cudaDeviceSynchronize();

    auto end = std::chrono::high_resolution_clock::now();//keep it just after the kernel launch

    cudaMemcpy(h_ans,gpuH_ans,m*n*sizeof(long int),cudaMemcpyDeviceToHost);
      
    /*$$$$$$$$$$$$$$$$$$$$$$$$Make sure your final output from the device is stored in h_ans.$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
    std::chrono::duration<double> elapsed1 = end - start;
    /**
     * 
     * DO NOT CHANGE ANYTHING BELOW THIS LINE
     * 
    */


    
    std::ofstream file("cuda.out");
    if (file.is_open()) {
        for (long int i = 0; i < m; i++) {
            for (long int j = 0; j < n; j++) {
                file << h_ans[i * n + j] << " ";
            }
            file << "\n";
        }
        file.close();
    } else {
        std::cout << "Unable to open file";
    }

    std::ofstream file2("cuda_timing.out");
    if(file2.is_open()) {
        file2 << elapsed1.count() << "\n";
        file2.close();
    } else {
        std::cout << "Unable to open file";
    }

    return 0;
}