﻿#include <iostream> 
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

    struct stat results1{};
    std::ifstream file1("file1.bin", std::ios::binary | std::ios::in);//wczytanie pliku
    /*if (stat("file1.bin", &results1) == 0) //rozmiar plików
    {
        std::cout << results1.st_size << std::endl;//test danych rozmiaru
    }
    else
    {
        std::cout << "file 1 error size" << std::endl;
    }
    */
    file1.seekg(0, std::ios::end); //rozmiar pliku 2
    int size1 = file1.tellg();
    file1.seekg(0, std::ios::beg);
    std::cout << size1 << std::endl;
        //int size1 = results1.st_size; //rozmiar do inta
        char* buffer1 = new char(size1); //tablica na plik
        file1.read(buffer1, size1); //odczyt danych z pliku
    
    file1.close();//zamkniecie pliku na zakonczenie

    struct stat results2{};
    std::ifstream file2("file2.bin", std::ios::binary | std::ios::in);
    /*if (stat("file2.bin", &results2) == 0)
    {
        std::cout << results2.st_size << std::endl;
    }
    else
    {
        std::cout << "file 2 error size" << std::endl;
    }
    */
    file2.seekg(0, std::ios::end);
    long size2 = file2.tellg();
    file2.seekg(0, std::ios::beg);
    std::cout << size2 << std::endl;
        //int size2 = results2.st_size;
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