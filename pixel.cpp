#include "pixel.h"

pixel::pixel(){
    x=0;
    y=0;
}

pixel::pixel(int x0, int y0){
    x=x0;
    y=y0;
}

int pixel::getx(){
    return x;
}

int pixel::gety(){
    return y;
}

void pixel::setx(int x0){
    x=x0;
}

void pixel::sety(int y0){
    y=y0;
}

int pixel::indice(int W){
    return(y*W+x);
}

pixel pixel::voisin(int dx0, int dy0){
    pixel p(x+dx0,y+dy0);
    return p;
}

int pixel::mouse(){
    return(getMouse(x,y));
}

vecteur::vecteur(){
    x=0;
    y=0;
}

vecteur::vecteur(double x0, double y0){
    x=x0;
    y=y0;
}

vecteur::vecteur(pixel p){
    x=p.getx();
    y=p.gety();
}

double vecteur::getx(){
    return(x);
}

double vecteur::gety(){
    return(y);
}

vecteur operator+(vecteur p1, vecteur p2){
    pixel somme(p1.getx()+p2.getx(),p1.gety()+p2.gety());
    return(somme);
}

vecteur operator-(vecteur p1, vecteur p2){
    vecteur diff(p1.getx()-p2.getx(),p1.gety()-p2.gety());
    return(diff);
}

vecteur operator/(vecteur p, int k){
    vecteur d(p.getx()/k,p.gety()/k);
    return (d);
}

double ps(vecteur p1, vecteur p2){
    return(p1.getx()*p2.getx()+p1.gety()*p2.gety());
}

vecteur normalise(vecteur p){
    return(p/sqrt(ps(p,p)));
}
