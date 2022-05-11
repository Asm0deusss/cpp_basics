#include <iostream>
#include "ImEx.h"
#include "crop_filter.h"
#include "negative_filter.h"
#include "grayscale_filter.h"
#include "sharpening_filter.h"
#include "edge_detection_filter.h"
#include "blur_filter.h"
#include "my_filter.h"
#include <memory>
#include <iomanip>

void Help() {
    std::cout << std::endl;

    std::cout << "Input format: {name of program} {input file path} {output file path} [-{filter 1 name} [parameter "
                 "1] [parameter 2] ...] [-{filter2 name} [parameter 1] [parameter 2] ...] ..."
              << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(8) << "FILTERS" << std::setw(20) << "PARAMETERS" << std::setw(5) << ""
              << std::setiosflags(std::ios::left) << std::setw(40) << "DESCRIPTION"
              << std::resetiosflags(std::ios::left) << std::endl;

    std::cout << std::setw(8) << "-crop" << std::setw(20) << "height, width" << std::setw(5) << ""
              << std::setiosflags(std::ios::left) << std::setw(40) << "Crop image with given integer size"
              << std::resetiosflags(std::ios::left) << std::endl;

    std::cout << std::setw(8) << "-neg" << std::setw(20) << "no parameters" << std::setw(5) << ""
              << std::setiosflags(std::ios::left) << std::setw(40) << "Apply negative filter"
              << std::resetiosflags(std::ios::left) << std::endl;

    std::cout << std::setw(8) << "-gs" << std::setw(20) << "no parameters" << std::setw(5) << ""
              << std::setiosflags(std::ios::left) << std::setw(40) << "Apply grayscale filter"
              << std::resetiosflags(std::ios::left) << std::endl;

    std::cout << std::setw(8) << "-sharp" << std::setw(20) << "no parameters" << std::setw(5) << ""
              << std::setiosflags(std::ios::left) << std::setw(40) << "Apply sharpening filter"
              << std::resetiosflags(std::ios::left) << std::endl;

    std::cout << std::setw(8) << "-edge" << std::setw(20) << "threshold" << std::setw(5) << ""
              << std::setiosflags(std::ios::left) << std::setw(40) << "Apply edge detection filter with given threshold"
              << std::resetiosflags(std::ios::left) << std::endl;

    std::cout << std::setw(8) << "-blur" << std::setw(20) << "sigma" << std::setw(5) << ""
              << std::setiosflags(std::ios::left) << std::setw(40) << "Apply Gauss blur with given sigma"
              << std::resetiosflags(std::ios::left) << std::endl;

    std::cout << std::setw(8) << "-sobel" << std::setw(20) << "no parameters" << std::setw(5) << ""
              << std::setiosflags(std::ios::left) << std::setw(40) << "Apply my realization of Sobel's filter"
              << std::resetiosflags(std::ios::left) << std::endl;

    std::cout << std::endl;
}

enum class ArgInp { Int, Double, Str };

ArgInp CheckInp(const std::string &inp) {
    size_t dot_count = 0;
    bool is_prime = true;
    for (const auto i : inp) {
        if (i == '.') {
            ++dot_count;
        }

        if (!isdigit(i)) {
            if (i == '.' && dot_count == 1) {
                continue;
            }
            is_prime = false;
        }
    }
    if (is_prime && dot_count == 0) {
        return ArgInp::Int;
    } else if (is_prime && dot_count == 1) {
        return ArgInp::Double;
    }
    return ArgInp::Str;
}

void UnknownCommand() {
    std::cout << "Unknown command!" << std::endl;
    std::cout << "Type -help to see help menu" << std::endl;
}

void NoArgs(const std::string &s) {
    std::cout << "No arguments for " << s << std::endl;
}

void BadArgs(const std::string &s) {
    std::cout << "Bad arguments for " << s << std::endl;
}

void CheckFilter(const std::string &s, const char *argv, const size_t argc, size_t &i,
                 std::vector<std::shared_ptr<Filter>> &filters) {
    if (CheckInp(argv) != ArgInp::Int && CheckInp(argv) != ArgInp::Double) {
        throw std::runtime_error("bad input");
    }
    if (s == "-edge") {
        filters.push_back(std::shared_ptr<Filter>(new EdgeDetection(std::strtof(argv, nullptr))));
    } else if (s == "-blur") {
        filters.push_back(std::shared_ptr<Filter>(new GaussBlur(std::strtof(argv, nullptr))));
    }
    i += 1;
}

int main(int argc, char *argv[]) {

    // No commands
    if (argc == 1) {
        UnknownCommand();
        return 0;
    }

    // Only one command (-help or trash)
    if (argc == 2) {
        if (std::strcmp(argv[1], "-help") == 0) {
            Help();
        } else {
            UnknownCommand();
        }
        return 0;
    }

    const char *input_path = argv[1];
    const char *output_path = argv[2];

    std::vector<std::shared_ptr<Filter>> filters;

    for (size_t i = 3; i < argc; ++i) {
        if (std::strcmp(argv[i], "-crop") == 0) {
            if (argc - i < 2) {
                NoArgs("-crop");
                return 0;
            } else {
                if (CheckInp(argv[i + 1]) != ArgInp::Int || CheckInp(argv[i + 2]) != ArgInp::Int) {
                    BadArgs("-crop");
                    return 0;
                }
                filters.push_back(std::shared_ptr<Filter>(
                    new Crop(std::strtol(argv[i + 1], nullptr, 10), std::strtol(argv[i + 2], nullptr, 10))));
                i += 2;
                continue;
            }
        } else if (std::strcmp(argv[i], "-gs") == 0) {
            filters.push_back(std::shared_ptr<Filter>(new GrayScale()));
        } else if (std::strcmp(argv[i], "-neg") == 0) {
            filters.push_back(std::shared_ptr<Filter>(new Negative()));
        } else if (std::strcmp(argv[i], "-sharp") == 0) {
            filters.push_back(std::shared_ptr<Filter>(new SharpFilter()));
        } else if (std::strcmp(argv[i], "-edge") == 0) {
            if (argc - i < 2) {
                NoArgs("-edge");
                return 0;
            }
            try {
                CheckFilter("-edge", argv[i + 1], argc, i, filters);
            } catch (std::runtime_error &err) {
                BadArgs("-edge");
                return 0;
            }
            continue;

        } else if (std::strcmp(argv[i], "-blur") == 0) {
            if (argc - i < 2) {
                NoArgs("-blur");
                return 0;
            }
            try {
                CheckFilter("-blur", argv[i + 1], argc, i, filters);
            } catch (std::runtime_error &err) {
                BadArgs("-blur");
                return 0;
            }
            continue;

        } else if (std::strcmp(argv[i], "-sobel") == 0) {
            filters.push_back(std::shared_ptr<Filter>(new SobelFilter()));
        } else {
            UnknownCommand();
            return 0;
        }
    }

    BMP main_bmp;
    DIB main_dib;
    Image image;

    try {
        ImEx::ImportImage(input_path, main_bmp, main_dib, image);
    } catch (const std::runtime_error &err) {
        std::cout << "You can't open import file" << std::endl;
        return 0;
    }

    for (const auto &filter : filters) {
        try {
            filter->MakeFilter(image);
        } catch (const std::exception &exc) {
            std::cout << exc.what() << std::endl;
            return 0;
        }
    }

    main_bmp = BMP(image.width_, image.height_);
    main_dib = DIB(image.width_, image.height_);

    try {
        ImEx::ExportImage(output_path, main_bmp, main_dib, image);
    } catch (const std::runtime_error &err) {
        std::cout << "You can't open export file" << std::endl;
        return 0;
    }
}
