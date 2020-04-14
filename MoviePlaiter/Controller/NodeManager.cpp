#include "NodeManager.h"

namespace controller
{

//
// Initializes the NodeManager
//
// @precondition none
// @postcondition none
//
NodeManager::NodeManager()
{
    this->headNameNode = new Node();
    this->headLengthNode = new Node();
    this->headRatingNode = new Node();
    this->node = new Node();
}

//
// Creates and modifies the plaited list.
//
// @precondition movie != 0
// @postcondition none
//
// @param movie The movie pointer that will be added to the plaited list according to its name, length, and rating.
// The rating plait has a second layer sort by name for any that are the same.
//
void NodeManager::addNode(Movie* movie)
{

    if(this->node->GetmovieInfo() == nullptr)
    {
        this->node->SetmovieInfo(movie);
        this->headNameNode->SetmovieInfo(movie);
        this->headLengthNode->SetmovieInfo(movie);
        this->headRatingNode->SetmovieInfo(movie);

        return;
    }

    this->addNextName(movie);
    this->addNextLength(movie);
    this->addNextRating(movie);
}

//
// Returns the lengthHeadNode
//
// @precondition none
// @postcondition none
//
Node* NodeManager::getLengthHead()
{
    return this->headLengthNode;
}

//
// Returns the headHeadNode
//
// @precondition none
// @postcondition none
//
Node* NodeManager::getNameHead()
{
    return this->headNameNode;
}

//
// Returns the ratingHeadNode
//
// @precondition none
// @postcondition none
//
Node* NodeManager::getRatingHead()
{
    return this->headRatingNode;
}

void NodeManager::addNextRating(Movie* movie)
{
    Node* nodeToAdd = new Node();
    nodeToAdd->SetmovieInfo(movie);

    int ratingToAdd = nodeToAdd->GetmovieInfo()->getRating();
    Node* currentNode = this->headRatingNode;

    int currentNodeRating = currentNode->GetmovieInfo()->getRating();
    if(ratingToAdd < currentNodeRating)
    {
        Node* tempNode = new Node();
        tempNode = this->headRatingNode;
        this->headRatingNode = nodeToAdd;
        this->headRatingNode->SetnextRating(tempNode);
        tempNode->SetpreviousRating(this->headRatingNode);

        return;
    }
    bool ratingsEqual = (ratingToAdd == currentNodeRating);

    string currentNodeName = toUpperCase(currentNode->GetmovieInfo()->getName());
    string nameToAdd = toUpperCase(movie->getName());

    if( (nameToAdd < currentNodeName) && ( ratingsEqual ))
    {
        Node* tempNode = new Node();
        tempNode = this->headRatingNode;
        this->headRatingNode = nodeToAdd;
        this->headRatingNode->SetnextRating(tempNode);
        tempNode->SetpreviousRating(this->headRatingNode);

        return;
    }
    do
    {
        if(currentNode->GetnextRating() == nullptr)
        {
            currentNode->SetnextRating(nodeToAdd);
            nodeToAdd->SetpreviousRating(currentNode);
            break;
        }

        currentNode = currentNode->GetnextRating();
        currentNodeRating = currentNode->GetmovieInfo()->getRating();

        if(ratingToAdd < currentNodeRating)
        {
            Node* tempNode = new Node();
            tempNode = currentNode;
            currentNode = nodeToAdd;
            currentNode->SetnextRating(tempNode);

            Node* previousCurrentNode = new Node();
            previousCurrentNode = tempNode->GetpreviousRating();
            previousCurrentNode->SetnextRating(currentNode);
            currentNode->SetpreviousRating(previousCurrentNode);
            tempNode->SetpreviousRating(currentNode);
            break;
        }

        ratingsEqual = (ratingToAdd == currentNodeRating);
        currentNodeName = toUpperCase(currentNode->GetmovieInfo()->getName());

        if( (nameToAdd < currentNodeName) && ( ratingsEqual ))
        {
            Node* tempNode = new Node();
            tempNode = currentNode;
            currentNode = nodeToAdd;
            currentNode->SetnextRating(tempNode);

            Node* previousCurrentNode = new Node();
            previousCurrentNode = tempNode->GetpreviousRating();
            previousCurrentNode->SetnextRating(currentNode);
            currentNode->SetpreviousRating(previousCurrentNode);
            tempNode->SetpreviousRating(currentNode);
            break;
        }
    }
    while(true);
}

void NodeManager::addNextLength(Movie* movie)
{
    Node* nodeToAdd = new Node();
    nodeToAdd->SetmovieInfo(movie);
    int lengthToAdd = nodeToAdd->GetmovieInfo()->getLength();

    Node* currentNode = this->headLengthNode;
    int currentNodeLength = currentNode->GetmovieInfo()->getLength();

    if(lengthToAdd < currentNodeLength)
    {
        Node* tempNode = new Node();
        tempNode = this->headLengthNode;
        this->headLengthNode = nodeToAdd;
        this->headLengthNode->SetnextLength(tempNode);
        tempNode->SetpreviousLength(this->headLengthNode);

        return;
    }
    do
    {
        if(currentNode->GetnextLength() == nullptr)
        {
            currentNode->SetnextLength(nodeToAdd);
            nodeToAdd->SetpreviousLength(currentNode);
            break;
        }

        currentNode = currentNode->GetnextLength();
        currentNodeLength = currentNode->GetmovieInfo()->getLength();

        if(lengthToAdd < currentNodeLength)
        {
            Node* tempNode = new Node();
            tempNode = currentNode;
            currentNode = nodeToAdd;
            currentNode->SetnextLength(tempNode);

            Node* previousCurrentNode = new Node();
            previousCurrentNode = tempNode->GetpreviousLength();
            previousCurrentNode->SetnextLength(currentNode);
            currentNode->SetpreviousLength(previousCurrentNode);
            tempNode->SetpreviousLength(currentNode);
            break;
        }
    }
    while(true);
}

void NodeManager::addNextName(Movie* movie)
{
    Node* nodeToAdd = new Node();
    nodeToAdd->SetmovieInfo(movie);

    Node* currentNode = this->headNameNode;
    string headNameNodeName = toUpperCase(this->headNameNode->GetmovieInfo()->getName());
    string nameToAdd = toUpperCase(movie->getName());

    if(nameToAdd < headNameNodeName)
    {
        Node* tempNode = new Node();
        tempNode = this->headNameNode;
        this->headNameNode = nodeToAdd;
        this->headNameNode->SetnextName(tempNode);
        tempNode->SetpreviousName(this->headNameNode);

        return;
    }
    do
    {
        if(currentNode->GetnextName() == nullptr)
        {
            currentNode->SetnextName(nodeToAdd);
            nodeToAdd->SetpreviousName(currentNode);
            break;
        }

        currentNode = currentNode->GetnextName();
        string currentNodeName = toUpperCase(currentNode->GetmovieInfo()->getName());

        if(nameToAdd < currentNodeName)
        {
            Node* tempNode = new Node();
            tempNode = currentNode;
            currentNode = nodeToAdd;
            currentNode->SetnextName(tempNode);

            Node* previousCurrentNode = new Node();
            previousCurrentNode = tempNode->GetpreviousName();
            previousCurrentNode->SetnextName(currentNode);
            currentNode->SetpreviousName(previousCurrentNode);
            tempNode->SetpreviousName(currentNode);
            break;
        }
    }
    while (true);
}

//
// Deconstructs the NodeManager and the plaited list.
//
// @precondition none
// @postcondition none
//
NodeManager::~NodeManager()
{
    Node* currentNode = new Node();
    currentNode = this->headNameNode;
    while (currentNode->GetnextName() != nullptr)
    {
        Node* nextNode = currentNode->GetnextName();
        delete currentNode;
        currentNode = nextNode;
    }
}
}
