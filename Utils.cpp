#include "Utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>

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

Vecteur Vecteur::inf(const Vecteur &other) const {
    return other.xyz[0] < xyz[0] && other.xyz[1] < xyz[1] && other.xyz[2] < xyz[2] ? other : *this;
}

Vecteur Vecteur::sup(const Vecteur &other) const {
    return other.xyz[0] > xyz[0] && other.xyz[1] > xyz[1] && other.xyz[2] > xyz[2] ? other : *this;
}

Vecteur Vecteur::cross(const Vecteur &v) const {
    return Vecteur((*this)[1] * v[2] - (*this)[2] * v[1],
                   (*this)[2] * v[0] - (*this)[0] * v[2],
                   (*this)[0] * v[1] - (*this)[1] * v[0]);
}

float Vecteur::norme() const {
    return sqrt((*this)[0] * (*this)[0] + (*this)[1] * (*this)[1] + (*this)[2] * (*this)[2]);
}

Vecteur Vecteur::operator*(float lambda) {
    return Vecteur((*this)[0] * lambda, (*this)[1] * lambda, (*this)[2] * lambda);
}

Triangle::Triangle(Vecteur sommet1, Vecteur sommet2, Vecteur sommet3) : sommet{sommet1, sommet2, sommet3} {}

Vecteur Triangle::operator[](int i) const {
    return sommet[i];
}

Vecteur &Triangle::operator[](int i) {
    return sommet[i];
}

Vecteur Triangle::normal() const {
    Vecteur a = (*this)[0],
            b = (*this)[1],
            c = (*this)[2];
    Vecteur ab(
            b[0] - a[0],
            b[1] - a[1],
            b[2] - a[2]);
    Vecteur ac(
            c[0] - a[0],
            c[1] - a[1],
            c[2] - a[2]);
    return ab.cross(ac) * (1 / (ab.cross(ac).norme()));
}

bool TriangleSoup::read(std::istream &in) {
    if (!in.good()) return false;
    std::string str;
    std::getline(in, str);
    Triangle triangle = Triangle(Vecteur(0, 0, 0), Vecteur(0, 0, 0), Vecteur(0, 0, 0));
    while (str != "") {
        if (str[0] != '#') {
            std::istringstream strStream(str);
            strStream >> triangle;
            triangles.push_back(triangle);
        }
        getline(in, str);
    }
    printf("Nb triangle %ld", triangles.size());
    return true;
}


std::istream &operator>>(std::istream &in, Vecteur &v) {
    in >> v[0] >> v[1] >> v[2];
    return in;
}

std::ostream &operator<<(std::ostream &out, Vecteur v) {
    out << v[0] << " " << v[1] << " " << v[2];
    return out;
}

std::ostream &operator<<(std::ostream &out, Triangle t) {
    out << t[0] << " " << t[1] << " " << t[2];
    return out;
}

std::istream &operator>>(std::istream &in, Triangle &t) {
    in >> t[0] >> t[1] >> t[2];
    return in;
}

Index::Index(int i0, int i1, int i2) {
    idx[0] = i0;
    idx[1] = i1;
    idx[2] = i2;
}

Index::Index(int indices[]) {
    idx[0] = indices[0];
    idx[1] = indices[1];
    idx[2] = indices[2];
}

int Index::operator[](int i) const { return idx[i]; }

int &Index::operator[](int i) { return idx[i]; }

bool Index::operator<(const Index &other) const {
    return (idx[0] < other.idx[0])
           || ((idx[0] == other.idx[0])
               && ((idx[1] < other.idx[1])
                   || ((idx[1] == other.idx[1])
                       && (idx[2] < other.idx[2]))));
}

bool Index::operator==(const Index &other) const {
    return (idx[0] == other.idx[0]) && (idx[1] == other.idx[1]) && (idx[2] == other.idx[2]);
}

TriangleSoupZipper::TriangleSoupZipper(const TriangleSoup &anInput,
                                       TriangleSoup &anOuput, Index size) :
        min(0, 0, 0), max(0, 0, 0) {
    size = size;
    for (auto triangleIteratorBegin = anInput.triangles.begin(),
                 triangleIteratorEnd = anInput.triangles.end();
         triangleIteratorBegin < triangleIteratorEnd;
         triangleIteratorBegin++) {
        for (auto sommetIteratorBegin = std::begin(triangleIteratorBegin->sommet),
                     sommetIteratorEnd = std::end(triangleIteratorBegin->sommet);
             sommetIteratorBegin < sommetIteratorEnd;
             sommetIteratorBegin++) {
            min = min.inf(*sommetIteratorBegin);
            max = max.sup(*sommetIteratorBegin);
        }
    }
    tailleBoiteX = (Vecteur(max[0] - min[0], 0, 0).norme());
    tailleBoiteY = (Vecteur(0, max[1] - min[1], 0).norme());
    tailleBoiteZ = (Vecteur(0, 0, max[2] - min[2]).norme());
    tailleMiniBoiteX = tailleBoiteX / size[0];
    tailleMiniBoiteY = tailleBoiteY / size[1];
    tailleMiniBoiteZ = tailleBoiteZ / size[2];
}

Index TriangleSoupZipper::index(const Vecteur &p) const {
    float xPure =  p[0]-min[0];
    float yPure =  p[1]-min[1];
    float zPure =  p[2]-min[2];

    return Index(floor(xPure/tailleMiniBoiteX),floor(yPure/tailleMiniBoiteY),floor(zPure/tailleMiniBoiteZ));
}

Vecteur TriangleSoupZipper::centroid(const Index &idx) const {
    return Vecteur(min[0]+idx[0]*tailleMiniBoiteX+tailleMiniBoiteX/2,
                   min[1]+idx[1]*tailleMiniBoiteY+tailleMiniBoiteY/2,
                   min[2]+idx[2]*tailleMiniBoiteZ+tailleMiniBoiteZ/2);
}
