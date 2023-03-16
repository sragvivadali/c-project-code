#include "MovieDatabase.h"
#include "Movie.h"
#include "treemm.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

bool MovieDatabase::load(const string& filename)
{
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file \"" << filename << "\"" << endl;
        return false;
    }
    string line;
    int lineCount = 0;

    string id;
    string title;
    string year;
    vector<string> directors;
    vector<string> actors;
    vector<string> genres;
    float rating;

    while (getline(file, line)){
        if (lineCount == 0){
            id = line;
            lineCount ++;
        }
        else if (lineCount == 1){
            title = line;
            lineCount ++;
        }
        else if (lineCount == 2){
            year = line;
            lineCount ++;
        }
        else if (lineCount == 3){
            string directorName;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == ','){
                    directors.push_back(directorName);
                    directorName = "";
                }
                else{
                    directorName += line[i];
                }
            }
            lineCount ++;
        }
        else if (lineCount == 4){
            string actorsName;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == ','){
                    actors.push_back(actorsName);
                    actorsName = "";
                }
                else{
                    actorsName += line[i];
                }
            }
            lineCount ++;
        }
        else if (lineCount == 5){
            string genreName;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == ','){
                    genres.push_back(genreName);
                    genreName = "";
                }
                else{
                    genreName += line[i];
                }
            }
            lineCount ++;
        }
        else if (lineCount == 6){
            rating = stof(line);
            lineCount ++;
        }
        else {
            Movie *movie = new Movie(id, title, year, directors, actors, genres, rating);
            m_moviesWithID.insert(id, movie);
            m_moviesWithDirectors.insert(directors, movie);
            m_moviesWithActors.insert(actors, movie);
            m_moviesWithGenre.insert(genres, movie);
            lineCount = 0;
            id = "";
            title = "";
            year = "";
            directors.clear();
            actors.clear();
            genres.clear();
            rating = 0;
        }
    }

    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    return m_moviesWithID.find(id).get_value();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}
