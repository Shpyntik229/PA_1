#include "common.h"

using namespace std;

bool isCorrect(const Field& field) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] != i * 3 + j && !(i == 2 && j == 2)) return false;
        }
    }
    return true;
}

Coords find_empty(const Field& field) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] == -1) return { i, j };
        }
    }
    return { -1, -1 };
}

void decrementEachValue(Field& field) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) {
            field[i][j]--;
        }
    }
}