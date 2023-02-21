#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

class BancoRegistradores{
    private:
        bitset<32> *registradores;
    
    public:
        BancoRegistradores(){
            registradores = new bitset<32>[32];
            clear();
        }
        ~BancoRegistradores(){
            delete [] registradores;
        }
        void clear(){
            for(int i=0; i<32; i++)
                registradores[i] = 0;
        }
        bitset<32> getRegistrador(bitset<5> endereco){
            return registradores[endereco.to_ulong()];
        }
        void setRegistrador(bitset<5> endereco, bitset<32> valor){
            registradores[endereco.to_ulong()] = valor;
        }
};