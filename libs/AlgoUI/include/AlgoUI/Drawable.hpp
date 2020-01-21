#pragma once
#include <AlgoUI/Canvas.hpp>
#include <mutex>


/*
 * Simple interface of a drawable class.
 *
 */
class Drawable
{
public:
    Drawable() = default;

    virtual void draw(Canvas& canvas) = 0;
};


/*
 * UpdatableDrawable: mixin-style extension of class Drawable
 * (and its subclasses) that allows to update the drawable object
 * in a different thread.
 *
 */
template <typename BASE>
class UpdatableDrawable : public BASE
{
    std::mutex accessControl;
public:

    void draw(Canvas& canvas) override
    {
        std::lock_guard<std::mutex> lock(accessControl);
        BASE::draw(canvas);
    }

    /* Arguments of this method should be compliant with arguments
     * of a BASE class constructor.
     */
    template <typename... Args>
    void update(Args&&... args)
    {
        BASE newDrawable(std::forward<Args>(args)...);

        std::lock_guard<std::mutex> lock(accessControl);
        std::swap<BASE>(*this, newDrawable);
    }

};

