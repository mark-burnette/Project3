#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
#include <algorithm>
#include <chrono>
#include "game.h"
#include "sort.h"

void promptUser(vector<string>& selectedGenres, vector<string>& selectedESRBRatings, vector<string>& selectedPlatforms) {
    // get user's chosen genre(s)
    vector<string> genres = {"Action", "Adventure", "Arcade", "Board Games", "Card", "Casual", "Educational", "Family", "Fighting", "Indie", "Massively Multiplayer", "Platformer", "Puzzle", "RPG", "Racing", "Shooter", "Simulation", "Sports", "Strategy"};

    int num = -1;
    while (num != 0) {
        cout << endl;
        cout << 0 << ") Exit" << endl;
        for (int i = 0; i < genres.size(); i++)
            cout << i+1 << ") " << genres[i] << endl;

        if (selectedGenres.size() > 0) {
            cout << endl;
            cout << "Currently selected genre(s): ";

            for (int i = 0; i < selectedGenres.size(); i++) {
                cout << selectedGenres[i];
                if (i != selectedGenres.size() - 1)
                    cout << ", ";
            }
        }

        cout << endl;
        cout << "Which genre(s) would you like to see? (select a number, or select 0 to continue): ";
        cin >> num;

        if (num == 0)
            break;

        if (num < 0 || num > genres.size()) {
            cerr << "Invalid option. Please choose again." << endl;
            continue;
        }

        // don't add duplicate genres
        if (std::find(selectedGenres.begin(), selectedGenres.end(), genres[num-1]) == selectedGenres.end())
            selectedGenres.push_back(genres[num-1]);
    }

    // get user's preferred ESRB rating(s)
    vector<string> esrbRatings = {"Everyone", "Everyone 10+", "Teen", "Mature", "Adults Only"};
    num = -1;
    while (num != 0) {
        cout << endl;
        cout << 0 << ") Exit" << endl;
        for (int i = 0; i < esrbRatings.size(); i++)
            cout << i+1 << ") " << esrbRatings[i] << endl;

        if (esrbRatings.size() > 0) {
            cout << endl;
            cout << "Currently selected ESRB rating(s): ";

            for (int i = 0; i < selectedESRBRatings.size(); i++) {
                cout << selectedESRBRatings[i];
                if (i != selectedESRBRatings.size() - 1)
                    cout << ", ";
            }
        }

        cout << endl;
        cout << "Which ESRB rating(s) would you prefer? (select a number, or select 0 to generate recommendations): ";
        cin >> num;

        if (num == 0)
            break;

        if (num < 0 || num > esrbRatings.size()) {
            cerr << "Invalid option. Please choose again." << endl;
            continue;
        }

        if (std::find(selectedESRBRatings.begin(), selectedESRBRatings.end(), genres[num-1]) == selectedESRBRatings.end())
            selectedESRBRatings.push_back(esrbRatings[num-1]);
    }
}

int main() {
    // prompt user for genres/esrb ratings; these vectors will be populated
    vector<string> selectedGenres{};
    vector<string> selectedESRBRatings{};
    vector<string> selectedPlatforms{};
    promptUser(selectedGenres, selectedESRBRatings, selectedPlatforms);

    // Open the data file
    ifstream file("game_info.txt");
    if (file.fail()) {
        throw runtime_error{"Error opening file. Please ensure game_info.txt is in the same directory as the binary."};
    }

    string line;
    getline(file, line);
    line.clear();

    std::vector<Game> games{};

    while (getline(file, line)) {
        string name;
        int metacritic;
        string website;
        float rating;
        int ratingsCount;
        int suggestionsCount;
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
        getline(ss, tempStr, '\t'); //ratingsCount
        ratingsCount = stoi(tempStr);

        getline(ss, tempStr, '\t'); //suggestionsCount
        suggestionsCount = stoi(tempStr);

        getline(ss, tempStr, '\t'); //game_series
        getline(ss, tempStr, '\t'); //reviews_count

        getline(ss, platforms, '\t'); //platforms

        getline(ss, developers, '\t'); //developer
        getline(ss, genres, '\t'); //genres

        // find the number of genres in common for calculating recommendation score
        int genreMatchCount = 0;
        for (const auto& selectedGenre : selectedGenres) {
            if (genres.find(selectedGenre) != string::npos) {
                genreMatchCount++;
            }
        }

        // if game does not fit any of the user's selected genres, ignore it
        // if user chose no genres, assume they want to see games of all genres
        if (genreMatchCount == 0 && selectedGenres.size() != 0)
            continue;

        getline(ss, tempStr, '\t'); //publishers
        getline(ss, esrb, '\t'); //esrb

        bool esrbMatch = false;
        if (find(selectedESRBRatings.begin(), selectedESRBRatings.end(), esrb) != selectedESRBRatings.end())
           esrbMatch = true; 

        // make game object and add to list of recommendations
        Game game{name, genres, genreMatchCount, website, platforms, esrb, esrbMatch, developers, metacritic, rating, ratingsCount, suggestionsCount};
        games.push_back(game);
    }

    // get user's chosen algorithm
    cout << endl;
    cout << "Which sorting algorithm would you like to use?" << endl;
    cout << "1) Merge Sort" << endl;
    cout << "2) Quicksort" << endl;

    int choice = 0;

    while (!(choice == 1 || choice == 2))
    {
        cin >> choice;
        if (!(choice == 1 || choice == 2))
            cout << "Invalid choice. Please enter 1 or 2." << endl;
    }

    // sort data and measure efficiency
    auto start{std::chrono::steady_clock::now()};

    if (choice == 1)
        mergeSort(games, 0, games.size() - 1);
    else
        quickSort(games, 0, games.size() - 1);
    
    auto elapsed = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(std::chrono::steady_clock::now() - start).count();

    std::cout << endl;
    string choiceStr = (choice == 1) ? "Merge Sort" : "Quicksort";
    std::cout << choiceStr << " took " << elapsed << " seconds." << endl;

    // print list of recommendations
    char done = 'y';
    while (done != 'n')
    {
        static int last = 0;
        if (done == 'y')
        {
            for (int i = 0; i < 10; i++, last++)
                games[last++].print();
        }

        cout << endl;
        cout << "Continue showing results? (y/n): ";

        cin >> done;
        if (done != 'y' && done != 'n')
            cout << "Invalid choice." << endl;
    }
    
    return 0;
}
