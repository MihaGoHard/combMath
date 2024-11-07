#include <iostream>
#include <vector>
#include <random>

void Print(std::vector<int> const& v)
{
    for (int i : v) {
        std::cout << i << ' ';
    }
}

void ShuffleVector(std::vector<int>& v)
{
    int randomNumb;
    for (int i = 0; i < v.size(); ++i)
    {
        randomNumb = rand() % v.size();
        std::swap(v[i], v[randomNumb]);
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> v = { 2, 4, 6, 8, 9, 11};

    std::cout << "base vector: " << " ";

    Print(v);
 
    char isRepeating = 'y';
    	do
    	{
            ShuffleVector(v);
            std::cout << "shuffled vector: " << " ";
            
            Print(v);
            
    		std::cout << "\nrestart? y/n : ";
    		std::cin >> isRepeating;
    	} while (isRepeating == 121);
    
    return 0;
}


