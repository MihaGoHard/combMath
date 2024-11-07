#include <iostream>
#include <vector>
#include <chrono>


void PrintArr(std::vector<int>& inputArr)
{
    for (int i = 0; i < inputArr.size(); ++i)
        std::cout << inputArr[i] << " ";
    std::cout << std::endl;
}

int main() {
    std::cout << "Please, enter the number of elements: ";
    int amountOfEl;
    std::cin >> amountOfEl;
    std::cout << "\n";

    auto start = std::chrono::high_resolution_clock::now();

    int amountOfElWithBorders = amountOfEl + 2;

    std::vector<int> currentPermutation(amountOfElWithBorders);
    std::vector<int> reversePermutation(amountOfElWithBorders);
    std::vector<int> direction(amountOfElWithBorders);

    for (int i = 1; i <= amountOfEl; ++i) {
        currentPermutation[i] = i;
        reversePermutation[i] = i;
        direction[i] = -1;
    }

    direction[0] = 0;
    currentPermutation[0] = amountOfEl + 1;
    currentPermutation.back() = amountOfEl + 1;

    int border = 0;

    while (border != 1) {
        //PrintArr(currentPermutation);
        border = amountOfEl;

        while (currentPermutation[reversePermutation[border] + direction[border]] > border && border > 1) {
            direction[border] = -direction[border];
            border = border - 1;
        }

        std::swap(currentPermutation[reversePermutation[border]],
            currentPermutation[reversePermutation[border] + direction[border]]);
        std::swap(reversePermutation[currentPermutation[reversePermutation[border]]],
            reversePermutation[border]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Duration: " << duration.count() << " seconds" << std::endl;

    return 0;
}
