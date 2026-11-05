#include <gtest/gtest.h>

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