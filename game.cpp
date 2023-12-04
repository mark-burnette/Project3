#include <iostream>
#include <sstream>
#include "game.h"

using namespace std;

Game::Game() {
    name = "";
    genres = {};
    genreMatchCount = 0;
    website = "";
    platforms = {};
    esrb = "";
    esrbMatch = false;
    metacritic = 0;
    rating = 0;
    ratingsCount = 0;
    suggestionsCount = 0;
}

Game::Game(string name, string genres, int genreMatchCount, string website, string platforms, string esrb, bool esrbMatch, string developers, int metacritic, float rating, int ratingsCount, int suggestionsCount) {
    // get genres
    stringstream ss(genres);
    string tmp;
    while (getline(ss, tmp, '|')) {
        // tmp may be empty as getline() only takes 1 delimiter, but there are 2 '|'s
        if (tmp.size() != 0)
            this->genres.push_back(tmp);
    }

    // get platforms
    ss.clear();
    ss.str(platforms);
    while (getline(ss, tmp, '|')) {
        if (tmp.size() != 0)
            this->platforms.push_back(tmp);
    }

    // get developers
    ss.clear();
    ss.str(developers);
    while (getline(ss, tmp, '|')) {
        if (tmp.size() != 0)
            this->developers.push_back(tmp);
    }

    this->name = name;
    this->genreMatchCount = genreMatchCount;
    this->website = website;
    this->esrb = esrb;
    this->esrbMatch = esrbMatch;
    this->metacritic = metacritic;
    this->rating = rating;
    this->ratingsCount = ratingsCount;
    this->suggestionsCount = suggestionsCount;

    recScore = suggestionsCount + (genreMatchCount * 50);
    if (esrbMatch)
        recScore += 25;
}

void Game::print() {
    cout << endl;
    cout << "Title: " << name << endl;
    
    cout << "Developer(s): ";
    for (int i = 0; i < developers.size(); i++) {
        cout << developers[i];
        if (i != developers.size() - 1)
            cout << ", ";
        else 
            cout << endl;
    }

    cout << "Website: ";
    if (website.size() > 0)
        cout << website << endl;
    else 
        cout << "No website found!" << endl;
    
    cout << "ESRB Rating: ";
    if (esrb.size() > 0)
        cout << esrb << endl;
    else 
        cout << "No ESRB rating found!" << endl;
        
    cout << "Genre(s): ";
    if (genres.size() != 0) {
        for (int i = 0; i < genres.size(); i++) {
            cout << genres[i];
            if (i != genres.size() - 1)
                cout << ", ";
            else 
                cout << endl;
        }
    }
    else
        cout << "No genres found!" << endl;

    cout << "Supported Platforms: ";
    for (int i = 0; i < platforms.size(); i++) {
        cout << platforms[i];
        if (i != platforms.size() - 1)
            cout << ", ";
        else 
            cout << endl;
    }

    cout << "Metacritic Rating: ";
    if (metacritic != 0)
        cout << metacritic << endl;
    else
        cout << "No Metacritic rating found!" << endl;

    cout << "Suggestions Count: ";
    if (suggestionsCount != 0)
        cout << suggestionsCount << endl;
    else
        cout << "No suggestion count found!" << endl;

    cout << "User Ratings: ";
    if (rating != 0)
        cout << rating << " (" << ratingsCount << " ratings)" << endl;
    else
        cout << "No user ratings found!" << endl;
}

int Game::getRecScore() {
    return recScore;
}
