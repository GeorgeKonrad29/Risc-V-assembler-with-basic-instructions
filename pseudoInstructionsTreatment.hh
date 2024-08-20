#ifndef __PSEUDOINSTRUCTIONSTREATMENT_HH__
#define __PSEUDOINSTRUCTIONSTREATMENT_HH__
#include <iostream>
#include <string>
#include "Vector.hh"
#include "InstructionsGeneration.hh"
#include "fileUsage.hh"
void laGeneration(const Vector<string>& codeline)
{
  Vector<string>* auipcPart = new Vector<string>;
  Vector<string>* addiPart = new Vector<string>;
  auipcPart->push_back("auipc");
  auipcPart->push_back(codeline.at(1));
  auipcPart->push_back(codeline.at(2));
  addiPart->push_back("addi");
  addiPart->push_back(codeline.at(1));
  addiPart->push_back(codeline.at(1));
  addiPart->push_back(codeline.at(2));
  Stack<int>* BinarioAUIPC = UtypeGeneration(*auipcPart);
  Stack<int>* BinarioADDI = ItypeGeneration(*addiPart);
  writeToFile(BinarioAUIPC);
  writeToFile(BinarioADDI);
}
void lpseudoInstructionsGeneration(const Vector<string>& codeline)
{
  Vector<string>* auipcPart = new Vector<string>;
  Vector<string>* lPart = new Vector<string>;
  auipcPart->push_back("auipc");
  auipcPart->push_back(codeline.at(1));
  auipcPart->push_back(codeline.at(2));
  lPart->push_back(codeline.at(0));
  lPart->push_back(codeline.at(1));
  lPart->push_back(codeline.at(2)+'('+codeline.at(1)+')');
  Stack<int>* BinarioAUIPC = UtypeGeneration(*auipcPart);
  Stack<int>* Binariol = ItypeGeneration(*lPart);
  writeToFile(BinarioAUIPC);
  writeToFile(Binariol);
}
void spseudoInstructionsGeneration(const Vector<string>& codeline)
{
  Vector<string>* auipcPart = new Vector<string>;
  Vector<string>* sPart = new Vector<string>;
  auipcPart->push_back("auipc");
  auipcPart->push_back(codeline.at(3));
  auipcPart->push_back(codeline.at(2));
  sPart->push_back(codeline.at(0));
  sPart->push_back(codeline.at(1));
  sPart->push_back(codeline.at(2)+'('+codeline.at(3)+')');
  Stack<int>* BinarioAUIPC = UtypeGeneration(*auipcPart);
  Stack<int>* BinarioS = StypeGeneration(*sPart);
  writeToFile(BinarioAUIPC);
  writeToFile(BinarioS);
}
void nopGeneration()
{
  Vector<string>* nop = new Vector<string>;
  nop->push_back("addi");
  nop->push_back("x0");
  nop->push_back("x0");
  nop->push_back("0");
  Stack<int>* BinarioNop = ItypeGeneration(*nop);
  writeToFile(BinarioNop);
}
void liGeneration(const Vector<string>& codeline)
{
  Vector<string>* liPart = new Vector<string>;
  liPart->push_back("addi");
  liPart->push_back(codeline.at(1));
  liPart->push_back("x0");
  liPart->push_back(codeline.at(2));
  Stack<int>* BinarioLi = ItypeGeneration(*liPart);
  writeToFile(BinarioLi);
}
void mvGeneration(const Vector<string>& codeline)
{
  Vector<string>* mvPart = new Vector<string>;
  mvPart->push_back("addi");
  mvPart->push_back(codeline.at(1));
  mvPart->push_back(codeline.at(2));
  mvPart->push_back("0");
  Stack<int>* BinarioMv = ItypeGeneration(*mvPart);
  writeToFile(BinarioMv);
}  
void notGeneration(const Vector<string>& codeline)
{
  Vector<string>* notPart = new Vector<string>;
  notPart->push_back("xori");
  notPart->push_back(codeline.at(1));
  notPart->push_back(codeline.at(2));
  notPart->push_back("-1");
  Stack<int>* BinarioNot = ItypeGeneration(*notPart);
  writeToFile(BinarioNot);
}
void negGeneration(const Vector<string>& codeline)
{
  Vector<string>* negPart = new Vector<string>;
  negPart->push_back("sub");
  negPart->push_back(codeline.at(1));
  negPart->push_back("x0");
  negPart->push_back(codeline.at(2));
  Stack<int>* BinarioNeg = RtypeGeneration(*negPart);
  writeToFile(BinarioNeg);
}
void seqzGeneration(const Vector<string>& codeline)
{
  Vector<string>* seqzPart = new Vector<string>;
  seqzPart->push_back("sltiu");
  seqzPart->push_back(codeline.at(1));
  seqzPart->push_back(codeline.at(2));
  seqzPart->push_back("1");
  Stack<int>* BinarioSeqz = ItypeGeneration(*seqzPart);
  writeToFile(BinarioSeqz);
}
void snezGeneration(const Vector<string>& codeline)
{
  Vector<string>* snezPart = new Vector<string>;
  snezPart->push_back("sltu");
  snezPart->push_back(codeline.at(1));
  snezPart->push_back("x0");
  snezPart->push_back(codeline.at(2));
  Stack<int>* BinarioSnez = RtypeGeneration(*snezPart);
  writeToFile(BinarioSnez);
}
void sltzGeneration(const Vector<string>& codeline)
{
  Vector<string>* sltzPart = new Vector<string>;
  sltzPart->push_back("slt");
  sltzPart->push_back(codeline.at(1));
  sltzPart->push_back(codeline.at(2));
  sltzPart->push_back("x0");
  Stack<int>* BinarioSltz = RtypeGeneration(*sltzPart);
  writeToFile(BinarioSltz);
}
void sgtzGeneration(const Vector<string>& codeline)
{
  Vector<string>* sgtzPart = new Vector<string>;
  sgtzPart->push_back("slt");
  sgtzPart->push_back(codeline.at(1));
  sgtzPart->push_back("x0");
  sgtzPart->push_back(codeline.at(2));
  Stack<int>* BinarioSgtz = RtypeGeneration(*sgtzPart);
  writeToFile(BinarioSgtz);
}
void beqzGeneration(const Vector<string>& codeline)
{
  Vector<string>* beqzPart = new Vector<string>;
  beqzPart->push_back("beq");
  beqzPart->push_back(codeline.at(1));
  beqzPart->push_back("x0");
  beqzPart->push_back(codeline.at(2));
  int offset;
  offset = stoi(beqzPart->at(3));
  Stack<int>* BinarioBeqz = BtypeGeneration(*beqzPart, offset);
  writeToFile(BinarioBeqz);
}
void bnezGeneration(const Vector<string>& codeline)
{
  Vector<string>* bnezPart = new Vector<string>;
  bnezPart->push_back("bne");
  bnezPart->push_back(codeline.at(1));
  bnezPart->push_back("x0");
  bnezPart->push_back(codeline.at(2));
  int offset;
  offset = stoi(bnezPart->at(3));
  Stack<int>* BinarioBnez = BtypeGeneration(*bnezPart, offset);
  writeToFile(BinarioBnez);
}
void blezGeneration(const Vector<string>& codeline)
{
  Vector<string>* blezPart = new Vector<string>;
  blezPart->push_back("bge");
  blezPart->push_back("x0");
  blezPart->push_back(codeline.at(1));
  blezPart->push_back(codeline.at(2));
  int offset;
  offset = stoi(blezPart->at(3));
  Stack<int>* BinarioBlez = BtypeGeneration(*blezPart, offset);
  writeToFile(BinarioBlez);
}
void bgezGeneration(const Vector<string>& codeline)
{
  Vector<string>* bgezPart = new Vector<string>;
  bgezPart->push_back("bge");
  bgezPart->push_back(codeline.at(1));
  bgezPart->push_back("x0");
  bgezPart->push_back(codeline.at(2));
  int offset;
  offset = stoi(bgezPart->at(3));
  Stack<int>* BinarioBgez = BtypeGeneration(*bgezPart, offset);
  writeToFile(BinarioBgez);
}
void bltzGeneration(const Vector<string>& codeline)
{
  Vector<string>* bltzPart = new Vector<string>;
  bltzPart->push_back("blt");
  bltzPart->push_back(codeline.at(1));
  bltzPart->push_back("x0");
  bltzPart->push_back(codeline.at(2));
  int offset;
  offset = stoi(bltzPart->at(3));
  Stack<int>* BinarioBltz = BtypeGeneration(*bltzPart, offset);
  writeToFile(BinarioBltz);
}
void bgtzGeneration(const Vector<string>& codeline)
{
  Vector<string>* bgtzPart = new Vector<string>;
  bgtzPart->push_back("blt");
  bgtzPart->push_back("x0");
  bgtzPart->push_back(codeline.at(1));
  bgtzPart->push_back(codeline.at(2));
  int offset;
  offset = stoi(bgtzPart->at(3));
  Stack<int>* BinarioBgtz = BtypeGeneration(*bgtzPart, offset);
  writeToFile(BinarioBgtz);
}
void bgtGeneration(const Vector<string>& codeline)
{
  Vector<string>* bgtPart = new Vector<string>;
  bgtPart->push_back("blt");
  bgtPart->push_back(codeline.at(2));
  bgtPart->push_back(codeline.at(1));
  bgtPart->push_back(codeline.at(3));
  int offset;
  offset = stoi(bgtPart->at(3));
  Stack<int>* BinarioBgt = BtypeGeneration(*bgtPart, offset);
  writeToFile(BinarioBgt);
}
void bleGeneration(const Vector<string>& codeline)
{
  Vector<string>* blePart = new Vector<string>;
  blePart->push_back("bge");
  blePart->push_back(codeline.at(2));
  blePart->push_back(codeline.at(1));
  blePart->push_back(codeline.at(3));
  int offset;
  offset = stoi(blePart->at(3));
  Stack<int>* BinarioBle = BtypeGeneration(*blePart, offset);
  writeToFile(BinarioBle);
}
void bgtuGeneration(const Vector<string>& codeline)
{
  Vector<string>* bgtuPart = new Vector<string>;
  bgtuPart->push_back("bltu");
  bgtuPart->push_back(codeline.at(2));
  bgtuPart->push_back(codeline.at(1));
  bgtuPart->push_back(codeline.at(3));
  int offset;
  offset = stoi(bgtuPart->at(3));
  Stack<int>* BinarioBgtu = BtypeGeneration(*bgtuPart, offset);
  writeToFile(BinarioBgtu);
}
void bleuGeneration(const Vector<string>& codeline)
{
  Vector<string>* bleuPart = new Vector<string>;
  bleuPart->push_back("bltu");
  bleuPart->push_back(codeline.at(2));
  bleuPart->push_back(codeline.at(1));
  bleuPart->push_back(codeline.at(3));
  int offset;
  offset = stoi(bleuPart->at(3));
  Stack<int>* BinarioBleu = BtypeGeneration(*bleuPart, offset);
  writeToFile(BinarioBleu);
}
void jGeneration(const Vector<string>& codeline)
{
  Vector<string>* jPart = new Vector<string>;
  jPart->push_back("jal");
  jPart->push_back("x0");
  jPart->push_back(codeline.at(1));
  int offset;
  offset = stoi(codeline.at(1));
  Stack<int>* BinarioJ = JtypeGeneration(*jPart, offset);
  writeToFile(BinarioJ);
}
void jrGeneration(const Vector<string>& codeline)
{
  Vector<string>* jrPart = new Vector<string>;
  jrPart->push_back("jalr");
  jrPart->push_back("x0");
  jrPart->push_back(codeline.at(1));
  jrPart->push_back("0");
  Stack<int>* BinarioJr = ItypeGeneration(*jrPart);
  writeToFile(BinarioJr);
}
void jalGeneration(const Vector<string>& codeline)
{
  Vector<string>* jalPart = new Vector<string>;
  jalPart->push_back("jal");
  jalPart->push_back("x1");
  jalPart->push_back(codeline.at(1));
  int offset;
  offset = stoi(codeline.at(1));
  Stack<int>* BinarioJal = JtypeGeneration(*jalPart, offset);
  writeToFile(BinarioJal);
}
void jalrGeneration(const Vector<string>& codeline)
{
  Vector<string>* jalrPart = new Vector<string>;
  jalrPart->push_back("jalr");
  jalrPart->push_back("x1");
  jalrPart->push_back(codeline.at(1));
  jalrPart->push_back("0");
  Stack<int>* BinarioJalr = ItypeGeneration(*jalrPart);
  writeToFile(BinarioJalr);
}
void retGeneration()
{
  Vector<string>* retPart = new Vector<string>;
  retPart->push_back("jalr");
  retPart->push_back("x0");
  retPart->push_back("x1");
  retPart->push_back("0");
  Stack<int>* BinarioRet = ItypeGeneration(*retPart);
  writeToFile(BinarioRet);
}
void callGeneration(const Vector<string>& codeline)
{
  Vector<string>* auipcPart = new Vector<string>;
  Vector<string>* jalrPart = new Vector<string>;
  auipcPart->push_back("auipc");
  auipcPart->push_back("x1");
  auipcPart->push_back(codeline.at(1));
  jalrPart->push_back("jalr");
  jalrPart->push_back("x1");
  jalrPart->push_back("x1");
  jalrPart->push_back(codeline.at(1));
  Stack<int>* BinarioAUIPC = UtypeGeneration(*auipcPart);
  Stack<int>* BinarioJalr = ItypeGeneration(*jalrPart);
  writeToFile(BinarioAUIPC);
  writeToFile(BinarioJalr);
}
void tailGeneration(const Vector<string>& codeline)
{
  Vector<string>* auipcPart = new Vector<string>;
  Vector<string>* jalrPart = new Vector<string>;
  auipcPart->push_back("auipc");
  auipcPart->push_back("x6");
  auipcPart->push_back(codeline.at(1));
  jalrPart->push_back("jalr");
  jalrPart->push_back("x0");
  jalrPart->push_back("x6");
  jalrPart->push_back(codeline.at(1));
  Stack<int>* BinarioJalr = ItypeGeneration(*jalrPart);
  writeToFile(BinarioJalr);
}

  

#endif