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
            // On recupere la valeur de la composante r,g,b pour le pixel (i,j)
            colors[i+N*j][0] = int(img(x-floor(N/2)+i,(y-floor(N/2)+j)).r());
            colors[i+N*j][1] = int(img(x-floor(N/2)+i,(y-floor(N/2)+j)).g());
            colors[i+N*j][2] = int(img(x-floor(N/2)+i,(y-floor(N/2)+j)).b());
        }
    }
}



int patch::getx(){
    return p.getx();
}



int patch::gety(){
    return p.gety();
}





bool patch::inclu(int C[], int W){
    int x = p.getx();
    int y = p.gety();
    for (int i=0; i < N; i++){
        for (int j=0; j < N; j++){
            if (C[x+i-N/2 + W*(y+j-N/2)] == 0){
                return false;
            }
        }
    }
    return true;
}



float patch::distance(patch pat, int C[], int W){
    int i=p.getx();
    int j=p.gety();
    float dist = 0;
    for (int x=0; x<N; x++){
        for (int y=0; y<N; y++){
            if (C[i+x-N/2 + W*(j+y-N/2)] != 0){
                for (int k=0; k<3; k++){
                    int intermediaire = colors[x+N*y][k] - pat.colors[x+N*y][k];
                    dist += intermediaire*intermediaire;
                }
            }
        }
    }
    return dist;
}



patch remplacant(pixel pix, int C[], int W, int H, Img img){

    pixel pixel_fin;        // pixel central du patch a renvoyer
    float somme = 0;
    float somme_min = INF;  // valeur de la plus petite distance

    // On definit les coordonnes le patch associe au pixel passe en argument de la fonction
    int xc = pix.getx();
    int yc = pix.gety();
    patch patch_front(xc,yc,img);

    // On boucle sur tous les pixels de l'image dont le patch sera strictement inclu dans l'image
    for (int i=N/2; i < W-N/2; i++){
        for (int j=N/2; j < H-N/2; j++){
            pixel pixel_int(i,j);
            patch patch_int(i,j,img);
            if (patch_int.inclu(C, W)){
                somme = patch_front.distance(patch_int, C, W);
                if (somme < somme_min){
                    somme_min = somme ;
                    pixel_fin = pixel_int;
                }
            }
        }
    }
    return patch(pixel_fin.getx(),pixel_fin.gety(),img);
}
