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

    // підрахунок місткостей
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

    // компаратори
    auto compByCountDesc = [](const CapacityCount& a, const CapacityCount& b) {
        return a.count < b.count;
    };
    auto compByNumberAsc = [](const Room& a, const Room& b) {
        return a.number > b.number;
    };

    int choice;
    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Вивести всі аудиторії\n";
        cout << "2. Підрахувати кількість аудиторій за місткістю\n";
        cout << "3. Побудувати рейтинг кількості кімнат по місткості\n";
        cout << "4. Пошук аудиторії за номером (jump search)\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nСписок аудиторій:\n";
                printRooms(rooms, n);
                break;

            case 2:
                cout << "\nКількість аудиторій за місткістю:\n";
                for (int i = 0; i < ratingSize; ++i) {
                    cout << "Місткість: " << rating[i].capacity
                         << " - " << rating[i].count << " аудиторій\n";
                }
                break;

            case 3:
                gnomeSort(rating, ratingSize, compByCountDesc);
                cout << "\nРейтинг кількості кімнат по місткості:\n";
                for (int i = 0; i < ratingSize; ++i) {
                    cout << "Місткість: " << rating[i].capacity
                         << " - " << rating[i].count << " аудиторій\n";
                }
                break;

            case 4: {
                gnomeSort(rooms, n, compByNumberAsc);  // сортуємо перед jump search
                int target;
                cout << "Введіть номер аудиторії для пошуку: ";
                cin >> target;
                int index = jumpSearch(rooms, n, target);
                if (index != -1) {
                    cout << "\nЗнайдено: Room #" << rooms[index].number
                         << " | Seats: " << rooms[index].capacity
                         << " | Board: " << (rooms[index].hasBoard ? "yes" : "no")
                         << " | Computers: " << rooms[index].computers << endl;
                } else {
                    cout << "Аудиторія з таким номером не знайдена.\n";
                }
                break;
            }

            case 0:
                cout << "Вихід з програми.\n";
                break;

            default:
                cout << "Невірний вибір!\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
