#pragma once
#include "pixel.h"

class frontiere{
    pixel* front;
    int taille;
public:
    frontiere();
    int gettaille();
    pixel get(int i);
    bool empty();
    void add(pixel p);
    void del(int k);
    int voisins(pixel p, pixel voisin[]);
    void del_patch(pixel p);
    void affiche(Color c);
};
