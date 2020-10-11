#include "bitmap.hpp"

#include <vector>

class FloodFiller : protected Bitmap {
    char fields;
    size_t filledArea;

public:
    FloodFiller(int width, int height)
        : Bitmap(width, height, '.', NULL)
        , fields(0)
        , filledArea(0)
    {}

    void draw(const Bitmap& other, int x0, int y0) {
        const char color = other.getColor();
        bool was_removed = false;

        for (int y = y0; (y < height && (y-y0) < other.getHeight()); y++)
            for (int x = x0; (x < width && (x-x0) < other.getWidth()); x++)
                if (other.get(x-x0,y-y0)) {
                    //char f = get(x, y);
                    //if (f && !was_removed) {
                    //    removeField(f);
                    //    was_removed = false;
                    //}
                    set(x, y, color);
                    area++;
                }

        reset();
    }

    void undraw(const Bitmap& other, int x0, int y0) {
        for (int y = y0; (y < height && (y-y0) < other.getHeight()); y++)
            for (int x = x0; (x < width && (x-x0) < other.getWidth()); x++)
                if (other.get(x-x0,y-y0)) {
                    set(x, y, 0);
                    area--;
                }

        reset();
    }

    size_t findNextField() {
        int x0, y0;

        if (fields > getTotalArea()) {
            printf("you have fucked up something son\n");
            return 0;
        }

        if (!findStartingPoint(x0, y0)) {
            if (area + filledArea != getTotalArea())
                printf("you have fucked up something son\n");
            return 0;
        }

        size_t filled = fillRecursive(x0, y0);
        fields++;
        filledArea += filled;
        return filled;
    }

    void reset() {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                if (get(x,y) <= fields) {
                    set(x,y,0);
                }

        fields = 0;
        filledArea = 0;
    }

private:
    bool findStartingPoint(int& x0, int& y0) {
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                if (get(x,y) == 0) {
                    x0 = x;
                    y0 = y;
                    return true;
                }

        return false;
    }

    size_t fillRecursive(int x, int y) {
        if (get(x,y) != 0)
            return 0;

        // mark the current pixel
        size_t sum = 1;
        set(x, y, fields+1);

        if (0 < x)
            sum += fillRecursive(x-1, y);
        if (0 < y)
            sum += fillRecursive(x, y-1);
        if (x < width-1)
            sum += fillRecursive(x+1, y);
        if (y < height-1)
            sum += fillRecursive(x, y+1);

        return sum;
    }

    void removeField(char f) {
        size_t area_cleared = 0;

        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                if (get(x, y) == f) {
                    set(x, y, 0);
                    area_cleared++;
                }

        if (area_cleared) {
            fields--;
            filledArea -= area_cleared;
        }
    }

};
