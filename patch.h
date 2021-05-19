#pragma once

#include "pixel.h"
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>

int const N=9; //N DOIT être impair

typedef Image<Color> Img;

class patch{
    pixel p;
    int colors[N*N][3]; //3 -> rgb
public:
    patch();
    patch(int x, int y, Img img);
    patch remplacant(pixel p, Img img);
};
