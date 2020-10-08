#include <stdio.h>

#include "shape.hpp"

Bitmap canvas(50,5);

const std::vector<Shape> shapes{
    (Bitmap) {5, 1, 'A', (const char[]) {1, 1, 1, 1, 1}},
    (Bitmap) {4, 2, 'B', (const char[]) {0, 1, 1, 1, 1, 1, 0, 0,}},
    (Bitmap) {4, 2, 'C', (const char[]) {1, 1, 1, 1, 1, 0, 0, 0,}},
    (Bitmap) {4, 2, 'D', (const char[]) {1, 1, 1, 1, 0, 1, 0, 0,}},
    (Bitmap) {3, 3, 'E', (const char[]) {1, 1, 1, 0, 1, 0, 0, 1, 0}},
    (Bitmap) {3, 3, 'F', (const char[]) {0, 1, 0, 1, 1, 1, 0, 1, 0}},
    (Bitmap) {3, 3, 'G', (const char[]) {1, 1, 0, 0, 1, 0, 0, 1, 1}},
    (Bitmap) {3, 3, 'H', (const char[]) {1, 1, 1, 0, 0, 1, 0, 0, 1}},
    (Bitmap) {3, 3, 'I', (const char[]) {1, 1, 0, 0, 1, 1, 0, 1, 0}},
    (Bitmap) {3, 3, 'J', (const char[]) {1, 1, 0, 0, 1, 1, 0, 0, 1}},
    (Bitmap) {3, 2, 'K', (const char[]) {1, 0, 1, 1, 1, 1}},
    (Bitmap) {3, 2, 'L', (const char[]) {1, 1, 1, 1, 1, 0}},
};


#define COLOR_AFTER "\033[0m"

const char* get_color_before(unsigned n)
{
    n = n % 14;
    static const char* labels[14] = {
        "\x1B[31m",
        "\x1B[32m",
        "\x1B[33m",
        "\x1B[34m",
        "\x1B[35m",
        "\x1B[36m",
        "\x1B[37m",
        "\x1B[91m",
        "\x1B[92m",
        "\x1B[93m",
        "\x1B[94m",
        "\x1B[35m",
        "\x1B[96m",
        "\x1B[97m"
    };

    return labels[n];
}

char get_marker(char c) {
    if (c == ' ')
        return ' ';

    return c/7 > 0 ? 'X' : 'O';
}

void print_bitmap(const Bitmap& bitmap) {
    for (int y = 0; y < bitmap.getHeight(); y++) {
        for (int x = 0; x < bitmap.getWidth(); x++){
            const char c = bitmap.getC(x,y);
            printf("%s%c" COLOR_AFTER, get_color_before(c%7), get_marker(c));
        }
        printf("\n");
    }
}

int main() {
    for (size_t i = 0; i < shapes.size(); i++) {
        for (size_t j = 0; j < shapes[i].getNumOfVariants(); j++)
        {
            Bitmap b = shapes[i].getVariant(j);
            canvas.drawColor(b, j*6, 0);
            b = b.rotate();
        }
        print_bitmap(canvas);
        canvas.clear();
        printf("---\n");
    }
}
