#pragma once

#include "pixel.h"
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include "frontiere.h"

int const N=9; //N DOIT être impair
const float INF = 1.0f/0.0; // Infini en float

typedef Image<Color> Img;

class patch{
    pixel p;
    int colors[N*N][3]; //3 -> rgb
public:
    patch();
    patch(int x, int y, Img img);
    int getx();
    int gety();
    bool inclu(double C[], int W); // Renvoi vrai si tous les pixels sont dans l'image source, et non dans l'image vide a completer
    float distance(patch pat, double C[], int W); // calcul la distance euclidienne RGB entre les deux patchs
                                               // "pat" est le patch remplacant
    pixel getpix(){return p;};
    void couleur(int i, int j, int* col);
};

void colle(patch pat, pixel pi, Img img, double* C, float newC, frontiere front);
patch remplacant(pixel pix, double C[], int W, int H, Img img);  // Renvoie le meilleur patch associe au patch centre en p
