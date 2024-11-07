#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <fstream>

constexpr int MAX_MATRIX_SIZE = 400;

struct Args
{
	std::string inputFileName;
};

typedef std::vector<std::vector<int> > Matrix;

std::optional<Args> Parse(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "argument count error\n";
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

int GetStreamMatrix(std::ifstream& input, Matrix& field, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			input >> field[i][j];
		}
	}

	return 0;
}

Matrix GetMatrixTransposed(Matrix& matrix, int n)
{
	Matrix matrixTransposed(n, std::vector<int>(n, 0));

	for (int row = 0; row < n; ++row)
	{
		for (int col = 0; col < n; ++col)
		{
			matrixTransposed[col][row] = matrix[row][col];
		}
	}
	return matrixTransposed;
}

void SearchDeepSort(Matrix const& matrix, int vertex, std::vector<bool>& visited, std::vector<int>& topSort)
{
	visited[vertex] = true;
	for (int i = 0; i < visited.size(); ++i)
	{
		int weight = matrix[vertex][i];
		if ((weight != 0) && (!visited[i]))
		{
			SearchDeepSort(matrix, i, visited, topSort);
		}

	}
	topSort.push_back(vertex);
}

void DetectStrongComponent(Matrix const& matrix, int vertex, std::vector<bool>& visited)
{
	visited[vertex] = true;
	for (int i = 0; i < matrix[vertex].size(); ++i)
	{
		int weight = matrix[vertex][i];
		if ((weight != 0) && (!visited[i]))
		{
			DetectStrongComponent(matrix, i, visited);
		}
	}
}

int main(int argc, char* argv[])
{
	std::vector<bool> visited;
	std::vector<int> topSortVertex;
	int countVertex = 0;
	int countSCC = 0;

	auto args = Parse(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream input(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "reading file error\n";
		return 1;
	}

	input >> countVertex;

	if (countVertex <= 0 || countVertex > MAX_MATRIX_SIZE)
	{
		std::cout << "matrix size error\n";
		return 1;
	}

	Matrix matrix(countVertex, std::vector<int>(countVertex, 0));
	GetStreamMatrix(input, matrix, countVertex);
	Matrix tMatrix = GetMatrixTransposed(matrix, countVertex);

	visited.assign(countVertex, false);
	for (int i = 0; i < countVertex; ++i)
	{
		if (!visited[i])
		{
			SearchDeepSort(matrix, i, visited, topSortVertex);
		}
	}

	visited.assign(countVertex, false);

	for (int i = 0; i < countVertex; ++i)
	{
		int vertex = topSortVertex[countVertex - 1 - i];
		if (!visited[vertex])
		{
			FindStrongComponent(tMatrix, vertex, visited);
			countSCC++;
		}
	}

	if (countSCC > 1)
	{
		std::cout << "no\n";
	}
	else if (countSCC == 1)
	{
		std::cout << "yes\n";
	}
	else
	{
		std::cout << "Hard related components not found\n";
	}

	return 0;
}
