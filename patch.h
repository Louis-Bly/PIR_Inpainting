#pragma once

#include "pixel.h"
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include "frontiere.h"

int const N=9; //N DOIT être impair

typedef Image<Color> Img;

class patch{
    pixel p;
    int colors[N*N][3]; //3 -> rgb
public:
    patch();
    patch(int x, int y, Img img);
    pixel getpix(){return p;};
    void couleur(int i, int j, int* col);
    patch remplacant(pixel p, Img img);
};

void colle(patch pat, pixel pi, Img img, int* C);
