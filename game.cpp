#include <iostream>
#include "game.h"
using namespace std;

void Game::printGameInfo() {
    cout << "Title: " << name << endl;
    cout << "Website: ";
    if (website.size() > 0)
        cout << website << endl;
    else 
        cout << "No website found!" << endl;
    
    cout << "ESRB Rating: " << endl;
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

    cout << "User Ratings: ";
    if (user_rating != 0)
        cout << user_rating << " (" << num_user_ratings << " ratings)" << endl;
    else
        cout << "No user ratings found!" << endl;

    cout << "Number of users who recommended this game: " << num_user_suggestions << endl;
}

void Game::setRecScore() {
    
}
