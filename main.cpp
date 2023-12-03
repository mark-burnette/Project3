#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
#include "game.h"

vector<string> promptUser() {
    /* prompting the user for a game they enjoy playing may lead to possible issues
     * instead, we can give the user a list of genres and ask them to indicate which one(s) they enjoy
     */

    vector<string> genres = {"Action", "Adventure", "Arcade", "Board Games", "Card", "Casual", "Educational", "Family", "Fighting", "Indie", "Massively Multiplayer", "Platformer", "Puzzle", "RPG", "Racing", "Shooter", "Simulation", "Sports", "Strategy"};
    vector<string> selected_genres{};

    int num = -1;
    while (num != 0) {
		cout << endl;
		cout << 0 << ") Exit" << endl;
		for (int i = 0; i < genres.size(); i++)
			cout << i+1 << ") " << genres[i] << endl;

        if (selected_genres.size() > 0) {
            cout << endl;
            cout << "Currently selected genre(s): ";

            for (int i = 0; i < selected_genres.size(); i++) {
                cout << selected_genres[i];
                if (i != selected_genres.size() - 1)
                    cout << ", ";
            }
        }

        cout << endl;
        cout << "Which genre(s) would you like to see? (select a number, or select 0 to generate recommendations): ";
        cin >> num;

        if (num == 0)
            break;

        if (num < 0 || num > genres.size()) {
            cerr << "Invalid option. Please choose again." << endl;
            continue;
        }

        selected_genres.push_back(genres[num-1]);
    }

    return selected_genres;
}

vector<Game> merge(vector<Game>& left, vector<Game>& right) {
    vector<Game> result{};

    while (!left.empty() && !right.empty()) {
        if (left[0].getRecScore() >= right[0].getRecScore()) {
            result.push_back(left[0]);
            left.erase(left.begin()); // TODO: with vectors this is very slow, use a queue
        }
        else {
            result.push_back(right[0]);
            right.erase(right.begin());
        }
    }

    for (const auto& x : left)
        result.push_back(x);

    for (const auto& x : right)
        result.push_back(x);

    return result;
}

vector<Game> mergeSort(const std::vector<Game>& games) {
    if (games.size() <= 1)
		return games;

    int mid = games.size() / 2;

    std::vector<Game> left{};
    for (int i = 0; i < mid; i++)
        left.push_back(games[i]);

    left = mergeSort(left);

    std::vector<Game> right{};
    for (int i = mid; i < games.size(); i++)
        right.push_back(games[i]);

    right = mergeSort(right);

    return merge(left, right);
}

int main() {
	// Prompt user for genres
    vector<string> chosen_genres = promptUser(); // TODO: allow user to choose ESRB rating and platforms
    if (chosen_genres.size() == 0)
		throw runtime_error{"Error: no genres selected."}; // TODO: if user selects no genres, use all genres?

    // Open the data file
    ifstream file("game_info.txt");
    if (!file.fail()) {
	    throw runtime_error{"Error opening file. Please ensure game_info.txt is in the same directory as the binary."};
    }

    string line;
    getline(file, line);
    line.clear();

    std::vector<Game> games{};

    while (getline(file, line)) {
        //cout << line << endl;

        string name;
        int metacritic;
        string website;
        float rating;
        int ratings_count;
		int suggestions_count;
        string platforms;
        string developers;
        string genres;
        string esrb;
        
        //  NOTE: This while loop only saves the variables we care about so that we can create Game objects
	
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

        getline(ss, tempStr, '\t'); //suggestions_count
		suggestions_count = stoi(tempStr);

        getline(ss, tempStr, '\t'); //game_series
        getline(ss, tempStr, '\t'); //reviews_count

        getline(ss, platforms, '\t'); //platforms
        getline(ss, developers, '\t'); //developer
        getline(ss, genres, '\t'); //genres

	// if game does not fit any of the user's selected genres, ignore it
	bool match = false;
	for (const auto& chosen_genre : chosen_genres) {
		if (genres.find(chosen_genre) != string::npos) {
			match = true;
			break;
		}
	}

	if (match == false)
		continue;

        getline(ss, tempStr, '\t'); //publishers

        getline(ss, esrb, '\t'); //esrb

		// make game object and add to list of recommendations
		Game game{name, genres, website, platforms, esrb, developers, metacritic, rating, ratings_count, suggestions_count};
		games.push_back(game);
    }

    games = mergeSort(games);

    return 0;
}
