#include "bitmap.hpp"

#include <vector>

class Shape
{
    std::vector<Bitmap> variants;

public:
    Shape(Bitmap bitmap) {
        for (size_t i = 0; i < 4; i++) {
            if(!isContained(bitmap))
                variants.push_back(bitmap);
            if(!isContained(bitmap.flipX()))
                variants.push_back(bitmap.flipX());
            if(!isContained(bitmap.flipY()))
                variants.push_back(bitmap.flipY());
            if(!isContained(bitmap.flipY().flipX()))
                variants.push_back(bitmap.flipY().flipX());
            bitmap = bitmap.rotate();
        }
    }

    const Bitmap& getVariant(size_t n) const {
        return variants[n];
    }

    size_t getNumOfVariants() const {
        return variants.size();
    }

private:
    bool isContained(const Bitmap& bitmap) {
        for (size_t i = 0; i < variants.size(); i++)
            if (variants[i] == bitmap)
                return true;

        return false;
    }

};



class ShapeMap : public Bitmap {

public:
    ShapeMap(int width, int height, char color = 'X', const char* data = nullptr)
        : Bitmap(width, height, color, data)
    {}

    bool willDrawOver(const Bitmap& other, int x0, int y0) {
        const int max_y = std::min(height, other.getHeight() + y0);
        const int max_x = std::min(width, other.getWidth() + x0);

        for (int y = y0; y < max_y; y++)
            for (int x = x0; x < max_x; x++)
                if (other.get(x-x0,y-y0) && get(x, y))
                    return true;

        return false;
    }

    bool placeIfNoOverlap(const Bitmap& other, int x0, int y0) {
        if (willDrawOver(other, x0, y0))
            return false;

        draw(other, x0, y0);
        return true;
    }

    bool operator==(const ShapeMap& other) {
        return (static_cast<Bitmap>(*this) == other);
    }
};
