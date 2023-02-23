#include <fstream>
#include "execucao.cpp"
#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

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
	// BancoMemoria MB = BancoMemoria();
	unsigned short pc = 24;
	bitset<32> instrucao;


	IF(programa, pc, instrucao);

	// -------------------------------- teste EXE --------------------------------------
	bitset<5> endereco1 = recorte5(instrucao, 21);
	bitset<5> endereco2 = recorte5(instrucao, 16);
	RB.setRegistrador(endereco1, bitset<32>(5));
	RB.setRegistrador(endereco2, bitset<32>(5));

	bitset<32> reg1 = RB.getRegistrador(endereco1);
	bitset<32> reg2 = RB.getRegistrador(endereco2);
	bitset<16> enderecoLabel = recorte16(instrucao, 0);
	bitset<6> funct = recorte6(instrucao, 0);
	bitset<2> ALUOp("01");
	bool ALUSrc = false;
	bool branch = true;
	bool bne = false;
	bool jump = false;
	// -------------------------------- fim teste --------------------------------------

	cout << instrucao << endl;
	cout << reg1 << endl;
	cout << reg2 << endl;
	
	EXE exe = EXE(reg1, reg2, enderecoLabel, funct, ALUOp, ALUSrc, branch, bne, jump, pc);

	cout << "PC: " << pc << endl;

	return 0;
}