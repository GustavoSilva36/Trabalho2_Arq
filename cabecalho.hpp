#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int registrador; // 4 bytes ou 32 bits
typedef char byte; // 1 byte ou 8 bits
typedef bool bit; // 1 bit (tem opção melhor?)
typedef short bit16; // 16 bits

struct BancoRegistradores{
    registrador *bancoReg;

    BancoRegistradores(){
        bancoReg = new registrador[32];
        clear();
    }
    ~BancoRegistradores(){
        delete [] bancoReg;
    }
    void clear(){
        for(int i=0; i<32; i++)
            bancoReg[i] = 0;
    }
    registrador acessarRegistrador(bit endereco[]){
        unsigned short indice = 0;
        for(int i=0; i<5; i++)
            if(endereco[i])
                indice += pow(2, 4-i);
        cout << indice << endl;
        return bancoReg[indice];
    }
};