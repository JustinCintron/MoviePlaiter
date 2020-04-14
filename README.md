# MoviePlaiter

How to use/install

This is a code::blocks program developed in Ubuntu using: g++ -std=c++11
Run from Code::Blocks:

Download Code::Blocks.
Download or clone this project.
Then open the file MoviePlaiter.cbp
Go to Build -> Clean
Go to Build -> Build&Run


Application information

Takes movie information from use (Movie name, studio, length, rating) and displays it in a sorted list.
Uses FLTK for GUI.
This list can be sorted by: Name, Rating, and Length (ascending and decending). The Rating sort has a second layer
sort done by name.

The structure used to contain this list of movies is a doubly linked list but more specific a braided/plaited doubly linked list.
The braided/plaited comes from the fact that there are three (mulitple) links (braids/strands/plaits) in this single linked list.
The list is conected and sorted by: name, length, and rating.

The application uses recursion to traverse the linked list in order to build the output presented to the user.
The application also allows users to Load and Save the movie list.

It saves the list in the format: name,studio,year,rating,length - the Load features requires the same format for the file.
No length or year can be equal to or less than 0.
Any lines that result in an error will stop the loading process and display which line inturupted the Load.
