﻿#include <iostream> 
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include <chrono>

int hammingDistance(char n1, char n2);

int main(int argc, char* argv[])
{
    auto start = std::chrono::steady_clock::now(); //początek liczenia czasu

    std::fstream file1; 
    file1.open(argv[1], std::ios::binary | std::ios::in);//wczytanie pliku
    
    if (true != file1.good()) //sprawdzenie czy plik działa
    {
        std::cout << "Nie udało się otworzyć pliku nr 1.";
    }

    file1.seekg(0, std::ios::end); //rozmiar pliku
    int size = (int)file1.tellg();
    file1.seekg(0, std::ios::beg);
    std::cout << size << std::endl;
 
        char * buffer1 = new char[size]; //tablica na plik
        file1.read(buffer1, size); //odczyt danych z pliku
    
    file1.close();//zamkniecie pliku na zakonczenie

    std::fstream file2;
    file2.open(argv[2], std::ios::binary | std::ios::in);

    if (true != file2.good()) //sprawdzenie czy plik działa
    {
        std::cout << "Nie udało się otworzyć pliku nr 2.";
    }

        char * buffer2 = new char[size];
        file2.read(buffer2, size);
    
    file2.close();

    int errorcount = 0;//obliczanie błędów
    int totcount = 0;
    for (int i = 0; i < size; i++)
    {
        errorcount += hammingDistance(buffer1[i], buffer2[i]); //za każdą iteracją dodajemy wartość zwróconą z funkcji
        totcount += 8; //za każdą iteracją porównaliśmy 8 bitów = 1 bajt. char = 1 Bajt
    }

    float BER=0;
    if (errorcount != 0) //obliczanie BER
    {
        BER = ((float)errorcount / size) * 100;
    }
    else
    {
        BER = 0;
    }

    auto end = std::chrono::steady_clock::now(); //koniec liczenia czasu

    std::cout << "Wyniki porowniani:" << std::endl;
    std::cout << "ilosc porownanych bitow = " << totcount << std::endl;
    std::cout << "ilosc roznych bitow = " << errorcount << std::endl;
    std::cout << "BER = " << BER << "%" << std::endl;
    std::cout << "czas obliczen = " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() <<" s." << std::endl;
}

// Function to calculate hamming distance
int hammingDistance(char n1, char n2)
{
    char x = n1 ^ n2;
    char setBits = 0;
    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}