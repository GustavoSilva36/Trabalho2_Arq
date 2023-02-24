#include <fstream>
#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif
#include "instructionDecoder.cpp"
#include "execucao.cpp"
#include "memoria.cpp"
#include "writeBack.cpp"


bool IF(ifstream &programa, unsigned short &pc, bitset<32> &instrucao){
	programa.seekg(pc, ios::beg);
	if(programa.read((char *) &instrucao, sizeof(instrucao))){
		pc += 4;
		return true;
	}
	else
		return false;
}

int main(){
	ifstream programa("programa.bin", ios::binary);
	BancoRegistradores RB = BancoRegistradores();
	BancoMemoria MB = BancoMemoria();
	unsigned short pc = 0;
	bitset<32> instrucao;


	while(IF(programa, pc, instrucao)){

		ID id = ID(recorte6(instrucao, 26), recorte5(instrucao, 21), recorte5(instrucao, 16), recorte5(instrucao, 11), RB);
		
		EXE exe = EXE(id.value_Rs, id.value_Rt, recorte16(instrucao, 0), recorte6(instrucao, 0),
					id.retornoAlu, id.alu_src, id.branch, id.isBNE, id.jump, pc);

		MEM mem = MEM(id.mem_read, id.mem_write, MB, exe.result, id.value_Rt);

		WR(id.reg_write, id.mem_to_reg, id.Write_Adrr, RB, mem.mem_read_data, exe.result);

		cout << "PC: " << pc << endl << "---------------------------------------" << endl;

		system("pause");
	}
	
	return 0;
}