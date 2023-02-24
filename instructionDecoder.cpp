#ifndef _CABECALHO_H
	#include "cabecalho.hpp"
#endif

struct ControlUnit
{
    // inicialização da unidade de controle
    bool jump = false;
    bool branch = false;
    bool mem_read = false;
    bool mem_to_reg = false;
    bool mem_write = false;
    bool alu_src = false;
    bool reg_write = false;
    bool reg_dst = false;
    bool isBNE = false;

    bitset<2> setControlUnit(bitset<6> opcode); // retirei a funct por enquanto
};

bitset<2> ControlUnit::setControlUnit(bitset<6> opcode) // retirei a funct por enquanto
{
    // Instruções tipo R:
    if (opcode == bitset<6>("000000"))
    {
        cout << "Instrucao do Tipo R" << endl;

        // talvez mult e div não estejam sendo contempladas..
        reg_write = true;
        reg_dst = true;
        // retorno pra AlUCtr
        return bitset<2>("10");
    }

    // Instruções tipo branch (beq / bne / bge):
    else if (opcode == bitset<6>("000100") or opcode == bitset<6>("000101") or opcode == bitset<6>("000110"))
    {
        cout << "Instrucao do Tipo Branch" << endl;

        if (opcode == bitset<6>("000101"))
            isBNE = true;
        branch = true;
        // retorno pra AlUCtr
        return bitset<2>("01");
    }
    // Instruções tipo J

    else if (opcode == bitset<6>("000010") or opcode == bitset<6>("000011") or (opcode == bitset<6>("000000"))) // retirei a funct por enquanto
    {
        cout << "Instrucao do Tipo Jump" << endl;

        jump = true;
        return bitset<2>("11");
    }

    // Instrução Load Word
    else if (opcode == bitset<6>("100011"))
    {
        cout << "Instrucao do Tipo Read" << endl;

        mem_read = true;
        mem_to_reg = true;
        alu_src = true;
        reg_write = true;

        return bitset<2>("00");
    }

    else if (opcode == bitset<6>("101011"))
    {
        cout << "Instrucao do Tipo Write" << endl;

        mem_write = true;
        alu_src = true;

        return bitset<2>("00");
    }

    else
    // Instrução tipo I:
    {
        cout << "Instrucao do Tipo Immediate" << endl;

        alu_src = true;
        reg_write = true;

        return bitset<2>("00");
    }
}

// flag bne

//  funct

class ID : public ControlUnit
{
    public:
        bitset<2> retornoAlu;
        bitset<32> value_Rs;
        bitset<32> value_Rt;
        bitset<5> Write_Adrr;

        ID(bitset<6> opcode, bitset<5> rs, bitset<5> rt, bitset<5> rd, BancoRegistradores &BR)
        {
            // falta entender isso aqui, saber oque pegar e como retornar o conteudo do registrador
            retornoAlu = setControlUnit(opcode);
            value_Rs = BR.getRegistrador(rs);
            value_Rt = BR.getRegistrador(rt);
            if (reg_dst)
            {
                Write_Adrr = rd;
            }

            else
            {
                Write_Adrr = rt;
            }
        }
};