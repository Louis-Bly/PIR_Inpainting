#pragma once
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include <iostream>

using namespace Imagine;
using namespace std;

int const N=9;
int const alpha=255;

class pixel{
    int x,y;
public:
    pixel();
    pixel(int x0, int y0);
    int getx();
    int gety();
    void setx(int x0);
    void sety(int y0);
    int indice(int W);
    pixel voisin(int dx0, int dy0);
    int mouse();
};

pixel operator+(pixel p1, pixel p2);
pixel operator/(pixel p, int k);
int ps(pixel p1, pixel p2);
pixel normalise(pixel p);
