#pragma once
#include <iostream>

const int BMP_HEAD_SIZE = 14;
const int DIB_HEAD_SIZE = 40;
const int BYTES_FOR_COLOR = 3;
const int OVERALL_BYTES = 4;

struct BMP {
    BMP(){};
    BMP(const size_t inp_width, const size_t inp_height);
    ~BMP() = default;

    const size_t operator[](size_t i) const {
        return data[i];
    };

    unsigned char data[BMP_HEAD_SIZE];
    size_t width;
    size_t height;
};

struct DIB {
    DIB(){};
    DIB(size_t width, size_t height);
    ~DIB() = default;

    size_t GetWidth();
    size_t GetHeight();

    const size_t operator[](size_t i) const {
        return data[i];
    };

    unsigned char data[DIB_HEAD_SIZE];
    size_t width;
    size_t height;
};
