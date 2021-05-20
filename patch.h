#pragma once

#include "pixel.h"
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>

int const N=9; //N DOIT être impair
const float INF = 1.0f/0.0; // Infini en float

typedef Image<Color> Img;

class patch{
    pixel p;
    int colors[N*N][3]; //Couleurs RGB(3) pour chacun des N*N pixels du patch
public:
    patch(); // Constructeur vide initialisant toutes les variables a 0
    patch(int x, int y, Img img); // Patch ayant pour centre le pixel (x,y)
    int getx();
    int gety();
    bool inclu(int C[], int W); // Renvoi vrai si tous les pixels sont dans l'image source, et non dans l'image vide a completer
    float distance(patch pat, int C[], int W); // calcul la distance euclidienne RGB entre les deux patchs
                                               // "pat" est le patch remplacant
    patch remplacant(pixel pix, int C[], int W, int H, Img img);  // Renvoie le meilleur patch associe au patch centre en p
};
