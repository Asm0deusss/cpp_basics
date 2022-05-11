#pragma once
#include "image.h"
#include <fstream>

struct ImEx {
    static void ImportImage(const char* path, BMP& bmp, DIB& dib, Image& cur_image);
    static void ExportImage(const char* path, BMP& bmp, DIB& dip, Image& cur_image);
};