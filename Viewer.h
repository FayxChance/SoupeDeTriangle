/// \file Viewer.h
#pragma once

#include <vector>
#include <QGLViewer/qglviewer.h>
#include "Utils.h"

class Viewer : public QGLViewer {
public:
    const TriangleSoup * soupe;
    Viewer(const TriangleSoup* soupe = 0):QGLViewer(),soupe(soupe) {}
    Viewer() : QGLViewer() {}


protected :
    /// Called at each draw of the window
    virtual void draw();

    /// Called before the first draw
    virtual void init();

    /// Called when pressing help.
    virtual QString helpString() const;
};
