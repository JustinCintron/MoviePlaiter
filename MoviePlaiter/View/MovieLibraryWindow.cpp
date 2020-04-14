#include "MovieLibraryWindow.h"

#include "DeleteMovieWindow.h"
#include "AddMovieWindow.h"


#include <FL/fl_types.h>
#include <Fl/fl_draw.H>
#include <Fl/Fl_File_Chooser.H>

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace view
{

//
// Constructs a movie library window creating and initializing all the widgets that will be displayed
//
// @precondition width > 0 AND height > 0
// @postcondition none
//
// @param width The width of the window
// @param height The height of the window
// @param title The title to display for the window
//
MovieLibraryWindow::MovieLibraryWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();

    this->sortingOutputLabel = new Fl_Output(100, 25, 0, 0, "Sort order:");
    createAndDisplaySortingRadioButtons();

    this->librarySummaryOutputLabel = new Fl_Output(190, 110, 0, 0, "Movie library summary:");

    this->summaryOutputTextBuffer = new Fl_Text_Buffer();
    this->summaryOutputTextDisplay = new Fl_Text_Display(20, 120, 525, 200);
    this->summaryOutputTextDisplay->textfont(FL_COURIER);
    this->summaryOutputTextDisplay->buffer(summaryOutputTextBuffer);

    this->loadButton = new Fl_Button(120, 330, 70, 30, "Load");
    this->loadButton->callback(cbLoad, this);

    this->saveButton = new Fl_Button(200, 330, 70, 30, "Save");
    this->saveButton->callback(cbSave, this);

    this->addButton = new Fl_Button(280, 330, 70, 30, "Add");
    this->addButton->callback(cbAddMovie, this);

    this->deleteButton = new Fl_Button(360, 330, 70, 30, "Delete");
    this->deleteButton->callback(cbDeleteMovie, this);

    this->setDefaultSummaryText();
    end();

    this->nodeManager = new NodeManager();

}

void MovieLibraryWindow::setDefaultSummaryText()
{
    this->setSummaryText("Please add movies or load a file to view their information");
}

void MovieLibraryWindow::updateText()
{
    if(this->movies.size() <= 0)
    {
        this->setDefaultSummaryText();

        return;
    }
    BuildOutput build(nodeManager->getNameHead());

    bool ascending = true;
    switch(this->sortOrderSelection)
    {
    case NAME_ASCENDING:
        this->setSummaryText(build.getNameOutput(nodeManager->getNameHead(), ascending));
        break;
    case NAME_DESCENDING:
        ascending = false;
        this->setSummaryText(build.getNameOutput(nodeManager->getNameHead(), ascending));
        break;
    case RATING_ASCENDING:
        this->setSummaryText(build.getRatingOutput(nodeManager->getRatingHead(), ascending));
        break;
    case RATING_DESCENDING:
        ascending = false;
        this->setSummaryText(build.getRatingOutput(nodeManager->getRatingHead(), ascending));
        break;
    case LENGTH_ASCENDING:
        this->setSummaryText(build.getLengthOutput(nodeManager->getLengthHead(), ascending));
        break;
    case LENGTH_DESCENDING:
        ascending = false;
        this->setSummaryText(build.getLengthOutput(nodeManager->getLengthHead(), ascending));
        break;
    }
}

//
// Overriding drawing of FL_Window so can draw a boxes around the sorting type radio buttons
// to make them appear in a group
//
void MovieLibraryWindow::draw()
{
    Fl_Window::draw();
    fl_frame("AAAA", 20, 35, 525, 55);
}

void MovieLibraryWindow::createAndDisplaySortingRadioButtons()
{
    const int X_RADIO_GROUP = 35;
    const int Y_RADIO_GROUP = 45;
    const int WIDTH_RADIO_GROUP = 400;
    const int HEIGHT_RADIO_GROUP = 100;

    this->sortingRadioGroup = new Fl_Group(X_RADIO_GROUP, Y_RADIO_GROUP, WIDTH_RADIO_GROUP, HEIGHT_RADIO_GROUP);
    this->sortingRadioGroup->begin();

    for (int i=0; i<SORTING_GROUPS; i++)
    {
        for (int j = 0; j<SORTING_TYPES_PER_GROUP; j++)
        {
            string label = this->sortingGroup[i] + " " + this->sortingTypes[j];
            int offset = (i*SORTING_TYPES_PER_GROUP) + j;
            this->radioSortingLabels[offset] = new string(label);
            this->sortingRadioGroupButton[offset] = new Fl_Round_Button(X_RADIO_GROUP + i*160, Y_RADIO_GROUP + j*25, 12, 12, radioSortingLabels[offset]->c_str());
            this->sortingRadioGroupButton[offset]->type(FL_RADIO_BUTTON);
            this->sortingRadioGroupButton[offset]->callback(cbSortingMethodChanged, this);
        }
    }

    this->sortingRadioGroup->end();
    this->sortingRadioGroupButton[0]->set();
    this->sortOrderSelection = NAME_ASCENDING;
}

//
// Callback when a radio button for the way to sort the movies has changed
//
// @precondition widget != 0 AND data != 0
// @postcondition MovieLibraryWindow::getSortOrder() == value of new sort order selected
//
// @param widget The widget that initiatied the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void MovieLibraryWindow::cbSortingMethodChanged(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;
    window->sortingMethodChanged();

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Sorting method: " << window->getSortOrder() << endl;
#endif
}

//
// Callback that is an instance function of the window class to encapsulate function
//
// @precondition none
// @postcondition getSortOrder() == value of new sort order selected
//
void MovieLibraryWindow::sortingMethodChanged()
{
    this->setSortOrderBasedOnSelection();
    this->updateText();
}

//
// Callback when the Load button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition MovieLibraryWindow::getFilename() == file selected by the user
//
// @param widget The widget that initiated the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void MovieLibraryWindow::cbLoad(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;
    window->promptUserForFilename(Fl_File_Chooser::SINGLE, "Movie file to load");

    window->loadMovies();

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Filename selected: " << window->getFilename() << endl;
#endif

}

void MovieLibraryWindow::prepareToLoadMovie()
{
    for (Movie* pMovie : this->movies)
    {
        delete pMovie;
    }
    this->movies.clear();

    this->setSummaryText("Loading Movies");
}

void MovieLibraryWindow::loadMovies()
{
    this->prepareToLoadMovie();

    ReadFile file;
    string fileContents = file.readAsString(this->getFilename());

    stringstream stream(fileContents);
    string line;

    while(getline(stream, line, '\n'))
    {
        vector<string> movieInformationTokens;
        string movieInformation;

        stringstream informationStream(line);
        while(getline(informationStream, movieInformation, ','))
        {
            movieInformationTokens.push_back(movieInformation);
        }
        string name;
        string studio;
        string yearString;
        string ratingString;
        string lengthString;
        int year;
        int length;

        try
        {
            if(movieInformationTokens.size() < 5)
            {
                throw "Line had too many /  not enough parameters in file.";
            }
            name = movieInformationTokens[0];
            studio = movieInformationTokens[1];
            yearString = movieInformationTokens[2];
            ratingString = movieInformationTokens[3];
            lengthString = movieInformationTokens[4];

            year = toInt(yearString, "Error converting year to an integer.");
            length = toInt(lengthString, "Error converting length to an integer.");

        }
        catch (const char* message)
        {
            fl_message("%s", message);
            this->setDefaultSummaryText();

            return;
        }

        if(name.empty() || studio.empty() || year <= 0 || length <= 0)
        {
            string message = "Error reading this line: " + line;
            const char *c = message.c_str();
            fl_message(c);

            return;
        }

        Movie::Rating rating = this->determineRating(ratingString);
        Movie* movie = new Movie(name, studio, year, rating, length);
        this->movies.push_back(movie);
    }
    this->addMoviesFromVector();
}

void MovieLibraryWindow::addMoviesFromVector()
{

    delete this->nodeManager;
    this->nodeManager = new NodeManager();

    for(auto movie=this->movies.begin(); movie!=this->movies.end(); ++movie)
    {
        this->nodeManager->addNode(*movie);
    }
    this->updateText();
}

Movie::Rating MovieLibraryWindow::determineRating(string ratingEntered)
{
    ratingEntered = toUpperCase(ratingEntered);

    Movie::Rating rating = Movie::Rating::NOT_RATED;

    if (ratingEntered == ENUM_TO_STR(G))
    {
        rating = Movie::Rating::G;
    }
    else if (ratingEntered == ENUM_TO_STR(PG))
    {
        rating = Movie::Rating::PG;
    }
    else if (ratingEntered == ENUM_TO_STR(PG13))
    {
        rating = Movie::Rating::PG13;
    }
    else if (ratingEntered == ENUM_TO_STR(R))
    {
        rating = Movie::Rating::R;
    }

    return rating;
}

//
// Callback when the Load button is invoked
//
// @precondition type == Fl_File_Chooser type of SINGLE, MULTI, CREATE, or DIRECTORY
// @postcondition MovieLibraryWindow::getFilename() == file selected by the user
//
// @param type Fl_File_Chooser type of SINGLE, MULTI, CREATE, or DIRECTORY
// @param title Title to display for the file chooser
//
// @return The filename the user selected
//
const string MovieLibraryWindow::promptUserForFilename(int type, const string& title)
{
    Fl_File_Chooser chooser(".", "*", type, title.c_str());
    chooser.show();

    while(chooser.shown())
    {
        Fl::wait();
    }

    if (chooser.value() != 0)
    {
        this->selectedFilename = chooser.value();
    }
    else
    {
        this->selectedFilename = "";
    }

    return this->selectedFilename;
}

//
// Gets the filename the user selected when the file chooser was invoked
//
// @precondition none
// @postcondition none
//
// @return The filename the user had selected when the file chooser was invoked
//
const string MovieLibraryWindow::getFilename() const
{
    return this->selectedFilename;
}

//
// Callback when the Save button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition MovieLibraryWindow::getFilename() == file selected by the user
//
// @param widget The widget that initiatied the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void MovieLibraryWindow::cbSave(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;
    window->promptUserForFilename(Fl_File_Chooser::CREATE, "Movie file to save to");

    window->saveMovies();

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Filename selected: " << window->getFilename() << endl;
#endif

}

void MovieLibraryWindow::saveMovies()
{
    BuildOutput out(this->nodeManager->getNameHead());
    string moviesToSave = out.getNameOutputToSave(this->nodeManager->getNameHead());

    SaveFile saver;
    saver.saveStringIntoFile(this->getFilename(), moviesToSave);
}

//
// Callback when the Add button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition none
//
// @param widget The widget that initiatied the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void MovieLibraryWindow::cbAddMovie(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;

    AddMovieWindow addMovie;
    addMovie.set_modal();
    addMovie.show();

    while (addMovie.shown())
    {
        Fl::wait();
    }

    window->movies.push_back(addMovie.getMovie());

    window->nodeManager->addNode(addMovie.getMovie());

    window->updateText();

#ifdef DIAGNOSTIC_OUTPUT

    //Good for diagnostic output left it in on purpose because it is still useful.
    if (addMovie.getWindowResult() == OKCancelWindow::WindowResult::OK)
    {
        for ( Movie* pMovie : window->movies)
        {
            cout << "OK" << endl;
            cout << "Name: " << pMovie->getName() << endl;
            cout << "Studio: " << pMovie->getStudio() << endl;
            cout << "Year: " << pMovie->getYear() << endl;
            cout << "Rating: " << pMovie->getRating() << endl;
            cout << "Length: " << pMovie->getLength() << endl;
        }
    }
    else
    {
        cout << "Cancel or closed window." << endl;
    }
#endif
}

//
// Callback when the Delete button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition none
//
// @param widget The widget that initiatied the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void MovieLibraryWindow::cbDeleteMovie(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;

    DeleteMovieWindow deleteMovie;
    deleteMovie.set_modal();
    deleteMovie.show();

    while (deleteMovie.shown())
    {
        Fl::wait();
    }

    window->checkForAndDeleteMovie(deleteMovie.getName());

#ifdef DIAGNOSTIC_OUTPUT
    if (deleteMovie.getWindowResult() == OKCancelWindow::WindowResult::OK)
    {
        cout << "OK - Movie name: " << deleteMovie.getName() << endl;
    }
    else
    {
        cout << "Cancel or closed window." << endl;
    }
#endif

}

void MovieLibraryWindow::checkForAndDeleteMovie(string name)
{

    for(int i = 0; i < this->movies.size(); i++)
    {

        if(toUpperCase(this->movies.at(i)->getName()) == toUpperCase(name))
        {
            this->movies.erase(this->movies.begin() + i);
            this->addMoviesFromVector();
            return;
        }
    }
    fl_message("Movie not found");
}

//
// Determines and sets the sort order based on the radio button the user has selected.
//
// @preconditon none
// @postcondition getSortOrder() == sort order that user selected
//
void MovieLibraryWindow::setSortOrderBasedOnSelection()
{
    for (int i=0; i<TOTAL_SORTING_METHODS; i++)
    {
        if (this->sortingRadioGroupButton[i]->value())
        {
            this->sortOrderSelection = (SortOrder)i;
        }
    }
}

//
// Sets the summary test to display in the movie library summary output
//
// @precondition none
// @postcondition none
//
// @param outputText The text to display
//
void MovieLibraryWindow::setSummaryText(const string& outputText)
{
    this->summaryOutputTextBuffer->text(outputText.c_str());
}

//
// Gets the sort order the user has selected
//
// @precondition none
// @postcondition none
//
// @return The sort order the user has selected
//
MovieLibraryWindow::SortOrder MovieLibraryWindow::getSortOrder() const
{
    return this->sortOrderSelection;
}

//
// Destructor that cleans up all allocated resources for the window
//
MovieLibraryWindow::~MovieLibraryWindow()
{
    for (int i=0; i<TOTAL_SORTING_METHODS; i++)
    {
        delete this->radioSortingLabels[i];
        delete this->sortingRadioGroupButton[i];
    }

    delete this->sortingOutputLabel;

    delete this->librarySummaryOutputLabel;
    this->summaryOutputTextDisplay->buffer(0);
    delete this->summaryOutputTextBuffer;
    delete this->summaryOutputTextDisplay;

    delete this->loadButton;
    delete this->saveButton;
    delete this->addButton;
    delete this->deleteButton;

    for (Movie* pMovie : this->movies)
    {
        delete pMovie;
    }
    this->movies.clear();
}

}
