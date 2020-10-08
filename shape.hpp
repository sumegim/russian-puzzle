#include "bitmap.hpp"

#include <vector>

class Shape : public Bitmap
{

public:
    Shape(const Bitmap& bitmap)
        : Bitmap(bitmap)
    {}

};
