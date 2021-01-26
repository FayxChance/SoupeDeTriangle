/// \file Utils.h
#include <vector>
#include <QGLViewer/qglviewer.h>
#include <iostream>
struct Vecteur {
    float xyz[ 3 ]; // les composantes
    Vecteur( float x, float y, float z );

    float  operator[]( int i ) const;

    float& operator[]( int i );
}

std::ostream& operator<<( std::ostream& out, Vecteur v ){ out << v[ 0 ] << " " << v[ 1 ] << " " << v[ 2 ]; }
std::istream& operator>>( std::istream& in, Vecteur& v ){ in >> v[ 0 ] >> v[ 1 ] >> v[ 2 ]; }

struct Triangle {
    Vecteur sommet[3];
    Triangle(Vecteur sommet1, Vecteur sommet2, Vecteur sommet3);
}

std::ostream& operator<<( std::ostream& out, Triangle v ){ out << v[ 0 ] << " " << v[ 1 ] << " " << v[ 2 ]; }
std::istream& operator>>( std::istream& in, Triangle& v ){ in >> v[ 0 ] >> v[ 1 ] >> v[ 2 ]; }

