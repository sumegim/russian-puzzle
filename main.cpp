#include <stdio.h>

#include "bitmap.hpp"
#include <vector>

Bitmap canvas(25,5);

const std::vector<Bitmap> shapes{
    {5, 1, 'A', (const char[]) {1, 1, 1, 1, 1}},
    {4, 2, 'B', (const char[]) {0, 1, 1, 1, 1, 1, 0, 0,}},
    {4, 2, 'C', (const char[]) {1, 1, 1, 1, 1, 0, 0, 0,}},
    {4, 2, 'D', (const char[]) {1, 1, 1, 1, 0, 1, 0, 0,}},
    {3, 3, 'E', (const char[]) {1, 1, 1, 0, 1, 0, 0, 1, 0}},
    {3, 3, 'F', (const char[]) {0, 1, 0, 1, 1, 1, 0, 1, 0}},
    {3, 3, 'G', (const char[]) {1, 1, 0, 0, 1, 0, 0, 1, 1}},
    {3, 3, 'H', (const char[]) {1, 1, 1, 0, 0, 1, 0, 0, 1}},
    {3, 3, 'I', (const char[]) {1, 1, 0, 0, 1, 1, 0, 1, 0}},
    {3, 3, 'J', (const char[]) {1, 1, 0, 0, 1, 1, 0, 0, 1}},
    {3, 2, 'K', (const char[]) {1, 0, 1, 1, 1, 1}},
    {3, 2, 'L', (const char[]) {1, 1, 1, 1, 1, 0}},
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
        Bitmap b = shapes[i];
        for (size_t j = 0; j < 4; j++)
        {
            canvas.drawColor(b, j*6, 0);
            b = b.rotate();
        }
        print_bitmap(canvas);
        canvas.clear();
        printf("---\n");
    }
}
