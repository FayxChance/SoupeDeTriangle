/// \file Viewer.cpp
#include "Viewer.h"

using namespace std;

// Draws a tetrahedron with 4 colors.
void Viewer::draw() {
    float colorBronzeDiff[4] = {0.8, 0.6, 0.0, 1.0};
    float colorBronzeSpec[4] = {1.0, 1.0, 0.4, 1.0};
    float colorNull[4] = {0.0, 0.0, 0.0, 1.0};
    /*float colorRedDiff[4] = {1.0, 0.0, 0.0, 1.0};
    float colorGreenDiff[4] = {0.0, 1.0, 0.0, 1.0};
    float colorBlueDiff[4] = {0.0, 0.0, 1.0, 1.0};*/
    int i = 0;
    // Draws triangles given by 3 vertices.
    glBegin(GL_TRIANGLES);
    glColor4fv(colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0f);
    for (auto triangleIteratorBegin = soupe->triangles.begin(),
                 triangleIteratorEnd = soupe->triangles.end();
         triangleIteratorBegin < triangleIteratorEnd;
         triangleIteratorBegin++) {
        i++;
        const Triangle &triangle = *triangleIteratorBegin;

        Vecteur n = triangle.normal();
        glNormal3f(n[0], n[1], n[2]);
        for (auto sommetIteratorBegin = std::begin(triangleIteratorBegin->sommet),
                     sommetIteratorEnd = std::end(triangleIteratorBegin->sommet);
             sommetIteratorBegin < sommetIteratorEnd;
             sommetIteratorBegin++) {
            glVertex3f(sommetIteratorBegin->xyz[0],
                       sommetIteratorBegin->xyz[1],
                       sommetIteratorBegin->xyz[2]);
        }
    }
    glEnd();
}


void Viewer::init() {


    // Restore previous viewer state.
    // restoreStateFromFile();

    Vecteur max(0.0, 0.0, 0.0);
    Vecteur min(0.0, 0.0, 0.0);
    for (auto triangleIteratorBegin = soupe->triangles.begin(),
                 triangleIteratorEnd = soupe->triangles.end();
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
    qglviewer::Vec minQGL(min[0], min[1], min[2]);
    qglviewer::Vec maxQGL(max[0], max[1], max[2]);
    printf("min %ld %ld %ld \n  max %ld %ld %ld\n",
           minQGL.x, minQGL.y, minQGL.z,  maxQGL.x, maxQGL.y, maxQGL.z);
    camera()->setSceneBoundingBox(minQGL, maxQGL);
    camera()->showEntireScene();
    // Opens help window
    help();
}

QString Viewer::helpString() const {
    QString text("<h2>S i m p l e V i e w e r</h2>");
    text += "Use the mouse to move the camera around the object. ";
    text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
    text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
    text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
    text += "Simply press the function key again to restore it. Several keyFrames define a ";
    text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
    text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
    text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
    text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
    text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
    text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
    text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
    text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
    text += "Press <b>Escape</b> to exit the viewer.";
    return text;
}

