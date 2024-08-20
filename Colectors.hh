#ifndef __COLECTORS_HH__
#define __COLECTORS_HH__
#include <string>
#include <map>
#include <iostream>
#include "bst.hh"
using std::cout;
using std::endl;
using std::string;
using std::map;
map<string,int>* registerColector()
{
  map<string,int>* registers= new map<string,int>;
  (*registers)["zero"]=0;
  (*registers)["ra"]=1;
  (*registers)["sp"]=2;
  (*registers)["gp"]=3;
  (*registers)["tp"]=4;
  (*registers)["t0"]=5;
  (*registers)["t1"]=6;
  (*registers)["t2"]=7;
  (*registers)["s0"]=8;
  (*registers)["s1"]=9;
  (*registers)["a0"]=10;
  (*registers)["a1"]=11;
  (*registers)["a2"]=12;
  (*registers)["a3"]=13;
  (*registers)["a4"]=14;
  (*registers)["a5"]=15;
  (*registers)["a6"]=16;
  (*registers)["a7"]=17;
  (*registers)["s2"]=18;
  (*registers)["s3"]=19;
  (*registers)["s4"]=20;
  (*registers)["s5"]=21;
  (*registers)["s6"]=22;
  (*registers)["s7"]=23;
  (*registers)["s8"]=24;
  (*registers)["s9"]=25;
  (*registers)["s10"]=26;
  (*registers)["s11"]=27;
  (*registers)["t3"]=28;
  (*registers)["t4"]=29;
  (*registers)["t5"]=30;
  (*registers)["t6"]=31;
  (*registers)["x0"]=0;
  (*registers)["x1"]=1;
  (*registers)["x2"]=2;
  (*registers)["x3"]=3;
  (*registers)["x4"]=4;
  (*registers)["x5"]=5;
  (*registers)["x6"]=6;
  (*registers)["x7"]=7;
  (*registers)["x8"]=8;
  (*registers)["x9"]=9;
  (*registers)["x10"]=10;
  (*registers)["x11"]=11;
  (*registers)["x12"]=12;
  (*registers)["x13"]=13;
  (*registers)["x14"]=14;
  (*registers)["x15"]=15;
  (*registers)["x16"]=16;
  (*registers)["x17"]=17;
  (*registers)["x18"]=18;
  (*registers)["x19"]=19;
  (*registers)["x20"]=20;
  (*registers)["x21"]=21;
  (*registers)["x22"]=22;
  (*registers)["x23"]=23;
  (*registers)["x24"]=24;
  (*registers)["x25"]=25;
  (*registers)["x26"]=26;
  (*registers)["x27"]=27;
  (*registers)["x28"]=28;
  (*registers)["x29"]=29;
  (*registers)["x30"]=30;
  (*registers)["x31"]=31;
  return registers;
}
void fun3Colector(BST<string>& arbol, int function3Type)
{
  if(function3Type == 0)
  {
    arbol.insert("add");
    arbol.insert("sub");
    arbol.insert("addi");
    arbol.insert("lb");
    arbol.insert("sb");
    arbol.insert("beq");
    arbol.insert("jalr");
    arbol.insert("ecall");
    arbol.insert("ebreak");
    arbol.insert("mul");
  }
  else if(function3Type == 1)
  {
    arbol.insert("sll");
    arbol.insert("slli");
    arbol.insert("lh");
    arbol.insert("sh");
    arbol.insert("bne");
    arbol.insert("mulh");
  }
  else if(function3Type == 2)
  {
    arbol.insert("slt");
    arbol.insert("slti");
    arbol.insert("lw");
    arbol.insert("sw");
    arbol.insert("mlsu");
  }
  else if(function3Type == 3)
  {
    arbol.insert("sltu");
    arbol.insert("sltiu");
    arbol.insert("mulu");

  }
  else if(function3Type == 4)
  {
    arbol.insert("xor");
    arbol.insert("xori");
    arbol.insert("lbu");
    arbol.insert("blt");
    arbol.insert("div");
  }
  else if(function3Type == 5)
  {
    arbol.insert("srl");
    arbol.insert("sra");
    arbol.insert("srli");
    arbol.insert("srai");
    arbol.insert("lhu");
    arbol.insert("bge");
    arbol.insert("divu");
  }
  else if(function3Type == 6)
  {
    arbol.insert("or");
    arbol.insert("ori");
    arbol.insert("bltu");
    arbol.insert("rem");
  }
  else if(function3Type == 7)
  {
    arbol.insert("and");
    arbol.insert("andi");
    arbol.insert("bgeu");
    arbol.insert("remu");
  }  
}
BST<string> InstructionsColector(const string& type)
{
  BST<string> arbol;
  if(type == "r")
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
  else if(type == "i")
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
  else if(type == "j")
  {
    arbol.insert("jal");
  }
  else if(type == "s")
  {
    arbol.insert("sb");
    arbol.insert("sh");
    arbol.insert("sw");
  }
  else if(type == "u")
  {
    arbol.insert("lui");
    arbol.insert("auipc");
  }
  else if(type == "b")
  {
    arbol.insert("beq");
    arbol.insert("bne");
    arbol.insert("blt");
    arbol.insert("bge");
    arbol.insert("bltu");
    arbol.insert("bgeu");
  }
  else if(type == "p")
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