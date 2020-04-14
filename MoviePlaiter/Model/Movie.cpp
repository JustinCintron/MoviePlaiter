#include "Movie.h"

namespace model
{

//
// Constructs a movie object.
//
// @precondition none
// @postcondition none
//
// @param name The movie name
// @param studio The studio who made the movie
// @param year The year the movie came out
// @param rating The rating of the movie
// @param length The length in minutes the movie is
//
Movie::Movie(const string& name, const string& studio, int year, Rating rating, int length)
{
    this->name = name;
    this->studio = studio;
    this->year = year;
    this->rating = rating;
    this->length = length;
}

//
// Returns the movie name
//
// @precondition none
// @postcondition none
//
const string& Movie::getName() const
{
    return this->name;
}

//
// Returns the movie studio
//
// @precondition none
// @postcondition none
//
const string& Movie::getStudio() const
{
    return this->studio;
}

//
// Returns the movie rating
//
// @precondition none
// @postcondition none
//
Movie::Rating Movie::getRating() const
{
    return this->rating;
}

//
// Returns the movie year
//
// @precondition none
// @postcondition none
//
int Movie::getYear() const
{
    return this->year;
}

//
// Returns the movie length
//
// @precondition none
// @postcondition none
//
int Movie::getLength() const
{
    return this->length;
}
}
