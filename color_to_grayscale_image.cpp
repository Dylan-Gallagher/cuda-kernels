__global__ void colorToGrayscaleImageKernel(unsigned char* P_in, unsigned char* P_out, int width, int height) {
    // Assume that P_in is of shape (rows, channels, columns) 
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    int col = blockIdx.y * blockDim.y + threadIdx.y;

    if (col < width && row < height) {
        int grayOffset = row * width + col;
        int rgbOffset = grayOffset * 3; 
        P_out[grayOffset] = P_in[rgbOffset] * 0.21f + P_in[rgbOffset + 1] * 0.71f + P_in[rgbOffset + 2] * 0.07f;
    }
}