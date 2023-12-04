#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Game {
    string name;
    vector<string> genres;
    int genreMatchCount;
    string website;
    vector<string> platforms;
    vector<string> developers;
    string esrb;
    bool esrbMatch;
    int metacritic;
    float rating;
    int ratingsCount;
    int suggestionsCount;

    int recScore;

public:
    Game();
    Game(string name, string genres, int genreMatchCount, string website, string platforms, string esrb, bool esrbMatch, string developers, int metacritic, float rating, int ratingsCount, int suggestionsCount);

    void print();
    int getRecScore();
};
