#include <iostream>
#include <array>
#include <utility>
#include <optional>
#include <vector>
#include <algorithm>
#include <fstream>

#include "ldfs.h"
#include "rbfs_and_manhattan.h"

using namespace std;

int main()
{
	std::ofstream out("res_table.txt");
	std::array<uint8_t, 9> matrix({ 2,1,4,
									  6,7,3,
									  5,8,0 });
	for (int i = 0; i < 20; i++) {
		Field field;
		for (int i = 0; i < 9; i++) field[i / 3][i % 3] = matrix[i];
		std::optional<int> sol1, sol2;
		Logger logger_ldfs, logger_rbfs;

		sol1 = puzzle8SolveLDFS(field, logger_ldfs);

		sol2 = puzzle8SolveRBFS(field, logger_rbfs);

		if (sol1 != sol2) {
			std::cerr << *sol1 << ' ' << *sol2 << " error!\n";
		}
		out << i + 1 << " condition\t" << logger_ldfs.getIterationCount() << '\t' << logger_ldfs.getDeafCorner() << '\t'
			<< logger_ldfs.getConditionsCount() << '\t' << logger_ldfs.getConditionsInMemoryCount() << '\t' << logger_ldfs.getTime() / 1e3 << "ms\t\t"
			<< logger_rbfs.getIterationCount() << '\t' << !sol2.has_value() << '\t'
			<< logger_rbfs.getConditionsCount() << '\t' << logger_rbfs.getConditionsInMemoryCount() << '\t' << logger_rbfs.getTime() / 1e3 << "ms\n";
		for (int j = 0, n = rand(); j < n; j++)
			std::next_permutation(matrix.begin(), matrix.end());
	}
    return 0;
}