#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <fstream>
#include <string>
using namespace std;

namespace model
{

class SaveFile
{
public:

    void saveStringIntoFile(string fileName, string contents);

};
}

#endif // SAVEFILE_H
