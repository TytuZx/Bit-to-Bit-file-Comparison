#include <iostream> 
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include <chrono>

int main(/*int argc, char* argv[]*/)
{
    auto start = std::chrono::steady_clock::now();
   /* if (argc > 1) { //wczytanie plików jeśli są argumenty
        std::ifstream file1(argv[1], std::ios::binary);
        std::ifstream file2(argv[2], std::ios::binary);
        }*/

    /*stat(argv[1], &results);//rozmiar plików
    int size1 = results.st_size;
    stat(argv[2], &results);
    int size2 = results.st_size;*/

 
    std::fstream file1("file1.bin", std::ios::binary | std::ios::in | std::ios::out);//wczytanie pliku
    file1.seekg(0, std::ios::end); //rozmiar pliku 2
    int size1 = file1.tellg();
    file1.seekg(0, std::ios::beg);
    std::cout << size1 << std::endl;
 
        size1 = size1 * 8;
        char* buffer1 = new char(size1); //tablica na plik
        file1.read(buffer1, size1); //odczyt danych z pliku
    
    file1.close();//zamkniecie pliku na zakonczenie

    std::fstream file2("file2.bin", std::ios::binary | std::ios::in | std::ios::out);
    file2.seekg(0, std::ios::end);
    long size2 = file2.tellg();
    file2.seekg(0, std::ios::beg);
    std::cout << size2 << std::endl;

        size2 = size2 * 8;
        char* buffer2 = new char(size2);
        file2.read(buffer2, size2);
    
    file2.close();

    int errorcount=0;//obliczanie błędów
    for (int i = 0; i <= size1; i++) {
        if (buffer1[i] != buffer2[i]) {
            errorcount += 1;
        }
        }

    int BER=0;
    if (errorcount != 0) //obliczanie BER
    {
        BER = (errorcount / size1) * 100;
    }
    else
    {
        BER = 0;
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "Wyniki porowniani:" << std::endl;
    std::cout << "ilosc porownanych bitow = " << size1 << std::endl;
    std::cout << "ilosc roznych bitow = " << errorcount << std::endl;
    std::cout << "BER = " << BER << "%" << std::endl;
    std::cout << "czas obliczen = " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() <<" s." << std::endl;
}