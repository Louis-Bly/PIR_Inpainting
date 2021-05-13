// Projet réalisé par Louis Boilly

#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
#include <iostream>
#include "frontiere.h"

using namespace Imagine;
using namespace std;

typedef Image<byte> Img;

int indice(int W, int x, int y){
    return(y*W+x);
}

void ajout(frontiere f, pixel p1, pixel p2, int W, int C[]){
    double dy=p2.gety()-p1.gety();
    double dx=p2.getx()-p1.getx();
    double coeff_dir=dy/dx;
    double coor_orig=p1.gety()-coeff_dir*p1.getx();
    int x0=p1.getx();
    int y0=p1.gety();
    int dxx;
    int dyy;
    if (dx>=0)
        dxx=1;
    else
        dxx=-1;
    if (dy>=0)
        dyy=1;
    else
        dyy=-1;
    while (x0!=p2.getx()){
        int y1=coeff_dir*(x0+dxx)+coor_orig;
        bool b=true;
        while (b){
            if (C[indice(W,x0,y0)]==1){
                pixel p(x0,y0);
                f.add(p);
                C[indice(W,x0,y0)]=0;
            }
            if (y0==y1)
               b=false;
            else
                y0=y0+dyy;
        }
        x0=x0+dxx;
        f.affiche(RED);
    }
}

pixel normale(pixel p, frontiere f){
    pixel voisin[2];
    int nb= f.voisins(p,voisin);
    if (nb==1)
        return(normalise((voisin[0]+p)/2));
    else
        return(normalise((voisin[0]+voisin[1])/2));
}

pixel orthogonal(pixel p){
    pixel ortho(p.gety(),p.getx());
    return(ortho);
}

pixel gradient(Img I, pixel p, int W){
    int dx=max(I[indice(W,p.getx()+1,p.gety())]-I[indice(W,p.getx(),p.gety())],I[indice(W,p.getx(),p.gety())]-I[indice(W,p.getx()-1,p.gety())]);
}

void priority(Img I, int P[], frontiere f, int C[], int W){
    for (int i=0; i<f.gettaille(); i++){
        int c=0;
        for (int j=-N/2; j<=N/2; j++){
            for (int k=-N/2; k<=N/2; k++){
                pixel q((f.get(i)).getx()+j,(f.get(i)).gety()+k);
                c=c+C[q.indice(W)];
            }
        }
        c=c/(pow(N,2));
        P[(f.get(i)).indice(W)]=c+abs(ps(orthogonal(gradient(I, f.get(i),W)),normale(f.get(i),f)))/alpha;
    }
}

void init_confiance(int H, int W, int C[]){
    int dedans;
    for (int y=0;y<H;y++) {
        dedans = 0;
        for (int x=0;x<W;x++){
            if (dedans==1){
                if (C[indice(W,x,y)]==0) dedans = 0;
                else C[indice(W,x,y)]=0;
            }
            else {
                if (C[indice(W,x,y)]==0) dedans = 1;
                else C[indice(W,x,y)]=1;
            }
        }
    }
}

void init_affichage(int H, int W, int C[]){
    for (int y=0;y<H;y++){
        for (int x=0;x<W;x++){
            if (C[indice(W,x,y)]==0)
                fillRect(x,y,1,1,WHITE);
        }
    }
}

frontiere def_frontiere(int width, int C[]){
    frontiere f;
    pixel p0, // Premier sommet
          prec, // Sommet precedent
          actuel; // Sommet qui vient d'etre clique
    int i; // Si i=1 alors le clic est un clic gauche, si i=3 alors le clic est un clic droit
    // Initialisation du premier sommet
    i = p0.mouse();
    // Initialisation des variables x_prec et y_prec
    prec=p0;
    // Boucle principale qui s'execute tant que le polygone n'est pas ferme
    while (i==1)
    {
        // Position et nature du nouveau clic
        i = actuel.mouse();
        // Trace du nouveau segment reliant le sommet precedent et le sommet qui vient d'etre clique
        //drawLine(prec.getx(),prec.gety(),actuel.getx(),actuel.gety(),GREEN);
        ajout(f,prec,actuel,width,C);
        f.affiche(RED);
        // Mise a jour des variables x_prec,y_prec
        prec=actuel;
        // Fermeture du polygone si le clic est droit
        if (i==3){
            // Trace du segment reliant le premier sommet et le sommet qui vient d'etre clique
            ajout(f,p0,actuel,width,C);
            f.affiche(RED);
            //drawLine(p0.getx(),p0.gety(),actuel.getx(),actuel.gety(),RED);
        }
    }
    return f;
}

int main() {
    // Img est un type representant une image et img est le nom de la variable
    Img img;
    if (load(img,srcPath("lena.png"))){ // Stop si l'image n'est pas chargee
        int width=img.width();
        int height=img.height();
        openWindow(width, height);
        display(img);
        int* C= new int[width*height];
        for (int i=0;i<width*height;i++){
            C[i]=1;
        }
    frontiere f = def_frontiere(width, C);
    init_confiance(height,width,C);
    init_affichage(height,width,C);
    endGraphics();
    }
    return 0;
}
