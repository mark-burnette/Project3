#include "sort.h"

void merge(vector<Game>& games, int low, int mid, int high) {
	vector<Game> result;

	int i = low;
	int j = mid + 1;

	while (i <= mid && j <= high) {
		if (games[i].getRecScore() >= games[j].getRecScore()) {
			result.push_back(games[i]);
			++i;
		}
		else {
			result.push_back(games[j]);
			++j;
		}
	}

	while (i <= mid) {
		result.push_back(games[i]);
		++i;
	}

	while (j <= high) {
		result.push_back(games[j]);
		++j;
	}

    // modify vector in-place
	for (int i = low; i <= high; ++i)
        games[i] = result[i-low];
}

void mergeSort(vector<Game>& games, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		mergeSort(games, low, mid);
		mergeSort(games, mid + 1, high);
		merge(games, low, mid, high);
	}
}

int partition(vector<Game>& games, int low, int high) {
    int pivot = games[high].getRecScore();

    int i = low - 1;
    for (int j = low; j <= high; j++) {
        if (games[j].getRecScore() > pivot) {
            i++;
            swap(games[i],games[j]);
        }
    }

    swap(games[i+1], games[high]);
    return i + 1;
}

void quickSort(std::vector<Game>& games, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(games, low, high);

        quickSort(games, low, pivotIndex-1);
        quickSort(games, pivotIndex+1, high);
    }
}
