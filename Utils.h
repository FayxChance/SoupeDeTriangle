/// \file Utils.h
#pragma once

#include <vector>
#include <QGLViewer/qglviewer.h>
#include <iostream>
#include <fstream>
#include <sstream>

struct Vecteur {
    float xyz[3]{};

    Vecteur(float x, float y, float z);

    float operator[](int i) const;

    float &operator[](int i);

    Vecteur inf(const Vecteur &other) const;

    Vecteur sup(const Vecteur &other) const;

    Vecteur cross(const Vecteur &v) const;

    float norme() const;

    Vecteur operator*(float lambda);
};

std::ostream &operator<<(std::ostream &out, Vecteur v);

std::istream &operator>>(std::istream &in, Vecteur &v);

struct Triangle {
    Vecteur sommet[3];

    Triangle(Vecteur sommet1, Vecteur sommet2, Vecteur sommet3);

    Vecteur operator[](int i) const;

    Vecteur &operator[](int i);

    Vecteur normal() const;
};

std::ostream &operator<<(std::ostream &out, Triangle t);

std::istream &operator>>(std::istream &in, Triangle &t);

struct TriangleSoup {
    std::vector<Triangle> triangles; // les triangles

    TriangleSoup() {};

    bool read(std::istream &in);
};

struct Index {
    int idx[3];

    Index() {}

    Index(int i0, int i1, int i2);

    Index(int indices[]);

    int operator[](int i) const;

    int &operator[](int i);

    bool operator<(const Index &other) const;

    bool operator==(const Index &other) const;

    bool operator!=(const Index &other) const;

    };

struct TriangleSoupZipper {

    Index size;
    Vecteur min;
    Vecteur max;
    TriangleSoup& in;
    TriangleSoup& out;
    float tailleBoiteX, tailleBoiteY, tailleBoiteZ;
    float tailleMiniBoiteX, tailleMiniBoiteY, tailleMiniBoiteZ;

    TriangleSoupZipper(const TriangleSoup &anInput,
                       TriangleSoup &anOuput,
                       Index size);

    Index index(const Vecteur &p) const;

    Vecteur centroid(const Index &idx) const;

    void zip();
};