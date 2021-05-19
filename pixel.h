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

class vecteur{
    double x,y;
public:
    vecteur();
    vecteur(double x0, double y0);
    vecteur(pixel p);
    double getx();
    double gety();
};

vecteur operator+(vecteur p1, vecteur p2);
vecteur operator-(vecteur p1, vecteur p2);
vecteur operator/(vecteur p, int k);
double ps(vecteur p1, vecteur p2);
vecteur normalise(vecteur p);
