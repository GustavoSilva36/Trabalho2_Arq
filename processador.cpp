#include "cabecalho.hpp"
#include <fstream>

int main(){
    ifstream programa("programa.bin", ios::binary);

    if(programa){
        bitset<32> linha;
        programa.read((char *) &linha, sizeof(linha));
        cout << linha << endl;

        bitset<32> n1(65535);
        bitset<32> n2(-10);

        cout << n1 << endl << n2 << endl;
        cout << (n1 & n2) << endl;

        programa.close();
    }

    return 0;
}