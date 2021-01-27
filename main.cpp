#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"
#include "Utils.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2)
    {
        std::cerr << "Usage: ./viewer <nomfichier> " << std::endl;
        return 0;
    }
    std::string nameTriFile = argv[1];
    ifstream input(nameTriFile);
    TriangleSoup soupe;
    soupe.read(input);
    // Read command lines arguments.
    QApplication application(argc, argv);
    // Instantiate the viewer.
    Viewer viewer(&soupe);
    // Give a name
    viewer.setWindowTitle("Viewer triangle soup");
    // Make the viewer window visible on screen.
    viewer.show();
    // Run main loop.
    application.exec();
    return 0;
}
