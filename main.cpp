#include <iostream> 
#include <fstream>
#include <sys/stat.h>

int main(/*int argc, char* argv[]*/)
{
    struct stat results;
   /* if (argc > 1) { //wczytanie plików jeśli są argumenty
        std::ifstream file1(argv[1], std::ios::binary);
        std::ifstream file2(argv[2], std::ios::binary);
        }*/

    /*stat(argv[1], &results);//rozmiar plików
    int size1 = results.st_size;
    stat(argv[2], &results);
    int size2 = results.st_size;*/

    std::ifstream file1("file1.bin", std::ios::in | std::ios::binary);
    std::ifstream file2("file2.bin", std::ios::in | std::ios::binary);

    stat("file1.bin", &results);//rozmiar plików
    int size1 = results.st_size;
    stat("file2.bin", &results);
    int size2 = results.st_size;
    

    return 0;
}