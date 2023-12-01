#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "game.h"

int main() {
    // Open the CSV file
    std::ifstream file("game_info.csv");

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    string line;
    getline(file, line);
    line.clear();

    while (getline(file, line)) {
        string name;
        int metacritic;
        string website;
        float rating;
        int ratings_count;
        string platforms;
        string developers;
        string genres;
        string esrb;

        //
        //  NOTE: This only saves the variables we care about so that we can create Game objects
        //

        stringstream ss(line);
        string tempStr;
        getline(ss, tempStr, ','); //id
        getline(ss, tempStr, ','); //slug

        //TODO: fix, this causes errors because commas and quotes can be contained in the title
        //this same error can happen for the developers and publishers variable :(
        getline(ss, name, ','); //name

        tempStr.clear();
        getline(ss, tempStr, ','); //metacritic
        if (tempStr.empty())
            metacritic = 0;
        else
            metacritic = stoi(tempStr);

        getline(ss, tempStr, ','); //released
        getline(ss, tempStr, ','); //tba
        getline(ss, tempStr, ','); //updated

        getline(ss, website, ','); //website

        tempStr.clear();
        getline(ss, tempStr, ','); //rating
        rating = stof(tempStr);

        getline(ss, tempStr, ','); //rating_top
        getline(ss, tempStr, ','); //playtime
        getline(ss, tempStr, ','); //achievements

        tempStr.clear();
        getline(ss, tempStr, ','); //ratings_count
        ratings_count = stoi(tempStr);

        getline(ss, tempStr, ','); //suggestions
        getline(ss, tempStr, ','); //game_series
        getline(ss, tempStr, ','); //reviews_count

        getline(ss, platforms, ','); //platforms
        getline(ss, developers, ','); //developer
        getline(ss, genres, ','); //genres

        getline(ss, tempStr, ','); //publishers

        getline(ss, esrb, ','); //esrb

        //TODO: use this data to make game objects
        //TODO: make a vector of all of the game objects
    }

    return 0;
}
