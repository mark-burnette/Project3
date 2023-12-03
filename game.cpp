#include <iostream>
#include <sstream>
#include "game.h"

using namespace std;

Game::Game() {
    name = "";
    genres = {};
    website = "";
    platforms = {};
    esrb = "";
    metacritic_rating = 0;
    user_rating = 0;
    num_user_ratings = 0;
}

Game::Game(string name, string genres, string website, string platforms, string esrb, string developers, int metacritic_rating, float user_rating, int num_user_ratings, int num_user_suggestions) {
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
    this->website = website;
    this->esrb = esrb;
    this->metacritic_rating = metacritic_rating;
    this->user_rating = user_rating;
    this->num_user_ratings = num_user_ratings;
    this->suggestions_count = num_user_suggestions; // TODO: change naming
}

void Game::printGameInfo() {
    cout << endl;
    cout << "Title: " << name << endl;
    
    cout << "Developer(s): ";
    for (int i=0; i < developers.size(); i++) {
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
    for (int i=0; i < genres.size(); i++) {
        cout << genres[i];
        if (i != genres.size() - 1)
            cout << ", ";
        else 
            cout << endl;
    }

    cout << "Supported Platforms: ";
    for (int i=0; i < platforms.size(); i++) {
        cout << platforms[i];
        if (i != platforms.size() - 1)
            cout << ", ";
        else 
            cout << endl;
    }

    cout << "Metacritic Rating: ";
    if (metacritic_rating != 0)
        cout << metacritic_rating << endl;
    else
        cout << "No Metacritic rating found!" << endl;

    cout << "Suggestions Count: ";
    if (suggestions_count != 0)
        cout << suggestions_count << endl;
    else
        cout << "No suggestion count found!" << endl;

    cout << "User Ratings: ";
    if (user_rating != 0)
        cout << user_rating << " (" << num_user_ratings << " ratings)" << endl;
    else
        cout << "No user ratings found!" << endl;
}

float Game::getRecScore() {
    float score = 0;

    // TODO: suggestion_count + (num genres in common*50) + esrb*25
    score = suggestions_count;

    return score;
}
