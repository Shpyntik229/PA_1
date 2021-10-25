#include "common.h"
#include "ldfs.h"

using namespace std;

static thread_local int LDFS_res = MAX_DEPTH + 1;

static thread_local vector<Field> path(MAX_DEPTH);

static bool LDFS(Field& field, Coords empty, int depth = 0, Pos lastPos = Unknown)
{
    if (depth == MAX_DEPTH) return false;
    if (!isCorrect(field))
    {
        bool solve = false;
        if (empty.i != 0 && lastPos != Up) {
            swap(field[empty.i][empty.j], field[empty.i - 1][empty.j]);
            solve |= LDFS(field, { empty.i - 1, empty.j }, depth + 1, Down);
            swap(field[empty.i][empty.j], field[empty.i - 1][empty.j]);
        }
        if (empty.i != 2 && lastPos != Down) {
            swap(field[empty.i][empty.j], field[empty.i + 1][empty.j]);
            solve |= LDFS(field, { empty.i + 1, empty.j }, depth + 1, Up);
            swap(field[empty.i][empty.j], field[empty.i + 1][empty.j]);
        }
        if (empty.j != 0 && lastPos != Left) {
            swap(field[empty.i][empty.j], field[empty.i][empty.j - 1]);
            solve |= LDFS(field, { empty.i, empty.j - 1 }, depth + 1, Right);
            swap(field[empty.i][empty.j], field[empty.i][empty.j - 1]);
        }
        if (empty.j != 2 && lastPos != Right) {
            swap(field[empty.i][empty.j], field[empty.i][empty.j + 1]);
            solve |= LDFS(field, { empty.i, empty.j + 1 }, depth + 1, Left);
            swap(field[empty.i][empty.j], field[empty.i][empty.j + 1]);
        }
        if (solve) {
            path[depth] = field;
            return true;
        }
    }
    else if (depth < LDFS_res) {
        path[depth] = field;
        LDFS_res = depth;
        return true;
    }
    return false;
}

optional<vector<Field>> puzzle8SolveLDFS(Field field) {
    if (!LDFS(field, find_empty(field))) {
        return nullopt;
    }
    path.resize(LDFS_res + 1);
    auto res = path;
    LDFS_res = 100;
    path.resize(MAX_DEPTH);
    return res;
}