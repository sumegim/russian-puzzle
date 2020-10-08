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
