#include "Utils.h"

using namespace std;

Vecteur::Vecteur(float x, float y, float z) {
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;
}

float Vecteur::operator[](int i) const {
    return xyz[i];
}

float &Vecteur::operator[](int i) {
    return xyz[i];
}

Triangle::Triangle(Vecteur sommet1, Vecteur sommet2, Vecteur sommet3) {
    sommet[0] = sommet1;
    sommet[1] = sommet2;
    sommet[2] = sommet3;
}

Vecteur Triangle::operator[](int i) const {
    return sommet[i];
}

Vecteur &Triangle::operator[](int i) {
    return sommet[i];
}