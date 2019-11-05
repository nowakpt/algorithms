#pragma once
#include "Canvas.hpp"


class Drawable
{
public:
    Drawable() = default;

    virtual void draw(Canvas& canvas) = 0;
};

