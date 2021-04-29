// Projet réalisé par Louis Boilly

#include "outils.h"
#include "frontiere.h"

int main() {
    // Img est un type representant une image et img est le nom de la variable
    Img img;
    if (!load(img,srcPath("lena.png"))) // Stop si l'image n'est pas chargee
        return 0;
    openWindow(img.width(), img.height());
    display(img);
    endGraphics();
    return 0;
}
