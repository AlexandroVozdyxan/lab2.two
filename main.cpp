#include <iostream>
using namespace std;

const int MAX_ROOMS = 100;

struct Room {
    int number;
    int capacity;
    bool hasBoard;
    int computers;
};

struct CapacityCount {
    int capacity;
    int count;
};

int findCapacityIndex(CapacityCount arr[], int size, int capacity) {
    for (int i = 0; i < size; ++i) {
        if (arr[i].capacity == capacity) {
            return i;
        }
    }
    return -1;
}

void sortByCount(CapacityCount arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[j].count > arr[i].count) {
                CapacityCount temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sortByComputers(Room arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[j].computers > arr[i].computers) {
                Room temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sortByBoard(Room arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[j].hasBoard && !arr[i].hasBoard) {
                Room temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void printRooms(const Room rooms[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << "Room #" << rooms[i].number
             << " | Seats: " << rooms[i].capacity
             << " | Board: " << (rooms[i].hasBoard ? "yes" : "no")
             << " | Computers: " << rooms[i].computers << endl;
    }
}

int main() {
    const int n = 8;
    Room rooms[n] = {
        {101, 30, true, 10},
        {102, 25, true, 5},
        {103, 30, false, 0},
        {104, 20, true, 8},
        {105, 25, false, 0},
        {106, 20, true, 12},
        {107, 30, true, 15},
        {108, 20, false, 0}
    };

    cout << "List of rooms:\n";
    printRooms(rooms, n);

    CapacityCount rating[MAX_ROOMS];
    int ratingSize = 0;

    for (int i = 0; i < n; ++i) {
        int index = findCapacityIndex(rating, ratingSize, rooms[i].capacity);
        if (index == -1) {
            rating[ratingSize].capacity = rooms[i].capacity;
            rating[ratingSize].count = 1;
            ratingSize++;
        } else {
            rating[index].count++;
        }
    }

    sortByCount(rating, ratingSize);

    cout << "\nCapacity rating by number of rooms:\n";
    for (int i = 0; i < ratingSize; ++i) {
        cout << "Capacity: " << rating[i].capacity
             << " - " << rating[i].count << " room(s)\n";
    }

    sortByComputers(rooms, n);
    cout << "\nSorted by number of computers (descending):\n";
    printRooms(rooms, n);

    sortByBoard(rooms, n);
    cout << "\nSorted by board availability (yes first):\n";
    printRooms(rooms, n);

    return 0;
}
