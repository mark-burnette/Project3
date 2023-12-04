#pragma once

#include <iostream>
#include <vector>
#include "game.h"

using namespace std;

void merge(vector<Game>& games, int low, int mid, int high);
void mergeSort(vector<Game>& games, int low, int high);

int partition(vector<Game>& games, int low, int high);
void quickSort(std::vector<Game>& games, int low, int high);
