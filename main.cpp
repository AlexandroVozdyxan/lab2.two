#include <iostream>
#include <cmath>
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
            swap(arr[i - 1], arr[i]);
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

int jumpSearch(Room arr[], int size, int target) {
    int step = sqrt(size);
    int prev = 0;

    while (arr[min(step, size) - 1].number < target) {
        prev = step;
        step += sqrt(size);
        if (prev >= size) return -1;
    }

    for (int i = prev; i < min(step, size); ++i) {
        if (arr[i].number == target) return i;
    }

    return -1;
}

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

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

    auto compByCountDesc = [](const CapacityCount& a, const CapacityCount& b) {
        return a.count < b.count;
    };
    auto compByNumberAsc = [](const Room& a, const Room& b) {
        return a.number > b.number;
    };

    int choice;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Show rooms\n";
        cout << "2. Show room counts by capacity\n";
        cout << "3. Show capacity rating\n";
        cout << "4. Search room by number\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                printRooms(rooms, n);
                break;
            case 2:
                for (int i = 0; i < ratingSize; ++i) {
                    cout << "Capacity: " << rating[i].capacity
                         << " - " << rating[i].count << endl;
                }
                break;
            case 3:
                gnomeSort(rating, ratingSize, compByCountDesc);
                for (int i = 0; i < ratingSize; ++i) {
                    cout << "Capacity: " << rating[i].capacity
                         << " - " << rating[i].count << endl;
                }
                break;
            case 4: {
                gnomeSort(rooms, n, compByNumberAsc);
                int target;
                cin >> target;
                int index = jumpSearch(rooms, n, target);
                if (index != -1) {
                    cout << "Room #" << rooms[index].number
                         << " | Seats: " << rooms[index].capacity
                         << " | Board: " << (rooms[index].hasBoard ? "yes" : "no")
                         << " | Computers: " << rooms[index].computers << endl;
                } else {
                    cout << "Not found\n";
                }
                break;
            }
            case 0:
                break;
            default:
                break;
        }
    } while (choice != 0);

    return 0;
}
