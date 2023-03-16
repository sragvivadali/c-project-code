#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include <set>

#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    TreeMultimap<std::string, Movie*> m_moviesWithID;
    TreeMultimap<std::string, Movie*> m_moviesWithDirectors;
    TreeMultimap<std::string, Movie*> m_moviesWithActors;
    TreeMultimap<std::string, Movie*> m_moviesWithGenre;

    std::vector<Movie *> m_movies;
    bool m_loaded;

    void makeVectorOf(std::string& line, std::vector<std::string> &tempVector);
};

#endif // MOVIEDATABASE_INCLUDED
