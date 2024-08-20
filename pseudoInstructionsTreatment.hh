#ifndef __PSEUDOINSTRUCTIONSTREATMENT_HH__
#define __PSEUDOINSTRUCTIONSTREATMENT_HH__
#include <iostream>
#include <string>
#include "Vector.hh"
#include "InstructionsTreatment.hh"
bool pseudoInstructionsTreatments(Vector<string>* codeLine)
{
  if(codeLine->at(0) == "la")
  {
    laGeneration(*codeLine);
  }
  else if((codeLine->at(0) == "lb" || codeLine->at(0) == "lh" || codeLine->at(0) == "lw") && !hasParentesis(codeLine->at(2)))
  {
    lpseudoInstructionsGeneration(*codeLine);
  }
  else if((codeLine->at(0) == "sb" || codeLine->at(0) == "sh" || codeLine->at(0) == "sw") && codeLine->getSize() == 4)
  {
    spseudoInstructionsGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "nop")
  {
     nopGeneration();
  }
  else if(codeLine->at(0) == "li")
  {
    liGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "mv")
  {
    mvGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "not")
  {
     notGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "neg")
  {
     negGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "seqz")
  {
    seqzGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "snez")
  {
    snezGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "sltz")
  {
    sltzGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "sgtz")
  {
    sgtzGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "beqz")
  {
    beqzGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "bnez")
  {
    bnezGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "blez")
  {
    blezGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "bgez")
  {
    bgezGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "bltz")
  {
    bltzGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "bgtz")
  {
    bgtzGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "bgt")
  {
     bgtGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "ble")
  {
     bleGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "bgtu")
  {
    bgtuGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "bleu")
  {
    bleuGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "j")
  {
     jGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "jr")
  {
    jrGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "jal" && codeLine->getSize() == 2)
  {
     jalGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "jalr")
  {
    jalrGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "ret")
  {
    retGeneration();
  }
  else if(codeLine->at(0) == "call")
  {
    callGeneration(*codeLine);
  }
  else if(codeLine->at(0) == "tail")
  {
    tailGeneration(*codeLine);
  }
  else
  {
    return false;
  }
  return true;
}  

#endif