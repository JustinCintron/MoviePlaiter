#include "BuildOutput.h"

namespace controller
{

//
// Builds all output that will be made in this application.
// This constructor determines the longest strings for name and studio for formatting purposes.
//
// @precondition leadingHeadNode != 0
// @postcondition none
//
// @param leadingHeadNode the first node for names.
//
BuildOutput::BuildOutput(Node* leadingHeadNode)
{
    this->longestNameLength = this->getLongestNameLength(leadingHeadNode);
    this->longestStudioLength = this->getLongestStudioLength(leadingHeadNode);
}

//
// Gets the output sorted by movie length.
//
// @precondition headLengthNode != 0
// @postcondition none
//
// @param headLengthNode The first node for length.
// @param ascending Determines if the sort should be ascending or descending.
//
string BuildOutput::getLengthOutput(Node* headLengthNode, bool ascending)
{
    vector<string> output = this->recursivelyGetLengthNodes(headLengthNode);

    if(ascending)
    {
        reverse(output.begin(), output.end());
    }
    string out;

    for(auto t=output.begin(); t!=output.end(); ++t)
    {
        out += *t + "\n";
    }

    return out;
}

vector<string> BuildOutput::recursivelyGetLengthNodes(Node* headLengthNode)
{

    vector<string> output;
    if(headLengthNode->GetnextLength() == nullptr)
    {
        output.push_back(this->buildString(headLengthNode));
        return output;
    }

    vector<string> addNext = this->recursivelyGetLengthNodes(headLengthNode->GetnextLength());
    for(auto t=addNext.begin(); t!=addNext.end(); ++t)
    {
        output.push_back(*t);
    }

    string addCurrent = this->buildString(headLengthNode);
    output.push_back(addCurrent);

    return output;
}

//
// Gets the output sorted by movie rating.
//
// @precondition headRatingNode != 0
// @postcondition none
//
// @param headRatingNode The first node for rating.
// @param ascending Determines if the sort should be ascending or descending.
string BuildOutput::getRatingOutput(Node* headRatingNode, bool ascending)
{
    vector<string> output = this->recursivelyGetRatingNodes(headRatingNode);

    if(ascending)
    {
        reverse(output.begin(), output.end());
    }
    string out;

    for(auto t=output.begin(); t!=output.end(); ++t)
    {
        out += *t + "\n";
    }

    return out;
}

vector<string> BuildOutput::recursivelyGetRatingNodes(Node* headRatingNode)
{

    vector<string> output;
    if(headRatingNode->GetnextRating() == nullptr)
    {
        output.push_back(this->buildString(headRatingNode));
        return output;
    }

    vector<string> addNext = this->recursivelyGetRatingNodes(headRatingNode->GetnextRating());
    for(auto t=addNext.begin(); t!=addNext.end(); ++t)
    {
        output.push_back(*t);
    }

    string addCurrent = this->buildString(headRatingNode);
    output.push_back(addCurrent);

    return output;
}

//
// Gets the output sorted by movie name.
//
// @precondition headNameNode != 0
// @postcondition none
//
// @param headNameNode The first node for name.
// @param ascending Determines if the sort should be ascending or descending.
string BuildOutput::getNameOutput(Node* headNameNode, bool ascending)
{
    vector<string> output = this->recursivelyGetNameNodes(headNameNode);

    if(ascending)
    {
        reverse(output.begin(), output.end());
    }
    string out;

    for(auto t=output.begin(); t!=output.end(); ++t)
    {
        out += *t + "\n";
    }

    return out;
}

//
// Gets the output sorted by movie name to save to a file.
//
// @precondition headNameNode != 0
// @postcondition none
//
// @param headNameNode The first node for name.
string BuildOutput::getNameOutputToSave(Node* headNameNode)
{
    vector<string> output = this->recursivelyGetNameNodesToSave(headNameNode);
    reverse(output.begin(), output.end());
    string out;

    for(auto t=output.begin(); t!=output.end(); ++t)
    {
        out += *t + "\n";
    }

    return out;
}

vector<string> BuildOutput::recursivelyGetNameNodes(Node* headNameNode)
{
    vector<string> output;
    if(headNameNode->GetnextName() == nullptr)
    {
        output.push_back(this->buildString(headNameNode));
        return output;
    }
    vector<string> addNext = this->recursivelyGetNameNodes(headNameNode->GetnextName());
    for(auto t=addNext.begin(); t!=addNext.end(); ++t)
    {
        output.push_back(*t);
    }

    string addCurrent = this->buildString(headNameNode);
    output.push_back(addCurrent);

    return output;
}

vector<string> BuildOutput::recursivelyGetNameNodesToSave(Node* headNameNode)
{
    vector<string> output;
    if(headNameNode->GetnextName() == nullptr)
    {
        output.push_back(this->buildStringToSave(headNameNode));
        return output;
    }
    vector<string> addNext = this->recursivelyGetNameNodesToSave(headNameNode->GetnextName());
    for(auto t=addNext.begin(); t!=addNext.end(); ++t)
    {
        output.push_back(*t);
    }

    string addCurrent = this->buildStringToSave(headNameNode);
    output.push_back(addCurrent);

    return output;
}

string BuildOutput::buildStringToSave(Node* node)
{
    string name = node->GetmovieInfo()->getName();
    string studio = node->GetmovieInfo()->getStudio();
    string year = to_string(node->GetmovieInfo()->getYear());
    string rating = this->convertRatingToString(node->GetmovieInfo()->getRating());
    string length = to_string(node->GetmovieInfo()->getLength());

    string output = name + "," + studio + "," + year + "," + rating + "," + length;

    return output;
}

string BuildOutput::buildString(Node* node)
{
    int accountForYearSpace = 6;
    int nameLength = this->longestNameLength + accountForYearSpace;
    int studioLength = this->longestStudioLength;
    int ratingLength = 9;
    int movieLength = 3;
    string year = to_string(node->GetmovieInfo()->getYear());
    string name = (node->GetmovieInfo()->getName() + "-" + year);
    name.resize(nameLength, ' ');
    string studio = node->GetmovieInfo()->getStudio();
    studio.resize(studioLength, ' ');

    string rating = this->convertRatingToString(node->GetmovieInfo()->getRating());
    rating.resize(ratingLength, ' ');


    string length = to_string(node->GetmovieInfo()->getLength());
    length.resize(movieLength, ' ');

    return name + " " + studio + " " + rating + " " + length;

}

string BuildOutput::convertRatingToString(Movie::Rating rating)
{
    string ratingString;
    switch(rating)
    {
    case Movie::G:
        ratingString = "G";
        break;
    case Movie::PG:
        ratingString = "PG";
        break;
    case Movie::PG13:
        ratingString = "PG13";
        break;
    case Movie::R:
        ratingString = "R";
        break;
    case Movie::NOT_RATED:
        ratingString = "NOT_RATED";
        break;
    }

    return ratingString;
}

int BuildOutput::getLongestNameLength(Node* headNode)
{
    int longestNameLength = headNode->GetmovieInfo()->getName().length();

    Node* node = new Node();
    node = headNode;

    while(node->GetnextName() != nullptr)
    {
        node = node->GetnextName();
        int currentLength = node->GetmovieInfo()->getName().length();
        if(currentLength > longestNameLength)
        {
            longestNameLength = currentLength;
        }
    }

    return longestNameLength;
}

int BuildOutput::getLongestStudioLength(Node* headNode)
{
    int longestStudioLength = headNode->GetmovieInfo()->getStudio().length();

    Node* node = new Node();
    node = headNode;

    while(node->GetnextName() != nullptr)
    {
        node = node->GetnextName();
        int currentLength = node->GetmovieInfo()->getStudio().length();
        if(currentLength > longestStudioLength)
        {
            longestStudioLength = currentLength;
        }
    }

    return longestStudioLength;
}
}
