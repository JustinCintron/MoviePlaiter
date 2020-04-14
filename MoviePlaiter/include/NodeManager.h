#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include "Movie.h"
#include "Node.h"
using namespace model;

#include "Utils.h"

#include <string>
#include <algorithm>
using namespace std;

namespace controller
{

class NodeManager
{
public:
    NodeManager();
    virtual ~NodeManager();

    void addNode(Movie* movie);

    Node* getNameHead();
    Node* getLengthHead();
    Node* getRatingHead();

private:
    Node* node;
    Node* headNameNode;
    Node* headLengthNode;
    Node* headRatingNode;

    void addNextName(Movie* movie);
    void addNextLength(Movie* movie);
    void addNextRating(Movie* movie);
};
}

#endif // NODEMANAGER_H
