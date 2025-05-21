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

template <typename T, typename Compare>
void gnomeSort(T arr[], int size, Compare comp) {
    int i = 1, j = 2;
    while (i < size) {
        if (!comp(arr[i], arr[i - 1])) {
            i = j;
            j++;
        } else {
            std::swap(arr[i - 1], arr[i]);
            i--;
            if (i == 0) {
                i = j;
                j++;
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

    // Компаратори
    auto compByCountDesc = [](const CapacityCount& a, const CapacityCount& b) {
        return a.count < b.count;
    };

    auto compByComputersDesc = [](const Room& a, const Room& b) {
        return a.computers < b.computers;
    };

    auto compByBoard = [](const Room& a, const Room& b) {
        return !a.hasBoard && b.hasBoard;
    };

    auto compByCapacityAsc = [](const Room& a, const Room& b) {
        return a.capacity > b.capacity;
    };

    gnomeSort(rating, ratingSize, compByCountDesc);

    cout << "\nCapacity rating by number of rooms:\n";
    for (int i = 0; i < ratingSize; ++i) {
        cout << "Capacity: " << rating[i].capacity
             << " - " << rating[i].count << " room(s)\n";
    }

    gnomeSort(rooms, n, compByComputersDesc);
    cout << "\nSorted by number of computers (descending):\n";
    printRooms(rooms, n);

    gnomeSort(rooms, n, compByBoard);
    cout << "\nSorted by board availability (yes first):\n";
    printRooms(rooms, n);

    gnomeSort(rooms, n, compByCapacityAsc);
    cout << "\nSorted by capacity (ascending):\n";
    printRooms(rooms, n);

    return 0;
}
