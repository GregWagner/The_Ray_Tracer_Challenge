#ifndef QT_CANVAS_H
#define QT_CANVAS_H

#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QPixmap>

#include "canvas.hpp"
#include "tuple.hpp"

inline void showCanvas(QApplication &application, const Canvas &canvasValue, const char *title) {
    QImage image(static_cast<int>(canvasValue.width), static_cast<int>(canvasValue.height), QImage::Format_RGB32);

    int y = 0;
    while (y < canvasValue.height) {
        int x = 0;
        while (x < canvasValue.width) {
            Tuple pixelValue = canvasValue.pixelAt(x, y);
            int redValue = static_cast<int>(pixelValue.red * 255.0 + 0.5);
            int greenValue = static_cast<int>(pixelValue.green * 255.0 + 0.5);
            int blueValue = static_cast<int>(pixelValue.blue * 255.0 + 0.5);

            if (redValue < 0) {
                redValue = 0;
            }
            if (redValue > 255) {
                redValue = 255;
            }
            if (greenValue < 0) {
                greenValue = 0;
            }
            if (greenValue > 255) {
                greenValue = 255;
            }
            if (blueValue < 0) {
                blueValue = 0;
            }
            if (blueValue > 255) {
                blueValue = 255;
            }

            image.setPixel(x, y, qRgb(redValue, greenValue, blueValue));
            x = x + 1;
        }
        y = y + 1;
    }

    QLabel label;
    label.setPixmap(QPixmap::fromImage(image));
    label.setWindowTitle(title);
    label.resize(image.size());
    label.show();

    application.exec();
}
#endif
