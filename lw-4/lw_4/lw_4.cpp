#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

constexpr int MAX_MATRIX_SIZE = 100;

typedef std::vector<std::vector<int> > Matrix;

struct Data
{
	std::vector<std::vector<int>> edges;
	std::vector<int> matchingPair; 
	std::vector<bool> usedPair; 
	int leftSize = 0;
	int rightSize = 0;
};

struct Args
{
	std::string inputFileName;
};

std::optional<Args> Parse(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Args error" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];

	return args;
}

int GetFileMatrix(std::ifstream& input, Matrix& field, int sizeX, int sizeY)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			input >> field[i][j];
		}
	}

	return 0;
}


Data GetMatrixData(Matrix& matrix, int sizeX, int sizeY)
{
	Data data;

	data.edges.resize(sizeY);

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (matrix[i][j])
			{
				data.edges[i].push_back(j);
			}
		}
	}

	data.leftSize = sizeY;
	data.rightSize = sizeX;

	return data;
}

bool ApplyKunnAlgorithm(Data& data, int vertex)
{
	if (data.usedPair[vertex])
	{
		return false;
	}

	data.usedPair[vertex] = true;
	for (size_t i = 0; i < data.edges[vertex].size(); ++i)
	{
		int to = data.edges[vertex][i];
		if (data.matchingPair[to] == -1 || ApplyKunnAlgorithm(data, data.matchingPair[to]))
		{
			data.matchingPair[to] = vertex;
			return true;
		}
	}
	return false;
}

void ProcessKunnAlgorithm(Data& data)
{
	data.matchingPair.assign(data.rightSize, -1);
	for (int vertexNumber = 0; vertexNumber < data.leftSize; vertexNumber++)
	{
		data.usedPair.assign(data.leftSize, false);
		ApplyKunnAlgorithm(data, vertexNumber);
	}
}

void OutputKunnResult(Data data)
{
	bool isHaveSolution = true;
	for (int vertex = 0; vertex < data.rightSize; vertex++)
	{
		if (isHaveSolution && data.matchingPair[vertex] == -1)
		{
			isHaveSolution = false;
		}
	}

	if (!isHaveSolution)
	{
		std::cout << "No\n";
		return;
	}
	else
	{
		std::cout << "Yes\n";
		for (int vertex = 0; vertex < data.rightSize; vertex++)
		{
			std::cout << data.matchingPair[vertex] + 1 << ' ' << vertex + 1 << "\n";
		}
	}

}

int main(int argc, char* argv[])
{
	auto args = Parse(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream input(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "File reading error\n";
		return 1;
	}

	int p = 0, q = 0;
	input >> p >> q;

	if (p <= 0 || p > MAX_MATRIX_SIZE || q <= 0 || q > MAX_MATRIX_SIZE)
	{
		std::cout << "Matrix error\n";
		return 1;
	}

	Matrix matrix(p, std::vector<int>(q, 0));
	GetFileMatrix(input, matrix, q, p);

	Data Data = GetMatrixData(matrix, q, p);

	ProcessKunnAlgorithm(Data);

	OutputKunnResult(Data);

	return 0;
}
