#include <iostream>
#include <vector>

using namespace std;

class Game {
    string name;
    vector<string> genres;
    string website;
    vector<string> platforms;
    vector<string> developers;
    string esrb;
    int metacritic_rating; // TODO: change naming conventions for consistency (snake_case camelCase)
    float user_rating;
    int num_user_ratings;
    int suggestions_count;
public:
    Game();
    Game(string name, string genres, string website, string platforms, string esrb, string developers, int metacritic_rating, float user_rating, int num_user_ratings, int num_user_suggestions);

    void printGameInfo();
    float getRecScore();
};
