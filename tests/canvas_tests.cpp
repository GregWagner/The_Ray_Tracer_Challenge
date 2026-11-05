#include <gtest/gtest.h>

#include <string>

#include "canvas.hpp"
#include "tuple.hpp"

TEST(Canvas, CreatingACanvas) {
    Canvas canvasValue = canvas(10, 20);

    EXPECT_EQ(canvasValue.width, 10);
    EXPECT_EQ(canvasValue.height, 20);

    for (int yIndex = 0; yIndex < canvasValue.height; yIndex++) {
        for (int xIndex = 0; xIndex < canvasValue.width; xIndex++) {
            EXPECT_TRUE(canvasValue.pixelAt(xIndex, yIndex) == color(0.0, 0.0, 0.0));
        }
    }
}

TEST(Canvas, WritingPixelsToCanvas) {
    Canvas canvasValue = canvas(10, 20);
    Tuple redValue = color(1.0, 0.0, 0.0);

    writePixel(canvasValue, 2, 3, redValue);

    EXPECT_TRUE(pixelAt(canvasValue, 2, 3) == redValue);
}

TEST(Canvas, ConstructingPpmHeader) {
    Canvas canvasValue = canvas(5, 3);

    std::string ppmValue = canvasToPpm(canvasValue);

    std::string expectedValue = "P3\n5 3\n255\n";
    EXPECT_EQ(ppmValue.substr(0, expectedValue.size()), expectedValue);
}

TEST(Canvas, ConstructingPpmPixelData) {
    Canvas canvasValue = canvas(5, 3);
    Tuple colorOne = color(1.5, 0.0, 0.0);
    Tuple colorTwo = color(0.0, 0.5, 0.0);
    Tuple colorThree = color(-0.5, 0.0, 1.0);

    writePixel(canvasValue, 0, 0, colorOne);
    writePixel(canvasValue, 2, 1, colorTwo);
    writePixel(canvasValue, 4, 2, colorThree);

    std::string ppmValue = canvasToPpm(canvasValue);

    std::string expectedRows =
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    EXPECT_TRUE(ppmValue.find(expectedRows) != std::string::npos);
}