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

pixel gradient(Img I, pixel p, int W, int H){
    int x=p.getx();
    int y=p.gety();
    int dx,dy;
    if (x==0){
        dx=I[indice(W,x+1,y)]-I[indice(W,x,y)];
    }
    else{
        if (x==W-1){
            dx=I[indice(W,x,y)]-I[indice(W,x-1,y)];
        }
        else{
            int dx1=I[indice(W,x+1,y)]-I[indice(W,x,y)];
            int dx2=I[indice(W,x,y)]-I[indice(W,x-1,y)];
            if (abs(dx1)>=abs(dx2)){
                dx=dx1;
            }
            else{
                dx=dx2;
            }
        }
    }
    if (y==0){
        dy=I[indice(W,x,y+1)]-I[indice(W,x,y)];
    }
    else{
        if (x==H-1){
            dy=I[indice(W,x,y)]-I[indice(W,x,y-1)];
        }
        else{
            int dy1=I[indice(W,x,y+1)]-I[indice(W,x,y)];
            int dy2=I[indice(W,x,y)]-I[indice(W,x,y-1)];
            if (abs(dy1)>=abs(dy2)){
                dy=dy1;
            }
            else{
                dy=dy2;
            }
        }
    }
    pixel grad(dx,dy);
    return(grad);
}

void priority(Img I, int P[], frontiere f, int C[], int W, int H){
    for (int i=0; i<f.gettaille(); i++){
        int c=0;
        for (int j=-N/2; j<=N/2; j++){
            for (int k=-N/2; k<=N/2; k++){
                pixel q((f.get(i)).getx()+j,(f.get(i)).gety()+k);
                c=c+C[q.indice(W)];
            }
        }
        c=c/(pow(N,2));
        P[(f.get(i)).indice(W)]=c+abs(ps(orthogonal(gradient(I, f.get(i),W,H)),normale(f.get(i),f)))/alpha;
    }
}

frontiere def_frontiere(){
    Img img;
    frontiere f;
    if (load(img,srcPath("lena.png"))){ // Stop si l'image n'est pas chargee
        int width=img.width();
        int height=img.height();
        openWindow(width, height);
        display(img);
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
            drawLine(prec.getx(),prec.gety(),actuel.getx(),actuel.gety(),RED);
            //ajout(f,prec,actuel);
            f.affiche(RED);
            // Mise a jour des variables x_prec,y_prec
            prec=actuel;
            // Fermeture du polygone si le clic est droit
            if (i==3)
                // Trace du segment reliant le premier sommet et le sommet qui vient d'etre clique
                drawLine(p0.getx(),p0.gety(),actuel.getx(),actuel.gety(),RED);
        }
        endGraphics();
    }
}

int main() {
    // Img est un type representant une image et img est le nom de la variable
    def_frontiere();
    cout << "test" << endl;
    return 0;
}
