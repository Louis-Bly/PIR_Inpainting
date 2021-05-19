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

patch remplacant(pixel p, Img img){

}
