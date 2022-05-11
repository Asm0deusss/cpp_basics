cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image.cpp
        bmp.cpp
        main.cpp
        ImEx.cpp
        matrix_filter.cpp
        crop_filter.cpp
        grayscale_filter.cpp
        negative_filter.cpp
        my_filter.cpp
        edge_detection_filter.cpp
        blur_filter.cpp
        )

add_catch(test_image_processor
        bmp.cpp
        image.cpp
        ImEx.cpp
        test.cpp
        )

add_catch(test_matrix_filter
        bmp.cpp
        image.cpp
        ImEx.cpp
        matrix_filter.cpp
        test_matrix_filter.cpp
        )

add_catch(test_crop
        bmp.cpp
        image.cpp
        ImEx.cpp
        crop_filter.cpp
        crop_test.cpp
        )

add_catch(test_grayscale
        bmp.cpp
        image.cpp
        ImEx.cpp
        grayscale_filter.cpp
        test_grayscale.cpp
        )

add_catch(test_negative
        bmp.cpp
        image.cpp
        ImEx.cpp
        negative_filter.cpp
        test_negative.cpp
        )

add_catch(test_edge_detection
        bmp.cpp
        image.cpp
        ImEx.cpp
        grayscale_filter.cpp
        matrix_filter.cpp
        edge_detection_filter.cpp
        test_edge_detection.cpp
        )

add_catch(test_blur
        bmp.cpp
        image.cpp
        ImEx.cpp
        blur_filter.cpp
        test_blur.cpp
        )

add_catch(test_sharpening
        bmp.cpp
        image.cpp
        ImEx.cpp
        matrix_filter.cpp
        test_sharpening.cpp
        )
