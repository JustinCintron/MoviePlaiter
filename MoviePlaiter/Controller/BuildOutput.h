#ifndef BUILDOUTPUT_H
#define BUILDOUTPUT_H

#include "Movie.h"
#include "Node.h"
using namespace model;

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

namespace controller
{

class BuildOutput
{
public:
    BuildOutput(Node* leadingHeadNode);

    string getNameOutput(Node* headNameNode, bool ascending);
    string getRatingOutput(Node* headRatingNode, bool ascending);
    string getLengthOutput(Node* headLengthNode, bool ascending);
    string getNameOutputToSave(Node* headNameNode);

private:
    vector<string> recursivelyGetNameNodes(Node* headNameNode);
    vector<string> recursivelyGetRatingNodes(Node* headRatingNode);
    vector<string> recursivelyGetLengthNodes(Node* headLengthNode);
    vector<string> recursivelyGetNameNodesToSave(Node* headNameNode);
    string buildString(Node* node);
    string buildStringToSave(Node* node);
    string convertRatingToString(Movie::Rating rating);

    int longestNameLength;
    int longestStudioLength;
    int getLongestNameLength(Node* headNode);
    int getLongestStudioLength(Node* headNode);
};
}

#endif // BUILDOUTPUT_H
