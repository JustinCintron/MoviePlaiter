#include "Node.h"

namespace model
{

//
// Constructs a node object that contains other nodes in a plaited list.
//
// @precondition none
// @postcondition none
//
Node::Node()
{
    this->movieInfo = nullptr;
    this->nextName = nullptr;
    this->nextLength = nullptr;
    this->nextRating = nullptr;
    this->previousName = nullptr;
    this->previousLength = nullptr;
    this->previousRating = nullptr;
}

//
// Returns the movieInfo
//
// @precondition none
// @postcondition none
//
Movie* Node::GetmovieInfo()
{
    return this->movieInfo;
}

//
// Sets the movieInfo
//
// @precondition none
// @postcondition none
//
// @param val Value to set it to
//
void Node::SetmovieInfo(Movie* val)
{
    this->movieInfo = val;
}

//
// Returns the nextName node
//
// @precondition none
// @postcondition none
//
Node* Node::GetnextName()
{
    return this->nextName;
}

//
// Sets the nextName node
//
// @precondition none
// @postcondition none
//
// @param val Value to set it to
//
void Node::SetnextName(Node* val)
{
    this->nextName = val;
}

//
// Returns the nextLength node
//
// @precondition none
// @postcondition none
//
Node* Node::GetnextLength()
{
    return this->nextLength;
}

//
// Sets the nextLength node
//
// @precondition none
// @postcondition none
//
// @param val Value to set it to
//
void Node::SetnextLength(Node* val)
{
    this->nextLength = val;
}

//
// Returns the nextRating node
//
// @precondition none
// @postcondition none
//
Node* Node::GetnextRating()
{
    return this->nextRating;
}

//
// Sets the nextRating node
//
// @precondition none
// @postcondition none
//
// @param val Value to set it to
//
void Node::SetnextRating(Node* val)
{
    this->nextRating = val;
}

//
// Returns the previousName node
//
// @precondition none
// @postcondition none
//
Node* Node::GetpreviousName()
{
    return this->previousName;
}

//
// Sets the previousName node
//
// @precondition none
// @postcondition none
//
// @param val Value to set it to
//
void Node::SetpreviousName(Node* val)
{
    this->previousName = val;
}

//
// Returns the previousLength node
//
// @precondition none
// @postcondition none
//
Node* Node::GetpreviousLength()
{
    return this->previousLength;
}

//
// Sets the previousLength node
//
// @precondition none
// @postcondition none
//
// @param val Value to set it to
//
void Node::SetpreviousLength(Node* val)
{
    this->previousLength = val;
}

//
// Returns the previousRating node
//
// @precondition none
// @postcondition none
//
Node* Node::GetpreviousRating()
{
    return this->previousRating;
}

//
// Sets the previousRating node
//
// @precondition none
// @postcondition none
//
// @param val Value to set it to
//
void Node::SetpreviousRating(Node* val)
{
    this->previousRating= val;
}
}
