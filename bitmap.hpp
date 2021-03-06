#pragma once

#include <algorithm>
#include <cstring>

class Bitmap {
protected:
    static const int MAX_WIDTH = 50;
    static const int MAX_HEIGHT = 20;

    int width;
    int height;
    char color;
    size_t area;
    char buffer[MAX_WIDTH * MAX_HEIGHT];

public:
    Bitmap(int width, int height, char color = 'X', const char* data = nullptr)
        : width(width)
        , height(height)
        , color(color)
        , area(0)
    {
        memset(buffer, 0, MAX_WIDTH * MAX_HEIGHT);

        if (data)
            for (int i = 0; i < width*height; i++)
                if (data[i]) {
                    buffer[i] = data[i];
                    area++;
                }
    }

    const int getWidth() const {
        return width;
    }

    const int getHeight() const {
        return height;
    }

    const char getColor() const {
        return color;
    }

    const size_t getArea() const {
        return area;
    }

    const size_t getTotalArea() const {
        return width*height;
    }

    char get(int x, int y) const {
        return buffer[width*y + x];
    }

    char getC(int x, int y) const {
        return (buffer[width*y + x] ? buffer[width*y + x] : ' ');
    }

    void inc(int x, int y) {
        buffer[width*y + x]++;
    }

    void set(int x, int y, char val) {
        buffer[width*y + x] = val;
    }

    void setColor(int color) {
        this->color = color;
    }

    void clear() {
        for (int i = 0; i < width*height; i++)
            buffer[i] = 0;
    }

    void draw(const Bitmap& other, int x0, int y0) {
        const int max_y = std::min(height, other.height + y0);
        const int max_x = std::min(width, other.width + x0);

        for (int y = y0; y < max_y; y++)
            for (int x = x0; x < max_x; x++)
                if (other.get(x-x0,y-y0))
                    set(x, y, other.color);
    }

    void undraw(const Bitmap& other, int x0, int y0) {
        const int max_y = std::min(height, other.height + y0);
        const int max_x = std::min(width, other.width + x0);

        for (int y = y0; y < max_y; y++)
            for (int x = x0; x < max_x; x++)
                if (other.get(x-x0,y-y0))
                    set(x, y, 0);
    }

    Bitmap rotate() const {
        Bitmap r(height, width, color);

        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                r.set(y, x, get((width-1)-x, y));

        return r;
    }

    Bitmap flipX() const {
        Bitmap r(width, height, color);

        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                r.set(x, y, get((width-1)-x, y));

        return r;
    }

    Bitmap flipY() const {
        Bitmap r(width, height, color);

        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                r.set(x, y, get(x, (height-1)-y));

        return r;
    }

    bool operator==(const Bitmap& other) {
        if (width != other.width || height != other.height)
            return false;

        return (memcmp(buffer, other.buffer, width*height) == 0);
    }
};
