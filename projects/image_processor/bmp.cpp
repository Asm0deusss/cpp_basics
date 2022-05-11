#include "bmp.h"

// BMP_HEAD_SIZE = 14;
// DIB_HEAD_SIZE = 40;
// BYTES_FOR_COLOR = 3;
// OVERALL_BYTES = 4;

BMP::BMP(const size_t inp_width, const size_t inp_height) {
    width = inp_width;
    height = inp_height;
    int padding = (OVERALL_BYTES - (width * BYTES_FOR_COLOR) % OVERALL_BYTES) % OVERALL_BYTES;
    int file_size = BMP_HEAD_SIZE + DIB_HEAD_SIZE + width * height * 3 + height * padding;
    // ASCII name
    data[0] = 'B';
    data[1] = 'M';

    // File size
    data[2] = file_size;
    data[3] = file_size >> 8;
    data[4] = file_size >> 16;
    data[5] = file_size >> 24;

    // Reserved space
    data[6] = 0;
    data[7] = 0;
    data[8] = 0;
    data[9] = 0;

    // Pixel offset
    data[10] = BMP_HEAD_SIZE + DIB_HEAD_SIZE;
    data[11] = 0;
    data[12] = 0;
    data[13] = 0;
}

DIB::DIB(size_t inp_width, size_t inp_height) {
    width = inp_width;
    height = inp_height;

    // Header size
    data[0] = DIB_HEAD_SIZE;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;

    // Image width
    data[4] = width;
    data[5] = width >> 8;
    data[6] = width >> 16;
    data[7] = width >> 24;

    // Image height
    data[8] = height;
    data[9] = height >> 8;
    data[10] = height >> 16;
    data[11] = height >> 24;

    // Planes
    data[12] = 1;
    data[13] = 0;

    // Bits per pixel
    data[14] = 24;
    data[15] = 0;

    // Compression (none)
    data[16] = 0;
    data[17] = 0;
    data[18] = 0;
    data[19] = 0;

    // Raw bitmap size
    data[20] = 0;
    data[21] = 0;
    data[22] = 0;
    data[23] = 0;

    // Print resolution X axis
    data[24] = 0;
    data[25] = 0;
    data[26] = 0;
    data[27] = 0;

    // Print resolution Y axis
    data[28] = 0;
    data[29] = 0;
    data[30] = 0;
    data[31] = 0;

    // Number of colors
    data[32] = 0;
    data[33] = 0;
    data[34] = 0;
    data[35] = 0;

    // Important colors
    data[36] = 0;
    data[37] = 0;
    data[38] = 0;
    data[39] = 0;
}
size_t DIB::GetWidth() {
    return data[4] + (data[5] << 8) + (data[6] << 16) + (data[7] << 24);
}
size_t DIB::GetHeight() {
    return data[8] + (data[9] << 8) + (data[10] << 16) + (data[11] << 24);
}
