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
};

std::ostream &operator<<(std::ostream &out, Vecteur v);

std::istream &operator>>(std::istream &in, Vecteur &v);

struct Triangle {
    Vecteur sommet[3];

    Triangle(Vecteur sommet1, Vecteur sommet2, Vecteur sommet3);

    Vecteur operator[](int i) const;

    Vecteur &operator[](int i);
};

std::ostream &operator<<(std::ostream &out, Triangle t);

std::istream &operator>>(std::istream &in, Triangle &t);

struct TriangleSoup {
    std::vector<Triangle> triangles; // les triangles
    TriangleSoup() {}

    bool read(std::istream &in);
};