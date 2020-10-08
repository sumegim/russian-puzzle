#include <stdio.h>

#include "shape.hpp"

Bitmap canvas(25,5);

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

void print_bitmap(const Bitmap& bitmap) {
    for (int y = 0; y < bitmap.getHeight(); y++) {
        for (int x = 0; x < bitmap.getWidth(); x++)
            printf("%c", bitmap.getC(x,y));
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
