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
    m_loaded = false;
}

MovieDatabase::~MovieDatabase(){
    for (int i = 0; i < m_movies.size(); i++)   //delete all dynamically allocated movies
        delete m_movies[i];
}

bool MovieDatabase::load(const string& filename)
{
    if (m_loaded)
        return false;
    
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
        switch (lineCount){
            case 0:
                id = line;
                lineCount ++;
                break;
            case 1:
                title = line;
                lineCount ++;
                break;
            case 2:
                year = line;
                lineCount ++;
                break;
            case 3:
                makeVectorOf(line, directors);
                lineCount ++;
                break;
            case 4:
                makeVectorOf(line, actors);
                lineCount ++;
                break;
            case 5:
                makeVectorOf(line, genres);
                lineCount ++;
                break;
            case 6:
                rating = stof(line);
                lineCount ++;
                break;
            default: 
                Movie *movie = new Movie(id, title, year, directors, actors, genres, rating);
                m_movies.push_back(movie);
                m_moviesWithID.insert(id, movie);
                for (int i = 0; i < directors.size(); i++) 
                    m_moviesWithDirectors.insert(directors[i], movie);
                for (int i = 0; i < actors.size(); i++)
                    m_moviesWithActors.insert(actors[i], movie);
                for (int i = 0; i < genres.size(); i++)
                    m_moviesWithGenre.insert(genres[i], movie);
                lineCount = 0;
                id = "";
                title = "";
                year = "";
                directors.clear();
                actors.clear();
                genres.clear();
                rating = 0;
                break;

        }
    }

    m_loaded = true;
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const {
    TreeMultimap<string, Movie*>::Iterator it = m_moviesWithID.find(id);
    if(it.is_valid()) 
        return it.get_value();
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const {
    TreeMultimap<std::string, Movie*>::Iterator it = m_moviesWithDirectors.find(director);
    vector<Movie*> result;
    while (it.is_valid()) {
        result.push_back(it.get_value());
        it.advance();
    }
    return result; 
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const {
    TreeMultimap<std::string, Movie*>::Iterator it = m_moviesWithActors.find(actor);
    vector<Movie*> result;
    while (it.is_valid()) {
        result.push_back(it.get_value());
        it.advance();
    }
    return result;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = m_moviesWithGenre.find(genre);
    vector<Movie*> result;
    while (it.is_valid()) {
        result.push_back(it.get_value());
        it.advance();
    }
    return result; 
}


void MovieDatabase::makeVectorOf(std::string& line, std::vector<std::string> &tempVector){
    string word;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ','){
            tempVector.push_back(word);
            word = "";
        }
        else{
            word += line[i];
        }
    }
    tempVector.push_back(word);
}