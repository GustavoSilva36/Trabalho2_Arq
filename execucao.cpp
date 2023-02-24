#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

class EXE{
	public:
		// retornos
		bool ovf;
		bool Zero;
		bitset<32> endeExtended;
		bitset<32> result;

		// metodos
		EXE(bitset<32> reg1, bitset<32> reg2, bitset<16> enderecoLabel, bitset<6> funct, bitset<2> ALUOp, bool ALUSrc, bool branch, bool bne, bool jump, unsigned short &pc);

		void ALU(bitset<32> reg1, bitset<32> reg2, bitset<3> ALUCtr);

		bitset<3> ALUControl(bitset<2> ALUOp, bitset<6> funct);

		void mostrarValores(){
			cout << "Overflow: " << ovf << endl
				 << "Flag de zero: " << Zero << endl
				 << "Endereco extendido: " << endeExtended << endl
				 << "Resultado das operacoes: " << result << endl
				 << "Resultado inteiro: " << bitsetToInt(result) << endl;
		}

};

EXE::EXE(bitset<32> reg1, bitset<32> reg2, bitset<16> enderecoLabel, bitset<6> funct, bitset<2> ALUOp, bool ALUSrc, bool branch, bool bne, bool jump, unsigned short &pc){
	endeExtended = signalExtension(enderecoLabel);

	if(ALUSrc)
		reg2 = endeExtended;

	bitset<3> ALUCtr = ALUControl(ALUOp, funct);

	ALU(reg1, reg2, ALUCtr);

	if(jump){
		endeExtended <<= 2;
		cout << "Endereco do jump: " << bitsetToInt(endeExtended) << endl;
		pc = endeExtended.to_ulong();
	}

	Zero = !result.any();
	bool branchZero = bne ? !Zero : Zero;
	if(branch and branchZero){
		endeExtended <<= 2;
		cout << "Calculo do branch: " << bitsetToInt(endeExtended) << endl;
		pc = pc + bitsetToInt(endeExtended);
	}

	mostrarValores();
}

void EXE::ALU(bitset<32> reg1, bitset<32> reg2, bitset<3> ALUCtr){
	if(ALUCtr == bitset<3>("000")){
		result = reg1 & reg2;
		cout << "And" << endl;
	}
	else if(ALUCtr == bitset<3>("001")){
		result = reg1 | reg2;
		cout << "Or" << endl;
	}
	else if(ALUCtr == bitset<3>("010")){
		result = reg1 + reg2;
		cout << "Soma" << endl;
		cout << bitsetToInt(reg1) << " + " << bitsetToInt(reg2) << " = " << bitsetToInt(result) << endl;
	}
	else if(ALUCtr == bitset<3>("110")){
		result = reg1 - reg2;
		cout << "Subtracao" << endl;
		cout << reg2 << endl;
		cout << bitsetToInt(reg1) << " - " << bitsetToInt(reg2) << " = " << bitsetToInt(result) << endl;
	}
	else if(ALUCtr == bitset<3>("111")){
		result = reg1 < reg2;
		cout << "Menor que" << endl;
		cout << bitsetToInt(reg1) << " < " << bitsetToInt(reg2) << endl;
	}
}

bitset<3> EXE::ALUControl(bitset<2> ALUOp, bitset<6> funct){
	if(ALUOp == bitset<2>("00")){
		return bitset<3>("010");
	}
	else if(ALUOp == bitset<2>("01")){
		return bitset<3>("110");
	}
	else if(ALUOp == bitset<2>("10")){
		if(funct == bitset<6>("100000"))
			return bitset<3>("010");
		else if(funct == bitset<6>("100010"))
			return bitset<3>("110");
		else if(funct == bitset<6>("100100"))
			return bitset<3>("000");
		else if(funct == bitset<6>("100101"))
			return bitset<3>("001");
		else if(funct == bitset<6>("101010"))
			return bitset<3>("111");
		else
			return bitset<3>("000");
	}
	else{
		return bitset<3>("000");
	}
}