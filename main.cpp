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

void ajout(frontiere &f, pixel p1, pixel p2, int W, double C[]){
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

pixel orthogonal(pixel p){
    pixel ortho(p.gety(),p.getx());
    return(ortho);
}

vecteur orthogonal(vecteur p){
    vecteur ortho(p.gety(),p.getx());
    return(ortho);
}

vecteur normale(pixel p, frontiere f){
    pixel voisin[2];
    int nb= f.voisins(p,voisin);
    if (nb==1)
        return(normalise(orthogonal((voisin[0]-p)/2)));
    else
        return(normalise(orthogonal((voisin[0]-voisin[1])/2)));
}

pixel gradient(byte R[], byte G[], byte B[], pixel p, int W, int H){
    int x=p.getx();
    int y=p.gety();
    pixel grad;
    int dx1=0, dx2=0, dy1=0, dy2=0;
    if (x>0)
        dx1=(R[indice(W,x,y)]-R[indice(W,x-1,y)]+G[indice(W,x,y)]-G[indice(W,x-1,y)]+B[indice(W,x,y)]-B[indice(W,x-1,y)])/3;
    if (x<W-1)
        dx2=(R[indice(W,x+1,y)]-R[indice(W,x,y)]+G[indice(W,x+1,y)]-G[indice(W,x,y)+B[indice(W,x+1,y)]-B[indice(W,x,y)]])/3;
    if (abs(dx1)>=abs(dx2))
        grad.setx(dx1);
    else
        grad.setx(dx2);
    if (y>0)
        dy1=(R[indice(W,x,y)]-R[indice(W,x,y-1)]+G[indice(W,x,y)]-G[indice(W,x,y-1)]+B[indice(W,x,y)]-B[indice(W,x,y-1)])/3;
    if (y<H-1)
        dy2=(R[indice(W,x,y+1)]-R[indice(W,x,y)]+G[indice(W,x,y+1)]-G[indice(W,x,y)+B[indice(W,x,y+1)]-B[indice(W,x,y)]])/3;
    if (abs(dy1)>=abs(dy2))
        grad.sety(dy1);
    else
        grad.sety(dy2);
    return(grad);
}

void priority(byte R[], byte G[], byte B[], double P[], frontiere f, double C[], int W,int H){
    for (int i=0; i<f.gettaille(); i++){
        int c=0;
        for (int j=-N/2; j<=N/2; j++){
            for (int k=-N/2; k<=N/2; k++){
                pixel q((f.get(i)).getx()+j,(f.get(i)).gety()+k);
                c=c+C[q.indice(W)];
            }
        }
        c=c/(pow(N,2));
        C[indice(W,f.get(i).getx(),f.get(i).gety())]=c;
        P[(f.get(i)).indice(W)]=c+abs(ps(orthogonal(gradient(R,G,B,f.get(i),W,H)),normale(f.get(i),f)))/alpha;
    }
}

void init_confiance(double C[], int W, int H){
    pixel* chemin= new pixel[W*H];
    chemin[0].mouse();
    int compteur=1;
    int boucle=0;
    while (compteur>boucle && compteur<W*H){
        int x=chemin[boucle].getx();
        int y=chemin[boucle].gety();
        if (x>0 && C[indice(W,x-1,y)]!=0){
            C[indice(W,x-1,y)]=0;
            chemin[compteur].setx(x-1);
            chemin[compteur].sety(y);
            compteur+=1;
        }
        if (x<W-1 && C[indice(W,x+1,y)]!=0){
            C[indice(W,x+1,y)]=0;
            chemin[compteur].setx(x+1);
            chemin[compteur].sety(y);
            compteur+=1;
        }
        if (y>0 && C[indice(W,x,y-1)]!=0){
            C[indice(W,x,y-1)]=0;
            chemin[compteur].setx(x);
            chemin[compteur].sety(y-1);
            compteur+=1;
        }
        if (y<H-1 && C[indice(W,x,y+1)]!=0){
            C[indice(W,x,y+1)]=0;
            chemin[compteur].setx(x);
            chemin[compteur].sety(y+1);
            compteur+=1;
        }
        boucle+=1;
    }
}


void init_affichage(int H, int W, double C[]){
    for (int y=0;y<H;y++){
        for (int x=0;x<W;x++){
            if (C[indice(W,x,y)]==0)
                fillRect(x,y,1,1,WHITE);
        }
    }
}

frontiere def_frontiere(int width, int height, double C[]){
    frontiere f(width,height);
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
            ajout(f,actuel,p0,width,C);
            f.affiche(RED);
            //drawLine(p0.getx(),p0.gety(),actuel.getx(),actuel.gety(),RED);
        }
    }
    return f;
}

int main() {
    // Img est un type representant une image et img est le nom de la variable
    Img img;
    if (load(img,srcPath("Image_Couleur_Test.jpg"))){ // Stop si l'image n'est pas chargee
        int width=img.width();
        int height=img.height();
        openWindow(width, height);
        display(img);
        double* C= new double[width*height];
        for (int i=0;i<width*height;i++){
            C[i]=1;
        }
    frontiere f = def_frontiere(width, height, C);
    init_confiance(C,width, height);
    init_affichage(height,width,C);
    endGraphics();
    }
    return 0;
}
