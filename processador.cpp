#include "cabecalho.hpp"
#include <fstream>

// struct ID{
//     bitset<1> ALUsrc;

//     ID(bitset<6> opcode, bitset<5> rs, bitset<5> rt){
//         if(opcode[0] == 1)
//             ALUsrc.set(0);
//     }


// };

bitset<32> operator+(bitset<32> &b1, bitset<32> &b2){
	bitset<32> result;
	bool vai1;
	for(int i=0; i<32; i++){
		if(b1[i] and b2[i] and vai1){
			result.set(i);
			vai1 = 1;
		}
		else if((b1[i] and b2[i]) or (b1[i] and vai1) or (b2[i] and vai1)){
			vai1 = 1;
		}
		else if(b1[i] or b2[i] or vai1){
			result.set(i);
			vai1 = 0;
		}
		else{
			vai1 = 0;
		}
	}
	return result;
}

bitset<32> operator-(bitset<32> &b1, bitset<32> &b2){
	b2.flip();
	bitset<32> aux(1);
	b2 = b2 + aux;
	bitset<32> result = b1 + b2;
	return result;
}

bitset<32> operator<(bitset<32> &b1, bitset<32> &b2){
	bitset<32> aux = b1 - b2;
	bitset<32> result;
	if(aux[31] == 0)
		result = bitset<32>(1);
	return result;
}



bitset<16> recorte16(bitset<32> linha, int inicio){
	bitset<16> retorno;
	for(int i=0; i<16; i++)
		retorno.set(i, linha[i+inicio]);

	return retorno;
}

bitset<5> recorte5(bitset<32> linha, int inicio){
	bitset<5> retorno;
	for(int i=0; i<5; i++)
		retorno.set(i, linha[i+inicio]);

	return retorno;
}

bitset<6> recorte6(bitset<32> linha, int inicio){
	bitset<6> retorno;
	for(int i=0; i<6; i++)
		retorno.set(i, linha[i+inicio]);

	return retorno;
}

bool IF(ifstream &programa, unsigned short &pc, bitset<32> &instrucao){
	programa.seekg(pc, ios::beg);
	if(programa.read((char *) &instrucao, sizeof(instrucao))){
		pc += 4;
		return true;
	}
	else
		return false;
}

bitset<32> signalExtension(bitset<32> instrucao){
	bitset<32> extendido;
	for(int i=0; i<16; i++)
		extendido.set(i, instrucao[i]);
	for(int i=16; i<32; i++)
		extendido.set(i, instrucao[15]);
	return extendido;
}

struct EXE{
	// retornos
	bitset<1> ovf;
	bitset<32> result;

	EXE(bitset<32> rs, bitset<32> other, bitset<2> ALUOp, bitset<6> funct){
		bitset<3> ALUCtr = ALUControl(ALUOp, funct);

		if(ALUCtr == bitset<3>("000"))
			result = rs & other;
		else if(ALUCtr == bitset<3>("001"))
			result = rs | other;
		else if(ALUCtr == bitset<3>("010"))
			result = rs + other;
		else if(ALUCtr == bitset<3>("110"))
			result = rs - other;
		else if(ALUCtr == bitset<3>("111"))
			result = rs < other;
	}

	bitset<3> ALUControl(bitset<2> ALUOp, bitset<6> funct){
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
};

int main(){
	ifstream programa("programa.bin", ios::binary);
	BancoRegistradores RB = BancoRegistradores();
	// unsigned short pc = 0;
	bitset<32> instrucao;

	// -------------------------------- teste EXE --------------------------------------
	RB.setRegistrador(bitset<5>(5), bitset<32>(5));
	RB.setRegistrador(bitset<5>(3), bitset<32>(3));

	bitset<32> rs = RB.getRegistrador(bitset<5>(5));
	bitset<32> other = RB.getRegistrador(bitset<5>(-3));
	bitset<2> ALUOp("10");
	bitset<1> ALUSrc;
	bitset<6> funct("101010");
	// -------------------------------- fim teste --------------------------------------

	cout << rs << endl;
	cout << other << endl;

	// while(IF(programa, pc, instrucao)){
	//     cout << instrucao << endl;

		// ID
		if(ALUSrc[0])
			other = signalExtension(instrucao);
		EXE exe = EXE(rs, other, ALUOp, funct);
		cout << exe.result << endl;
	// }

	return 0;
}