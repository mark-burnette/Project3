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
    public:
        void printGameInfo();
        void setRecScore(); //how we will rank the games, I was thinking with a combination of metacritic & user ratings
        float recommendation_score; //a score of how likely we are to recommend this game based on what the user entered
};
