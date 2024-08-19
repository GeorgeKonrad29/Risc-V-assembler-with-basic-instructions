#ifndef __COLECTORS_HH__
#define __COLECTORS_HH__
#include <string>
#include <iostream>
#include "bst.hh"
using std::cout;
using std::endl;
using std::string;
BST<string> InstructionsColector(const string& tipo)
{
  BST<string> arbol;
  if(tipo == "r")
  {
    arbol.insert("add");
    arbol.insert("sub");
    arbol.insert("and");
    arbol.insert("or");
    arbol.insert("xor");
    arbol.insert("sra");
    arbol.insert("slt");
    arbol.insert("sll");
    arbol.insert("srl");
    arbol.insert("sltu");
    arbol.insert("mul");
    arbol.insert("mulh");
    arbol.insert("mulsu");
    arbol.insert("mulu");
    arbol.insert("div");
    arbol.insert("divu");
    arbol.insert("rem");
    arbol.insert("remu");

  }
  else if(tipo == "i")
  {
    arbol.insert("addi");
    arbol.insert("andi");
    arbol.insert("ori");
    arbol.insert("xori");
    arbol.insert("slti");
    arbol.insert("slli");
    arbol.insert("srli");
    arbol.insert("sltiu");
    arbol.insert("srai");
    arbol.insert("lb");
    arbol.insert("lh");
    arbol.insert("lw");
    arbol.insert("lbu");
    arbol.insert("lhu");
    arbol.insert("jalr");
    arbol.insert("ecall");
    arbol.insert("ebreak");
  }
  else if(tipo == "j")
  {
    arbol.insert("jal");
  }
  else if(tipo == "s")
  {
    arbol.insert("sb");
    arbol.insert("sh");
    arbol.insert("sw");
  }
  else if(tipo == "u")
  {
    arbol.insert("lui");
    arbol.insert("auipc");
  }
  else if(tipo == "b")
  {
    arbol.insert("beq");
    arbol.insert("bne");
    arbol.insert("blt");
    arbol.insert("bge");
    arbol.insert("bltu");
    arbol.insert("bgeu");
  }
  else if(tipo == "p")
  {
    arbol.insert("la");
    arbol.insert("lb");
    arbol.insert("lh");
    arbol.insert("lw");
    arbol.insert("sb");
    arbol.insert("sh");
    arbol.insert("sw");
    arbol.insert("nop");
    arbol.insert("li");
    arbol.insert("mv");
    arbol.insert("not");
    arbol.insert("neg");
    arbol.insert("seqz");
    arbol.insert("snez");
    arbol.insert("sltz");
    arbol.insert("sgtz");
    arbol.insert("beqz");
    arbol.insert("bnez");
    arbol.insert("blez");
    arbol.insert("bgez");
    arbol.insert("bltz");
    arbol.insert("bgtz");
    arbol.insert("bgt");
    arbol.insert("ble");
    arbol.insert("bgtu");
    arbol.insert("bleu");
    arbol.insert("j");
    arbol.insert("jr");
    arbol.insert("jal");
    arbol.insert("jalr");
    arbol.insert("ret");
    arbol.insert("call");
    arbol.insert("tail");
  }
  else
  {
    cout<<"Error, tipo de instruccion no encontrado"<<endl;
  }
  return arbol;
}
#endif