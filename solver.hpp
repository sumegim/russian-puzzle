#include "shapeset.hpp"
#include "flood-filler.hpp"

typedef size_t attempt_counter_t;

struct solving_info_t {
    attempt_counter_t attempts;
    attempt_counter_t fits;
    size_t solutions;
    size_t iterations;
};

struct ProgressNotifier {
    virtual void handlePlacedShape(const ShapeSet& solution, solving_info_t info) {}
    virtual void handleSolution(const ShapeSet& solution, solving_info_t info) {}
};



class Solver : public ShapeSet
{
    ShapeMap& canvas;
    ProgressNotifier& notifier;
    solving_info_t info;
    FloodFiller flooder;
    enum fit_result_t{FIT, FAIL, SOLUTION, CONTINUE};
    int minX, minY, maxX, maxY;

public:
    Solver(shapes_t& shapes, ShapeMap& canvas, ProgressNotifier& notifier)
        : ShapeSet(shapes)
        , canvas(canvas)
        , notifier(notifier)
        , info({.attempts = 0, .fits = 0, .solutions = 0, .iterations = 0})
        , flooder(canvas.getWidth(), canvas.getHeight())
        , minX(0)
        , minY(0)
        , maxX(canvas.getWidth()-1)
        , maxY(canvas.getHeight()-1)
    {}

    void solve() {
        fitNextRecursive();
    }

private:
    bool tryToFitShape(const Shape& shape_to_fit, shape_desc_t& desc, bool skip_first = false) {
        const size_t max_var = shape_to_fit.getNumOfVariants();

        if (skip_first)
            desc.x++;

        for (size_t var = desc.var; var < max_var; var++) {
            const Bitmap& b = shape_to_fit.getVariant(var);
            const int max_y = (maxY + 1) - (b.getHeight() - 1);
            const int max_x = (maxX + 1) - (b.getWidth() - 1);

            for (int y = desc.y; y < max_y; y++) {
                for (int x = desc.x; x < max_x; x++) {
                    info.iterations++;

                    if (canvas.placeIfNoOverlap(b, x, y)) {
                        flooder.draw(b, x, y);
                        desc.var = var;
                        desc.x = x;
                        desc.y = y;
                        descriptors.push_back(desc);
                        return true;
                    }
                }
                desc.x = minX;
            }
            desc.y = minY;
        }

        return false;
    }

    fit_result_t tryToFit(bool refit = false) {
        bool fitted;
        shape_desc_t desc;

        updateRowCol();

        if (refit)
            desc = undrawLast();
        else
            desc = {.var = 0, .x = minX, .y = minY};

        do {
            info.attempts++;
            fitted = tryToFitShape(shapes[descriptors.size()], desc, refit);

            if (fitted) {
                refit = !fieldsAreOk();
                notifier.handlePlacedShape(*this, info);

                if (refit)
                    undrawLast();
            }
        } while(fitted && refit);

        info.fits++;

        if (!fitted)
            return FAIL;
        else {
            return ((descriptors.size() == shapes.size()) ? SOLUTION : FIT);
        }
    }

    fit_result_t fitNextRecursive(int lvl = 0, bool refit = false) {
        fit_result_t res;

        do {
            res = tryToFit(refit);

            if (res == FIT)
                res = fitNextRecursive(lvl+1);
            else if (res == SOLUTION) {
                info.solutions++;
                notifier.handleSolution(*this, info);
                undrawLast();
                return CONTINUE;
            }
            else
                return res;

            refit = true;
        } while (descriptors.size() > 0);

        return res;
    }

    shape_desc_t undrawLast() {
        shape_desc_t desc = ShapeSet::undrawLast(canvas);
        const Bitmap& b = shapes[descriptors.size()].getVariant(desc.var);
        flooder.undraw(b, desc.x, desc.y);
        return desc;
    }

    bool fieldsAreOk() {
        size_t filled;

        while ((filled = flooder.findNextField())) {
            if ((filled % 5) != 0)
                return false;
        }

        return true;
    }

    bool isColFilled (int y) {
        for (int x = 0; x < canvas.getWidth(); x++)
            if (!canvas.get(x, y))
                return false;

        return true;
    }

    bool isRowFilled (int x) {
        for (int y = 0; y < canvas.getHeight(); y++)
            if (!canvas.get(x, y))
                return false;

        return true;
    }

    void updateRowCol() {
        // cols
        minY = 0;
        while (isColFilled(minY))
            minY++;

        maxY = (canvas.getHeight() - 1);
        while (isColFilled(maxY))
            maxY--;

        // rows
        minX = 0;
        while (isRowFilled(minX))
            minX++;

        maxX = (canvas.getWidth() - 1);
        while (isRowFilled(maxX))
            maxX--;
    }
};
