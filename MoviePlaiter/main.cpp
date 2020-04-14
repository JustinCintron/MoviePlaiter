#include "MovieLibraryWindow.h"
using namespace view;

int main(int argc, char ** argv)
{
    MovieLibraryWindow mainWindow(570, 375, "Justin Cintron's Movie Database");
    mainWindow.show();

    int exitCode = Fl::run();
    return exitCode;
}
