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

    /*
    TriangleSoup zip;
    TriangleSoupZipper zipper(soupe,zip,Index(150,150,150));
    */
    QApplication application(argc, argv);

    /*Viewer viewer(&zip);*/
    //*
    Viewer viewer(&soupe);
    //*/
    viewer.setWindowTitle("Viewer triangle soup");
    viewer.show();
    application.exec();
    return 0;
}
