#include "Utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

Vecteur::Vecteur(float x, float y, float z) {
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;
}

float Vecteur::operator[](int i) const {
    return xyz[i];
}

float& Vecteur::operator[](int i) {
    return xyz[i];
}

Triangle::Triangle(Vecteur sommet1, Vecteur sommet2, Vecteur sommet3):sommet{sommet1,sommet2,sommet3} {}

Vecteur Triangle::operator[](int i) const {
    return sommet[i];
}

Vecteur& Triangle::operator[](int i) {
    return sommet[i];
}

bool TriangleSoup::read(istream &in) {
    if ( ! in.good() ) return false;
    string str;
    std::getline(in,str);
    Triangle triangle = Triangle(Vecteur(0,0,0),Vecteur(0,0,0),Vecteur(0,0,0));
    while(str != ""){
        if (str[0] != '#') {
            istringstream strStream(str);
            strStream >> triangle;
            triangles.push_back(triangle);
        }
        getline(in,str);
    }
    printf("Nb triangle %ld",triangles.size());
    return true;
}

std::istream& operator>>( std::istream& in, Vecteur& v ){ in >> v[ 0 ] >> v[ 1 ] >> v[ 2 ]; return in;}
std::ostream& operator<<( std::ostream& out, Vecteur v ){ out << v[ 0 ] << " " << v[ 1 ] << " " << v[ 2 ]; return out; }
std::ostream& operator<<( std::ostream& out, Triangle t ){ out << t[ 0 ] << " " << t[ 1 ] << " " << t[ 2 ]; return out;}
std::istream& operator>>( std::istream& in, Triangle& t ){ in >> t[ 0 ] >> t[ 1 ] >> t[ 2 ]; return in;}