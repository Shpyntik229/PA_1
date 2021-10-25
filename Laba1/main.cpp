#include <iostream>
#include <array>
#include <utility>
#include <optional>
#include <vector>
#include <stack>

#include "ldfs.h"
#include "rbfs_and_manhattan.h"

using namespace std;

int main()
{
    Field field;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int n;
            cin >> n;
            field[i][j] = n - 1;
        }
    }
    cout << "LDFS\n";
    if (optional res = puzzle8SolveLDFS(field); res) {
        cout << "\n" << res.value().size() - 1 << "\n\n";
        for (const auto& f : res.value()) {
            for (const auto& row : f) {
                for (int v : row) {
                    cout << v+1 << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
    }
    else {
        cout << "No way!";
    }
    cout << endl;
    cout << "RBFS\n";
    if (optional res = puzzle8SolveRBFS(field); res) {
        cout << res.value();
    }
    else {
        cout << "No way!";
    }
    return 0;
}