#include "patch.h"



patch::patch(){
    p = pixel();
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int c=0;c<3;c++){
                colors[i+N*j][c] = 0;
            }
        }
    }
}

patch::patch(int x, int y, Img img){
    p = pixel(x,y);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
        colors[i+N*j][0] = int(img(x-floor(N/2)+i,(y-floor(N/2)+j)).r());
        colors[i+N*j][1] = int(img(x-floor(N/2)+i,(y-floor(N/2)+j)).g());
        colors[i+N*j][2] = int(img(x-floor(N/2)+i,(y-floor(N/2)+j)).b());
        }
    }
}


void patch::couleur(int i, int j, int* col){
    for(int k=0; k<3; k++){
        col[k] = colors[i+N*j][k];
    }
}

patch remplacant(pixel p, Img img){

}


void colle(patch pat, pixel pi, Img img, int* C, float newC, frontiere front){
    int x = pi.getx();
    int y = pi.gety();
    int W = img.width();
    int col[3] = {0,0,0};
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(C[int(x+i-floor(N/2)+W*(y+j-floor(N/2)))] == 0){
                pat.couleur(i,j,col);
                for(int k=0;k<3;k++){
                    img(x+i-floor(N/2),y+j-floor(N/2))[k] = col[k]; //On colorie la nouvelle zone
                }
                C[int(x+i-floor(N/2)+W*(y+j-floor(N/2)))] = newC; //On actualise la confiance
            }
        }
    }
    front.del_patch(pixel(pi.getx()-1,pi.gety()-1));
    front.del_patch(pixel(pi.getx()-1,pi.gety()+1));
    front.del_patch(pixel(pi.getx()+1,pi.gety()+1));
    front.del_patch(pixel(pi.getx()+1,pi.gety()-1));
    for(int i=0;i<N+2;i++){
        for(int j=0;j<N+2;j++){
            if(C[int(x+i-floor(N/2)-1+W*(y+j-floor(N/2)-1))] == 0){
                front.add(pixel(x+i-floor(N/2)-1,y+j-floor(N/2)-1)); //On renouvelle la frontière
            }
        }
    }
}
