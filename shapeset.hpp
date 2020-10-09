#include "shape.hpp"

struct shape_desc_t {
    size_t var;
    int x;
    int y;
};

typedef const std::vector<Shape> shapes_t;
typedef std::vector<shape_desc_t> descriptors_t;

struct ShapeSet {
    shapes_t& shapes;
    descriptors_t descriptors;

public:
    ShapeSet(shapes_t& shapes)
        : shapes(shapes)
        , descriptors()
    {}

    ShapeSet(shapes_t& shapes, const descriptors_t& descriptors)
        : shapes(shapes)
        , descriptors(descriptors)
    {}

    void draw(Bitmap& canvas) const {
        canvas.clear();

        for (size_t i = 0; i < descriptors.size(); i++)
            canvas.drawColor(shapes[i].getVariant(descriptors[i].var),
                             descriptors[i].x,
                             descriptors[i].y);
    }

    bool isValid() {
        ShapeMap canvas(10, 6);

        for (size_t i = 0; i < descriptors.size(); i++) {
            if (!canvas.placeIfNoOverlap(
                shapes[i].getVariant(descriptors[i].var),
                descriptors[i].x,
                descriptors[i].y)
            )
                return false;
        }

        return true;
    }

    shape_desc_t undrawLast(ShapeMap& canvas) {
        shape_desc_t desc = descriptors.back();
        size_t i = (descriptors.size() - 1);

        canvas.undraw(shapes[i].getVariant(desc.var), desc.x, desc.y);
        descriptors.pop_back();
        return desc;
    }
};
