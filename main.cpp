#include <iostream> 
#include <fstream>
#include <sys/stat.h>
#include <cstdlib>
#include <chrono>

int hammingDistance(char n1, char n2);

int main(int argc, char* argv[])
{
    auto start = std::chrono::steady_clock::now(); //początek liczenia czasu

    //UWAGA. Nie sprawdza Pan czy argv[1] i argv[2] zostaly przekazane

    std::fstream file1; //zmienna (tzw handler) do pliku1
    file1.open(argv[1], std::ios::binary | std::ios::in); //wczytanie pliku - korzystamy z funkcji open
    if (true != file1.good())
    {
        std::cout << "Nie udało się otworzyć pliku. Pojawiała się Panu wartość (-1)";
    }
    
    file1.seekg(0, std::ios::end); 
    int size1 = (int)file1.tellg(); //tutaj dodajemy cast aby usunac warning. wiemy co robimy rozmiar < max int
    file1.seekg(0, std::ios::beg);
    std::cout << size1 << std::endl;
 
    // BŁĄD (file1.read potrzebuje bajtow) 
    //size1 = size1 * 8; //zmiana rozmiaru z bajtów na bity

    //BLAD inny nawias -> new char[size1] 
    char* buffer1 = new char[size1]; //tablica na plik
    file1.read(buffer1, size1); //odczyt danych z pliku
    
    file1.close();//zamkniecie pliku na zakonczenie

    std::fstream file2;
    file2.open(argv[2], std::ios::binary | std::ios::in);

// UWAGA - dla uproszczenia zakladamy ze rozmiar file1 = rozmiar file2
// Tylko taki przypadek będziemy rozpatrywać w zadaniu 
// 
//    file2.seekg(0, std::ios::end);
//   long size2 = file2.tellg();
//    file2.seekg(0, std::ios::beg);
//    std::cout << size2 << std::endl;
//        size2 = size2 * 8;
    
    //BLAD inny nawias -> new char[size1] 
    char* buffer2 = new char[size1];
    file2.read(buffer2, size1);
    
    file2.close();

    //UWAGA - nie możemy porównania wykonać na bajtach (buffer1[i] != buffer2[i]
    // na zajęciach omawialiśmy funkcję hammingDistance
    
    int errorcount = 0;//obliczanie błędów
    int totcount = 0;
    for (int iter = 0; iter < size1; iter ++)
    {
        errorcount += hammingDistance(buffer1[iter], buffer2[iter]); //za każdą iteracją dodajemy wartość zwróconą z funkcji
        totcount += 8; //za każdą iteracją porównaliśmy 8 bitów = 1 bajt. char = 1 Bajt
    }

/*
    for (int i = 0; i <= size1; i++) {
        if (buffer1[i] != buffer2[i]) {
            errorcount += 1;
        }
        }
*/

    //int BER=0; //BLAD- BER nie może być int. Bedzie zawierał wynik dzielenia 
    float BER = 0;

    if (errorcount != 0) //obliczanie BER
    {
        BER = ((float)errorcount / size1) * 100; //zwiekszamy prezycję errorcount do float dla poprawnych obliczeń
    }
    else
    {
        BER = 0;
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "Wyniki porowniani:" << std::endl;
    std::cout << "ilosc porownanych bitow = " << totcount << std::endl; // zmieniłem zmienna na totcount
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