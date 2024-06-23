#define BLUR_SIZE 1;

__global__ void imageBlurKernel(unsigned char* in, unsigned char* out, int w, int h) {
    int row = blockDim.x * blockIdx.x + threadIdx.x;
    int col = blockDim.y * blockIdx.y + threadIdx.y;

    if (row < h && col < w) {
        int pixVal = 0;
        int pixels = 0;

        for (int currRow = row - BLUR_SIZE; currRow <= row + BLUR_SIZE; ++currRow) { 
            for (int currCol = col - BLUR_SIZE; currCol <= col + BLUR_SIZE; ++currCol) {
                if (currRow > 0 && currRow < h && currCol > 0 && currCol < w) {
                    pixVal += in[currRow * w + currCol];
                    ++pixels;
                }
            }
        }

        out[row * w + col] = (unsigned char) (pixVal / pixles);
    }
}