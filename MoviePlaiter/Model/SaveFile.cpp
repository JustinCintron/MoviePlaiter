#include "SaveFile.h"

namespace model
{

//
// Constructs a movie object.
//
// @precondition none
// @postcondition none
//
// @param fileName The name of the file to write to
// @param contents The contents to write to the file
//
void SaveFile::saveStringIntoFile(string fileName, string contents)
{
    ofstream textDocument;
    textDocument.open(fileName);
    textDocument << contents;
    textDocument.close();
}
}
