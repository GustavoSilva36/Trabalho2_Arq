#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

struct WR {    
    WR(bool reg_write, bool mem_to_reg, bitset<5> reg_dst, BancoRegistradores& RB, bitset<32> mem_data, bitset<32> alu_data){
        // Se deve ocorrer escrita em um registrador
        if (reg_write) {
            // Se deve ser utilizado o valor lido na memória para escrita no registrador
            if (mem_to_reg) {
                RB.setRegistrador(reg_dst, mem_data);
                cout << "Valor do sinal de memoria para registrador (Mem2Reg): 1" << endl;
            } else { // Senão, utiliza o valor gerado pela ALU 
                RB.setRegistrador(reg_dst, alu_data);
                cout << "Valor do sinal de memoria para registrador (Mem2Reg): 0" << endl;
            }
            cout << "Endereco do registrador de destino (RegDst): " << reg_dst.to_ulong() << endl;
            cout << "Valor do dado a ser escrito no registrador (Dado): " << bitsetToInt(RB.getRegistrador(reg_dst)) << endl;
        }
    }
};