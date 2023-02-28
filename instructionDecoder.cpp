#ifndef _CABECALHO_H
#include "cabecalho.hpp"
#endif

struct ControlUnit
{
    // inicialização da unidade de controle
    bool jump = false;
    bitset<2> branch;
    bool mem_read = false;
    bool mem_to_reg = false;
    bool mem_write = false;
    bool alu_src = false;
    bool reg_write = false;
    bool reg_dst = false;
    bitset<2> alu_op;

    void setControlUnit(bitset<6> opcode); // retirei a funct por enquanto
    void imprimirID()
    {
        cout << "jump: " << jump << endl
             << "branch: " << branch << endl
             << "mem_read: " << mem_read << endl
             << "mem_to_reg: " << mem_to_reg << endl
             << "mem_write: " << mem_write << endl
             << "alu_src: " << alu_src << endl
             << "reg_write: " << reg_write << endl
             << "reg_dst: " << reg_dst << endl
             << "alu_op: " << alu_op << endl;
    }
};

void ControlUnit::setControlUnit(bitset<6> opcode) // retirei a funct por enquanto
{
    // Instruções tipo R:
    if (opcode == bitset<6>("000000"))
    {
        // talvez mult e div não estejam sendo contempladas..
        reg_write = true;
        reg_dst = true;
        // retorno pra AlUCtr
        alu_op = bitset<2>("10");
        imprimirID();
    }

    // Instruções tipo branch (beq / bne / bge):
    else if (opcode == bitset<6>("000100") or opcode == bitset<6>("000101") or opcode == bitset<6>("000110"))
    {
        if (opcode == bitset<6>("000101")) // bne
            branch = bitset<2>("10");

        else if (opcode == bitset<6>("000110")) // bge
            branch = bitset<2>("11");
        else
        {
            branch = bitset<2>("01");
        }

        alu_op = bitset<2>("01");

        imprimirID();
    }
    // Instruções tipo J

    else if (opcode == bitset<6>("000010") or opcode == bitset<6>("000011") or (opcode == bitset<6>("000000"))) // retirei a funct por enquanto
    {
        jump = true;
        imprimirID();
    }

    // Instrução Load Word
    else if (opcode == bitset<6>("100011"))
    {
        mem_read = true;
        mem_to_reg = true;
        alu_src = true;
        reg_write = true;

        alu_op = bitset<2>("00");
        imprimirID();
    }

    else if (opcode == bitset<6>("101011")) // Instrução Save Word
    {
        mem_write = true;
        alu_src = true;

        alu_op = bitset<2>("00");
        imprimirID();
    }

    else
    // Instrução tipo I:
    {
        alu_src = true;
        reg_write = true;

        alu_op = bitset<2>("00");
        imprimirID();
    }
}

// flag bne

//  funct

class ID : public ControlUnit
{
public:
    bitset<32> value_Rs;
    bitset<32> value_Rt;
    bitset<5> Write_Adrr;

    ID(bitset<6> opcode, bitset<5> rs, bitset<5> rt, bitset<5> rd, BancoRegistradores &BR)
    {
        // falta entender isso aqui, saber oque pegar e como retornar o conteudo do registrador
        setControlUnit(opcode);
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