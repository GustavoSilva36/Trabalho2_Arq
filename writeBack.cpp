#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

struct WR {    
	WR(bool reg_write, bool mem_to_reg, bitset<5> reg_dst, BancoRegistradores& RB, bitset<32> mem_data, bitset<32>alu_data){
    	// Se deve ocorrer escrita em um registrador
    	if (reg_write) {
            // Se deve ser utilizado o valor lido na memória para escrita no registrador
            if (mem_to_reg) {
                RB.setRegistrador(reg_dst, mem_data);
            } else { // Senão, utiliza o valor gerado pela ALU 
                RB.setRegistrador(reg_dst, alu_data);
        	}
    	}
	}
};