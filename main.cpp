#include <iostream> 
#include <fstream>

int main(int argc, char * argv[])
{
    if (argc > 1) { //wczytanie plików
        std::ofstream file1(argv[1], std::ios::binary);
        std::ofstream file2(argv[2], std::ios::binary);
        }
    

    return 0;
}