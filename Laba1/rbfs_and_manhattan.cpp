#include <cmath>
#include <iostream>
#include <map>

#include "rbfs_and_manhattan.h"

using namespace std;

constexpr int MAX_F_VALUE = 100'000;

bool isSolved(const Field& field) {
	int inversions = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = i + 1; j < 9; j++) {
			if (field[i / 3][i % 3] != -1 && field[j / 3][j % 3] && field[i / 3][i % 3] > field[j / 3][j % 3]) {
				inversions++;
			}
		}
	}
	return inversions % 2 == 0;
}

int g(const Field& field) {
	int distances = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (field[i][j] != -1) {
				distances += abs(field[i][j] / 3 - i) + abs(field[i][j] % 3 - j);
			}
		}
	}
	return distances;
}

static thread_local int result = -1;
//static thread_local map<Field, int> checker;

int f(Field field, Coords empty, int depth, Pos dir) {
	if (dir == Up) {
		if (empty.i == 0) return MAX_F_VALUE;
		swap(field[empty.i][empty.j], field[empty.i - 1][empty.j]);
		return g(field) + depth + 1;
		swap(field[empty.i][empty.j], field[empty.i - 1][empty.j]);
	}
	else if (dir == Down) {
		if (empty.i == 2) return MAX_F_VALUE;
		swap(field[empty.i][empty.j], field[empty.i + 1][empty.j]);
		return g(field) + depth + 1;
		swap(field[empty.i][empty.j], field[empty.i + 1][empty.j]);
	}
	else if (dir == Left) {
		if (empty.j == 0) return MAX_F_VALUE;
		swap(field[empty.i][empty.j], field[empty.i][empty.j - 1]);
		return g(field) + depth + 1;
		swap(field[empty.i][empty.j], field[empty.i][empty.j - 1]);
	}
	else if (dir == Right) {
		if (empty.j == 2) return MAX_F_VALUE;
		swap(field[empty.i][empty.j], field[empty.i][empty.j + 1]);
		return g(field) + depth + 1;
		swap(field[empty.i][empty.j], field[empty.i][empty.j + 1]);
	}
	return MAX_F_VALUE;
}

int RBFS(Field& field, Coords empty, int depth = 0, int f_value = MAX_F_VALUE) {
	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << (int)field[i][j] + 1 << " ";
		}
		cout << "\n";
	}
	cout << endl;*/
	int g_value = g(field);
	if (g_value == 0) {
		result = depth;
		return 0;
	}
	else {
		//if (checker.count(field) && checker[field] < depth) return MAX_F_VALUE;
		//checker[field] = depth;
		int up = f(field, empty, depth, Up), down = f(field, empty, depth, Down), left = f(field, empty, depth, Left), right = f(field, empty, depth, Right);
		Pos first = Unknown, second;
		int minimum = MAX_F_VALUE, second_min = MAX_F_VALUE;
		if (up < second_min) {
			second_min = up;
			second = Up;
		}
		if (down < second_min) {
			second_min = down;
			second = Down;
		}
		if (left < second_min) {
			second_min = left;
			second = Left;
		}
		if (right < second_min) {
			second_min = right;
			second = Right;
		}
		while (true) {
			minimum = second_min;
			first = second;
			second = Unknown;
			second_min = MAX_F_VALUE;
			if (minimum == MAX_F_VALUE || minimum > f_value) return minimum;
			if (first != Up && up < second_min) {
				second_min = up;
				second = Up;
			}
			if (first != Down && down < second_min) {
				second_min = down;
				second = Down;
			}
			if (first != Left && left < second_min) {
				second_min = left;
				second = Left;
			}
			if (first != Right && right < second_min) {
				second_min = right;
				second = Right;
			}

			switch (first) {
			case Up:
				swap(field[empty.i][empty.j], field[empty.i - 1][empty.j]);
				up = RBFS(field, { empty.i - 1, empty.j }, depth + 1, min(f_value, second_min));
				swap(field[empty.i][empty.j], field[empty.i - 1][empty.j]);
				if (!up) return 0;
				break;
			case Down:
				swap(field[empty.i][empty.j], field[empty.i + 1][empty.j]);
				down = RBFS(field, { empty.i + 1, empty.j }, depth + 1, min(f_value, second_min));
				swap(field[empty.i][empty.j], field[empty.i + 1][empty.j]);
				if (!down) return 0;
				break;
			case Left:
				swap(field[empty.i][empty.j], field[empty.i][empty.j - 1]);
				left = RBFS(field, { empty.i, empty.j - 1 }, depth + 1, min(f_value, second_min));
				swap(field[empty.i][empty.j], field[empty.i][empty.j - 1]);
				if (!left) return 0;
				break;
			case Right:
				swap(field[empty.i][empty.j], field[empty.i][empty.j + 1]);
				right = RBFS(field, { empty.i, empty.j + 1 }, depth + 1, min(f_value, second_min));
				swap(field[empty.i][empty.j], field[empty.i][empty.j + 1]);
				if (!right) return 0;
				break;
			}
		}
	}
}

optional<int> puzzle8SolveRBFS(Field field)
{
	if (!isSolved(field)) return nullopt;
	RBFS(field, find_empty(field));
	return result;
}
