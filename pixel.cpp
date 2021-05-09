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

pixel operator+(pixel p1, pixel p2){
    pixel somme(p1.getx()+p2.getx(),p1.gety()+p2.gety());
    return(somme);
}

pixel operator/(pixel p, int k){
    pixel d(p.getx()/k,p.gety()/k);
    return (d);
}

int ps(pixel p1, pixel p2){
    return(p1.getx()*p2.getx()+p1.gety()*p2.gety());
}

pixel normalise(pixel p){
    return(p/sqrt(ps(p,p)));
}

