#include "ReadFile.h"

namespace model
{

//
// Reads a file and returns the file contents as a string.
//
// @precondition none
// @postcondition none
//
// @param fileName The name of the file to read
string ReadFile::readAsString(string fileName)
{
    ifstream textDocument(fileName);

    char c;
    string fileContents;
    while(textDocument.get(c))
    {
        fileContents += c;
    }
    textDocument.close();

    return fileContents;
}
}
