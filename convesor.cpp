#include "cabecalho.hpp"
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

map<string, string> opcodeMap = {
	{"add" , "00000000000000000000000000100000"},
	{"sub" , "00000000000000000000000000100010"},
	{"addi", "00100000000000000000000000000000"},
	{"and" , "00000000000000000000000000100100"},
	{"or"  , "00000000000000000000000000100101"},
	{"nor" , "00000000000000000000000000100111"},
	{"mult", "00000000000000000000000000011000"},
	{"sll" , "00000000000000000000000000000000"},
	{"srl" , "00000000000000000000000000000010"},
	//{"mul" , "000000"}, // arrumar
	{"div" , "00000000000000000000000000011010"},
	{"lw"  , "10001100000000000000000000000000"},
	{"sw"  , "10101100000000000000000000000000"},
	{"beq" , "00010000000000000000000000000000"},
	{"bne" , "00010100000000000000000000000000"},
	//{"bge" , "000110"}, // arrumar
	{"slt" , "00000000000000000000000000101010"},
	{"j"   , "00001000000000000000000000000000"},
	{"jal" , "00001100000000000000000000000000"},
	{"jr"  , "00000000000000000000000000001000"}
};

map<string, string> tipoInstrucaoMap = {
	// aritmetica logica
	{"add" , "AL"},
	{"sub" , "AL"},
	{"and" , "AL"},
	{"or"  , "AL"},
	{"nor" , "AL"},
	{"mult", "AL"},
	{"sll" , "AL"},
	{"srl" , "AL"},
	{"div" , "AL"},
	{"slt" , "AL"},
	{"mul" , "AL"}, // arrumar
	// imediata
	{"addi", "IME"},
	// memoria
	{"lw"  , "MEM"},
	{"sw"  , "MEM"},
	// desvio condicional
	{"beq" , "DC"},
	{"bne" , "DC"},
	{"bge" , "DC"}, // arrumar
	// desvio incondicional
	{"j"   , "DI"},
	{"jal" , "DI"},
	// desvio incondicional com registrador
	{"jr"  , "DIR"}
};


void tipoAritmeticaLogica(bitset<32> &linhaB, string linha){
	size_t separador = linha.find(',');
	int reg = stoi(linha.substr(1, separador-1));
	bitset<32> rd(reg);
	linha = linha.substr(separador+1);

	separador = linha.find(',');
	reg = stoi(linha.substr(1, separador-1));
	bitset<32> rs(reg);
	linha = linha.substr(separador+1);

	reg = stoi(linha.substr(1)); // add, sub, ...
	bitset<32> rt(reg);

	rs <<= 21;
	rt <<= 16;
	rd <<= 11;
	linhaB = linhaB | rs;
	linhaB = linhaB | rt;
	linhaB = linhaB | rd;
	cout << linhaB << endl;
}

void tipoImediata(bitset<32> &linhaB, string linha){ // addi
	size_t separador = linha.find(',');
	int reg = stoi(linha.substr(1, separador-1));
	bitset<32> rt(reg);
	linha = linha.substr(separador+1);

	separador = linha.find(',');
	reg = stoi(linha.substr(1, separador-1));
	bitset<32> rs(reg);
	linha = linha.substr(separador+1);

	reg = stoi(linha); // add, sub, ...
	bitset<32> imm(reg);

	rs <<= 21;
	rt <<= 16;
	for(int i=16; i<32; i++)
		imm.reset(i);
	linhaB = linhaB | rs;
	linhaB = linhaB | rt;
	linhaB = linhaB | imm;
	cout << linhaB << endl;
}

void tipoMemoria(bitset<32> &linhaB, string linha){ // sw, lw
	size_t separador = linha.find(',');
	int reg = stoi(linha.substr(1, separador-1));
	bitset<32> rt(reg);
	linha = linha.substr(separador+1);

	separador = linha.find('(');
	reg = stoi(linha.substr(0, separador));
	bitset<32> offset(reg);
	linha = linha.substr(separador+1);

	reg = stoi(linha.substr(1, linha.find(')')-1)); // add, sub, ...
	bitset<32> rs(reg);
	
	rs <<= 21;
	rt <<= 16;
	for(int i=16; i<32; i++)
		offset.reset(i);
	linhaB = linhaB | rs;
	linhaB = linhaB | rt;
	linhaB = linhaB | offset;

	cout << linhaB << endl;
}

// void tipoDesvioCondicional(bitset<32> &linhaB, string linha){ // beq, bne, bge
	
//     cout << linhaB << endl;
// }

// void tipoDesvioIncondicional(bitset<32> &linhaB, string linha){ // j, jr
	
//     cout << linhaB << endl;
// }

bool converter(){
	ifstream txt("programa.txt");
	ofstream bin("programa.bin", ios::binary);

	if(txt and bin){
		string linha;

		while(getline(txt, linha)){
			cout << linha << endl;

			size_t separador = linha.find(' ');
			string funcao = linha.substr(0, separador); // add, sub, ...
			linha = linha.substr(separador+1);
			linha.erase(remove(linha.begin(), linha.end(), ' '), linha.end());

			string aux = opcodeMap[funcao];
			bitset<32> linhaB(aux);

			if(tipoInstrucaoMap[funcao] == "AL")
				tipoAritmeticaLogica(linhaB, linha);
			else if(tipoInstrucaoMap[funcao] == "IME")
				tipoImediata(linhaB, linha);
			else if(tipoInstrucaoMap[funcao] == "MEM")
				tipoMemoria(linhaB, linha);
			// else if(tipoInstrucaoMap[funcao] == "DC")
			//     tipoDesvioCondicional(linhaB, linha);
			// else if(tipoInstrucaoMap[funcao] == "DI")
			//     tipoDesvioIncondicional(linhaB, linha);
			else 
				cout << "funcao nao reconhecida" << endl;
			
			// bin.write((const char *) &linhaB, sizeof(bitset<32>));
		}

		txt.close();
		bin.close();
		return true;
	}
	else
		return false;
}

int main(){
	
	if(converter())
		cout << "Arquivo decodificado" << endl;
	else
		cout << "Erro ao codificar o arquivo" << endl;

	return 0;
}