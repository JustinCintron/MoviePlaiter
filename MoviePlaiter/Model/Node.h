#ifndef NODE_H
#define NODE_H

#include "Movie.h"
using namespace model;

namespace model
{

class Node
{
public:
    Node();

    Movie* GetmovieInfo();

    Node* GetnextName();
    Node* GetpreviousName();
    Node* GetpreviousLength();
    Node* GetpreviousRating();
    Node* GetnextLength();
    Node* GetnextRating();

    void SetmovieInfo(Movie* val);
    void SetnextName(Node* val);
    void SetpreviousName(Node* val);
    void SetpreviousLength(Node* val);
    void SetpreviousRating(Node* val);
    void SetnextLength(Node* val);
    void SetnextRating(Node* val);

private:
    Movie* movieInfo;

    Node* nextName;
    Node* nextLength;
    Node* nextRating;

    Node* previousName;
    Node* previousLength;
    Node* previousRating;
};
}

#endif // NODE_H
