#include "frontiere.h"

frontiere::frontiere(){
    front = new pixel[1000];
    taille=0;
}

int frontiere::gettaille(){
    return(taille);
}

pixel frontiere::get(int i){
    return(front[i]);
}

bool frontiere::empty(){
    return(taille==0);
}

void frontiere::add(pixel p){
    front[taille]=p;
    taille++;
}

void frontiere::del(int k){
    if (taille>1)
        front[k]=front[taille-1];
    taille--;
}

int frontiere::voisins(pixel p, pixel voisin[]){
    int j=0;
    for (int i=0;i<taille;i++){
        if ((pow(front[i].getx()-p.getx(),2)+pow(front[i].gety()-p.gety(),2))==1){
            voisin[j]=front[i];
            j++;
        }
    }
    return(j);
}

void frontiere::del_patch(pixel p){
    int k=0;
    while(k<taille){
        if ((abs(front[k].getx()-p.getx()))<N/2 && (abs(front[k].gety()-p.gety()))<N/2)
            del(k);
        else
            k++;
    }
}

void frontiere::affiche(Color c){
    for (int i=0;i<taille;i++){
        fillRect(front[i].getx(),front[i].gety(),1,1,c);
    }
}

bool operator==(pixel p1,pixel p2){
    return(p1.getx()==p2.getx() && p1.gety()==p2.gety());
}
