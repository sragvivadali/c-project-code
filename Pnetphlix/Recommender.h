#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include "MovieDatabase.h"
#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include <string>
#include <vector>
#include <unordered_map>

class UserDatabase;
class MovieDatabase;
class User;
class Movie;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
      : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
      Recommender(const UserDatabase& user_database,
                  const MovieDatabase& movie_database);
      std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                                int movie_count) const;

  private:
      const UserDatabase* m_userDB;
      const MovieDatabase* m_movieDB;

      const std::unordered_map<Movie*, int> moviesWithCompScore;

      std::unordered_map<Movie*, int> calcCompScoreForDir(User* user) const;
      void calcCompScoreForActors(User *user, std::unordered_map<Movie*, int> &moviesWithCompatabilityScore) const;
      void calcCompScoreForGenre(User *user, std::unordered_map<Movie*, int> &moviesWithCompatabilityScore) const;
      bool isInWatchHistory(User *user, std::string movieId) const;

      bool comp(const MovieAndRank& left, const MovieAndRank& right) const;
      void sort(std::vector<MovieAndRank> &vector, int left, int right) const;
      int partition(std::vector<MovieAndRank> &vector, int left, int right) const; 
};

#endif // RECOMMENDER_INCLUDED
