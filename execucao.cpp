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
		EXE(bitset<32> reg1, bitset<32> reg2, bitset<16> enderecoLabel, bitset<6> funct, bitset<5> shamt, bitset<2> ALUOp, bool ALUSrc, bitset<2> branch, bool jump, unsigned short &pc);

		void ALU(bitset<32> reg1, bitset<32> reg2, bitset<5> shamt, bitset<4> ALUCtr);

		bitset<4> ALUControl(bitset<2> ALUOp, bitset<6> funct);

		void mostrarValores(){
			cout << "Overflow: " << ovf << endl
				 << "Flag de zero: " << Zero << endl
				 << "Endereco extendido: " << endeExtended << endl
				 << "Resultado das operacoes: " << result << endl
				 << "Resultado inteiro: " << bitsetToInt(result) << endl;
		}

};

EXE::EXE(bitset<32> reg1, bitset<32> reg2, bitset<16> enderecoLabel, bitset<6> funct, bitset<5> shamt, bitset<2> ALUOp, bool ALUSrc, bitset<2> branch, bool jump, unsigned short &pc){
	endeExtended = signalExtension(enderecoLabel);

	if(ALUSrc)
		reg2 = endeExtended;

	bitset<4> ALUCtr = ALUControl(ALUOp, funct);

	ALU(reg1, reg2, shamt, ALUCtr);

	if(jump){
		endeExtended <<= 2;
		cout << "Endereco do jump: " << bitsetToInt(endeExtended) << endl;
		pc = endeExtended.to_ulong();
	}

	Zero = !result.any();
	if((branch == bitset<2>("01") and Zero) or (branch == bitset<2>("10") and !Zero)){
		endeExtended <<= 2;
		cout << "Calculo do branch: " << bitsetToInt(endeExtended) << endl;
		pc = pc + bitsetToInt(endeExtended);
	}
	else if(branch == bitset<2>("11")){
		result = reg1 < reg2;
		if(!result.any()){
			endeExtended <<= 2;
			cout << "Calculo do branch greater equal: " << bitsetToInt(endeExtended) << endl;
			pc = pc + bitsetToInt(endeExtended);
		}
	}

	mostrarValores();
}

void EXE::ALU(bitset<32> reg1, bitset<32> reg2, bitset<5> shamt, bitset<4> ALUCtr){
	if(ALUCtr == bitset<4>("0000")){ // and
		result = reg1 & reg2;
		cout << "And" << endl;
	}
	else if(ALUCtr == bitset<4>("0001")){ // or
		result = reg1 | reg2;
		cout << "Or" << endl;
	}
	else if(ALUCtr == bitset<4>("0010")){ // add
		result = reg1 + reg2;
		cout << "Soma" << endl;
		cout << bitsetToInt(reg1) << " + " << bitsetToInt(reg2) << " = " << bitsetToInt(result) << endl;
	}
	else if(ALUCtr == bitset<4>("0011")){ // sub
		result = reg1 - reg2;
		cout << "Subtracao" << endl;
		cout << reg2 << endl;
		cout << bitsetToInt(reg1) << " - " << bitsetToInt(reg2) << " = " << bitsetToInt(result) << endl;
	}
	else if(ALUCtr == bitset<4>("0100")){ // slt
		result = reg1 < reg2;
		cout << "Menor que" << endl;
		cout << bitsetToInt(reg1) << " < " << bitsetToInt(reg2) << endl;
	}
	else if(ALUCtr == bitset<4>("0101")){ // nor
		result = reg1 | reg2;
		result.flip();
		cout << "Nor" << endl;
		cout << bitsetToInt(reg1) << " nor " << bitsetToInt(reg2) << endl;
	}
	else if(ALUCtr == bitset<4>("0110")){ // sll
		cout << "Shift Left Logical" << endl;
		cout << bitsetToInt(reg2) << " << " << bitsetToInt(shamt) << endl;
		reg2 <<= bitsetToInt(shamt);
		result = reg2;
	}
	else if(ALUCtr == bitset<4>("0111")){ // srl
		cout << "Shift Right Logical" << endl;
		cout << bitsetToInt(reg2) << " >> " << bitsetToInt(shamt) << endl;
		reg2 >>= bitsetToInt(shamt);
		result = reg2;
	}
	else if(ALUCtr == bitset<4>("1000")){ // mul
		result = reg1 * reg2;
		cout << "Multiplicacao" << endl;
		cout << bitsetToInt(reg1) << " * " << bitsetToInt(reg2) << endl;
	}
	else if(ALUCtr == bitset<4>("1001")){ // div
		result = reg1 / reg2;
		cout << "Divisao Inteira" << endl;
		cout << bitsetToInt(reg1) << " / " << bitsetToInt(reg2) << endl;
	}
}

bitset<4> EXE::ALUControl(bitset<2> ALUOp, bitset<6> funct){
	if(ALUOp == bitset<2>("00")){
		return bitset<4>("0010");
	}
	else if(ALUOp == bitset<2>("01")){
		return bitset<4>("0011");
	}
	else if(ALUOp == bitset<2>("10")){
		if(funct == bitset<6>("100100")) // and
			return bitset<4>("0000");
		else if(funct == bitset<6>("100101")) // or
			return bitset<4>("0001");
		else if(funct == bitset<6>("100000")) // soma
			return bitset<4>("0010");
		else if(funct == bitset<6>("100010")) // subtracao
			return bitset<4>("0011");
		else if(funct == bitset<6>("101010")) // slt
			return bitset<4>("0100");
		else if(funct == bitset<6>("100111")) // nor
			return bitset<4>("0101");
		else if(funct == bitset<6>("000000")) // sll
			return bitset<4>("0110");
		else if(funct == bitset<6>("000010")) // srl
			return bitset<4>("0111");
		else if(funct == bitset<6>("011000")) // mul
			return bitset<4>("1000");
		else if(funct == bitset<6>("011010")) // div
			return bitset<4>("1001");
		else
			return bitset<4>("0000");
	}
	else{
		return bitset<4>("0000");
	}
}