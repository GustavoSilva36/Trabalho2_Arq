#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

class MEM {
    public:
        bitset<16> endereco;
        bitset<32> mem_read_data;

        MEM(bool MemRead, bool MemWrite, BancoMemoria& mb, bitset<32>ALU, bitset<32>mem_write_data);

        void imprimirMEMRead();

        void imprimirMEMWrite();
};

MEM::MEM(bool MemRead, bool MemWrite, BancoMemoria& mb, bitset<32>ALU, bitset<32>mem_write_data){
    // Lê da memória se MemRead estiver ativado
    if (MemRead) {
        endereco = recorte16(ALU, 0);
        mem_read_data = mb.getRegistrador(endereco);
        imprimirMEMRead();
    }

    // Escreve na memória se MemWrite estiver ativado
    if (MemWrite) {
        endereco = recorte16(ALU, 0);
        mb.setRegistrador(endereco, mem_write_data);
        imprimirMEMWrite();
    }
}

void MEM::imprimirMEMRead() {
    // Imprime o valor de MemRead, o endereço de memória e o dado lido
    cout << "MemRead: 1" << endl;
    cout << "Endereco: " << endereco.to_ulong() << endl;
    cout << "ReadData: " << mem_read_data.to_ulong() << endl;
}

void MEM::imprimirMEMWrite() {
    // Imprime o valor de MemWrite, o endereço de memória e o dado escrito
    cout << "MemWrite: 1" << endl;
    cout << "Endereco: " << endereco.to_ulong() << endl;
    cout << " WriteData: " << mem_read_data.to_ulong() << endl;
}