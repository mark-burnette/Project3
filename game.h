#include <iostream>
#include <vector>

using namespace std;

class Game {
    string name;
    vector<string> genres;
    string website;
    vector<string> platforms;
    string esrb;
    int metacritic_rating;
    float user_rating;
    int num_user_ratings;
    int num_user_suggestions;
    int recommendation_score;
    public:
        void printGameInfo();
        int recommendationScore(); //how we will rank the games, I was thinking with a combination of metacritic & user ratings
};
