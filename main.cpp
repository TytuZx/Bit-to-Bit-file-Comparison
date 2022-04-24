#include <iostream> 
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include <chrono>

int main(/*int argc, char* argv[]*/)
{
    auto start = std::chrono::steady_clock::now();
    struct stat results1;
    struct stat results2;
   /* if (argc > 1) { //wczytanie plików jeśli są argumenty
        std::ifstream file1(argv[1], std::ios::binary);
        std::ifstream file2(argv[2], std::ios::binary);
        }*/

    /*stat(argv[1], &results);//rozmiar plików
    int size1 = results.st_size;
    stat(argv[2], &results);
    int size2 = results.st_size;*/

    std::ifstream file1("file1", std::ios::in | std::ios::binary);//wczytanie pliku
    stat("file1", &results1);//rozmiar plików
    long size1 = results1.st_size; //rozmiar do inta
    char* buffer1=new char(size1); //tablica na plik
    file1.read(buffer1, size1); //odczyt danych z pliku
    for (int i = 0; i < size1; i++) {//wyświetlenie danych z pliku
        std::cout << buffer1[i] << std::endl;
    };
    file1.close();//zamkniecie plików na zakonczenie

    std::ifstream file2("file2", std::ios::in | std::ios::binary);
    stat("file2", &results2);
    long size2 = results2.st_size;
    char* buffer2=new char(size2);
    file2.read(buffer2, size2);
    for (int i = 0; i < size2; i++) {
        std::cout << buffer2[i] << std::endl;
    };
    file2.close();

    int errorcount=0;//obliczanie błędów
    for (int i = 0; i <= size1; i++) {
        if (buffer1[i] != buffer2[i]) {
            errorcount += 1;
        }
        }
    int BER;

    if (errorcount != 0) //obliczanie BER
    {
        BER = errorcount / size1 * 100;
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