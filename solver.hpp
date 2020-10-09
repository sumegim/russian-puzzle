#include "shapeset.hpp"

typedef size_t attempt_counter_t;

struct solving_info_t {
    attempt_counter_t attempts;
    size_t solutions;
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
    enum fit_result_t{FIT, FAIL, SOLUTION, CONTINUE};

public:
    Solver(shapes_t& shapes, ShapeMap& canvas, ProgressNotifier& notifier)
        : ShapeSet(shapes)
        , canvas(canvas)
        , notifier(notifier)
        , info({.attempts = 0, .solutions = 0})
    {}

    void solve() {
        fitNextRecursive();
    }

private:
    bool tryToFitShape(const Shape& shape_to_fit, shape_desc_t& desc, bool skip_first = false) {

        size_t max_var = shape_to_fit.getNumOfVariants();
        const int max_y = canvas.getHeight();
        const int max_x = canvas.getWidth();

        for (int y = desc.y; y < max_y; y++) {
            for (int x = desc.x; x < max_x; x++) {
                for (size_t var = desc.var; var < max_var; var++) {
                    if (skip_first) {
                        skip_first = false;
                        continue;
                    }

                    const Bitmap& b = shape_to_fit.getVariant(var);

                    if ((y + b.getHeight()) > max_y)
                        continue;
                    if ((x + b.getWidth()) > max_x)
                        continue;

                    if (canvas.placeIfNoOverlap(b, x, y)) {
                        desc.var = var;
                        desc.x = x;
                        desc.y = y;
                        return true;
                    }
                }
                desc.var = 0;
            }
            desc.x = 0;
        }

        return false;
    }

    fit_result_t tryToFit(bool refit = false) {
        shape_desc_t desc;

        info.attempts++;
        if (refit)
            desc = undrawLast(canvas);
        else
            desc = {.var = 0, .x = 0, .y = 0};

        if (!tryToFitShape(shapes[descriptors.size()], desc, refit))
            return FAIL;
        else {
            descriptors.push_back(desc);
            notifier.handlePlacedShape(*this, info);
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
                undrawLast(canvas);
                return CONTINUE;
            }
            else
                return res;

            refit = true;
        } while (descriptors.size() > 0);

        return res;
    }
};
