#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
    : m_movieDB(&movie_database), m_userDB(&user_database)
{
}


vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const // O(NlogN)
{
    unordered_map<Movie*, int> moviesWithCompScore;
    User *user = m_userDB -> get_user_from_email(user_email);
    moviesWithCompScore = calcCompScoreForDir(user); // O(log N)
    calcCompScoreForActors(user, moviesWithCompScore); // O(log N)
    calcCompScoreForGenre(user, moviesWithCompScore); // O(log N)
    vector<MovieAndRank> recommendations;
    for (auto it = moviesWithCompScore.begin(); it != moviesWithCompScore.end(); it ++){ // O(N)
        MovieAndRank movierank = MovieAndRank(it->first->get_id(), it->second);
        recommendations.push_back(movierank);
    }


    sort(recommendations, 0, recommendations.size() - 1); // O(NlogN)


    vector<MovieAndRank> result;
    int inserted = 0;
    int i = 0;
    while (inserted < movie_count){
        if (!isInWatchHistory(user, recommendations[i].movie_id)){  // O(N)
            result.push_back(recommendations[i]);
            inserted++;
        }
        i++;
    }
    return result; 
    return vector<MovieAndRank>();
}

bool Recommender::isInWatchHistory(User *user, string movieId) const { // O(N)
    unordered_set<string> watchHistorySet;
    for (string i : user -> get_watch_history()){
        watchHistorySet.insert(i);
    }
    unordered_set<string>::iterator it = watchHistorySet.find(movieId);
    if (it == watchHistorySet.end())
        return true;

    return false;
}

unordered_map<Movie*, int> Recommender::calcCompScoreForDir(User* user) const { // O(log N)
    unordered_map<Movie*, int> moviesWithCompScore;
    vector<string> watchHistory = user -> get_watch_history(); // O(log N)
    for (int i = 0; i < watchHistory.size(); i ++){ // O(1) assuming that the size is a constant (never infinite long)
        Movie *movie = m_movieDB -> get_movie_from_id(watchHistory[i]); //O(log N)
        if (movie != nullptr){
            vector<string> directorList = movie -> get_directors(); // O(1)
            for (int j = 0; j < directorList.size(); j ++){ // O(1)
                vector<Movie*> movieList = m_movieDB -> get_movies_with_director(directorList[i]); // O(log N)
                for (int k = 0; k < movieList.size(); k ++) // O(1)
                    moviesWithCompScore[movieList[k]] = 20; // O(1)
            }
        }
    }
    return moviesWithCompScore;
}

void Recommender::calcCompScoreForActors(User* user, unordered_map<Movie*, int> &moviesWithCompScore) const { // O(log N)
    vector<string> watchHistory = user -> get_watch_history();
    for (int i = 0; i < watchHistory.size(); i ++){
        Movie *movie = m_movieDB -> get_movie_from_id(watchHistory[i]);
        if (movie != nullptr){
            vector<string> actorList = movie -> get_actors();
            for (int j = 0; j < actorList.size(); j ++){
                vector<Movie*> movieList = m_movieDB -> get_movies_with_actor(actorList[i]);
                for (int k = 0; k < movieList.size(); k ++)
                    moviesWithCompScore[movieList[k]] += 30;
            }
        }
    }
}

void Recommender::calcCompScoreForGenre(User* user, unordered_map<Movie*, int> &moviesWithCompScore) const { // O(log N)
    vector<string> watchHistory = user -> get_watch_history();
    for (int i = 0; i < watchHistory.size(); i ++){
        Movie *movie = m_movieDB -> get_movie_from_id(watchHistory[i]);
        if (movie != nullptr){
            vector<string> genreList = movie -> get_genres();
            for (int j = 0; j < genreList.size(); j ++){
                vector<Movie*> movieList = m_movieDB -> get_movies_with_genre(genreList[i]);
                for (int k = 0; k < movieList.size(); k ++)
                    moviesWithCompScore[movieList[k]] += 1;
            }
        }
    }
}

bool Recommender::comp(const MovieAndRank& left, const MovieAndRank& right) const { // O (1)
    if (left.compatibility_score != right.compatibility_score)
        return left.compatibility_score > right.compatibility_score;
    else if (m_movieDB->get_movie_from_id(left.movie_id)->get_rating() != m_movieDB->get_movie_from_id(right.movie_id)->get_rating()) {
        return m_movieDB->get_movie_from_id(left.movie_id)->get_rating() > m_movieDB->get_movie_from_id(right.movie_id)->get_rating();
    }
    else
        return m_movieDB->get_movie_from_id(left.movie_id)->get_title() < m_movieDB->get_movie_from_id(right.movie_id)->get_title();
}

int Recommender::partition(std::vector<MovieAndRank> &vector, int left, int right) const {
    int pivotIndex = left + (right - left) / 2;
    MovieAndRank pivotValue = vector[pivotIndex];
    int i = left, j = right;
    while(i <= j) {
        while(comp(vector[i], pivotValue)) {
            i++;
        }
        while(comp(pivotValue, vector[j])) {
            j--;
        }
        if(i <= j) {
            MovieAndRank temp = vector[i];
            vector[i] = vector[j];
            vector[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void Recommender::sort(std::vector<MovieAndRank> &vector, int left, int right) const { // O(NlogN)
    if(left < right) {
        int pivotIndex = partition(vector, left, right);
        sort(vector, left, pivotIndex - 1);
        sort(vector, pivotIndex, right);
    }
}