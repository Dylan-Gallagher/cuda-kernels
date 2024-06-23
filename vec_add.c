// Compute vector sum C = A + B
__global__ void vecAddKernel(float* A, float* B, float* C, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        C[i] = A[i] + B[i];
    }
}


void vecAdd(float* A_h, float* B_h, float* C_h, int n_h) {
    int size = n * sizeof(float);
    float* A_d;
    float* B_d;
    float* C_d;

    // Allocate device memory for A, B, and C
    cudaMalloc((void**) &A_d, size);
    cudaMalloc((void**) &B_d, size);
    cudaMalloc((void**) &C_d, size);

    // Copy A and B to device memory
    cudaMemcpy(A_d, A_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(B_d, B_h, size, cudaMemcpyHostToDevice);

    vecAddKernel<<<ceil(n/256.0), 256>>>(A_d, B_d, C_d, n_h);


    // Copy C to host memory
    cudaMemcpy(C_h, C_d, size, cudaMemcpyDeviceToHost);

    // Free device memory for A, B and C
    cudaFree(A_d);
    cudaFree(B_d);
    cudaFree(C_d);
}