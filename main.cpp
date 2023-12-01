#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "game.h"

int main() {
    // Open the CSV file
    ifstream file("game_info.txt");

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    string line;
    getline(file, line);
    line.clear();

    while (getline(file, line)) {
        cout << line << endl;

        string name;
        int metacritic;
        string website;
        float rating;
        int ratings_count;
        string platforms;
        string developers;
        string genres;
        string esrb;
        
        //  NOTE: This while loop only saves the variables we care about so that we can create Game objects
        //  I also changed the .csv file to a tab-deliminated csv file. This made it much easier to parse, but I had to modify some data
        //  (the only thing I had to do is remove newlines, because they were causing problems with getline()).
        //  The edited data set is shared with you on google drive

        stringstream ss(line);
        string tempStr;
        getline(ss, tempStr, '\t'); //id
        getline(ss, tempStr, '\t'); //slug

        getline(ss, name, '\t'); //name

        tempStr.clear();
        getline(ss, tempStr, '\t'); //metacritic
        if (tempStr.empty())
            metacritic = 0;
        else
            metacritic = stoi(tempStr);

        getline(ss, tempStr, '\t'); //released
        getline(ss, tempStr, '\t'); //tba
        getline(ss, tempStr, '\t'); //updated

        getline(ss, website, '\t'); //website

        tempStr.clear();
        getline(ss, tempStr, '\t'); //rating
        rating = stof(tempStr);

        getline(ss, tempStr, '\t'); //rating_top
        getline(ss, tempStr, '\t'); //playtime
        getline(ss, tempStr, '\t'); //achievements

        tempStr.clear();
        getline(ss, tempStr, '\t'); //ratings_count
        ratings_count = stoi(tempStr);

        getline(ss, tempStr, '\t'); //suggestions
        getline(ss, tempStr, '\t'); //game_series
        getline(ss, tempStr, '\t'); //reviews_count

        getline(ss, platforms, '\t'); //platforms
        getline(ss, developers, '\t'); //developer
        getline(ss, genres, '\t'); //genres

        getline(ss, tempStr, '\t'); //publishers

        getline(ss, esrb, '\t'); //esrb

        //TODO: use this data to make game objects
        //TODO: make a vector of all of the game objects
    }

    return 0;
}
