/*Elaborado por:Ing(c) Jorge Luis López Grajales
fecha: 24/03/2024
Primer Parcial Estructuras de datos
Docente: Gustavo Adolfo Gutiérrez Sabogal
El presente programa consiste de un ensamblador cuyo objetivo es interpretar de un codigo fuente en codigo en hexadecimal

*/
#include <fstream>  // Para ifstream
#include <iostream> // Para cout
#include <string> // para stoi
#include <bitset> // para bitset
#include <map>
#include <math.h>
#include "Vector.hh"
#include "bst.hh"
#include "stack.hh"
#include "Colectors.hh"
#include "fileUsage.hh"
#include "pseudoInstructionsTreatment.hh"
#include "InstructionsGeneration.hh"
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
using std::map;
using std::bitset;
using std::ios;
using std::to_string;



Vector<string>* splitCodeline(const string& codeLine)
{
  Vector<string>* segmentedLine = new Vector<string>;
  string segment;
  for (unsigned int x=0; x < codeLine.size(); x++)
  {
    if(codeLine[x] != ' ' && codeLine[x] != ',' )
    {
      segment += codeLine[x];
    }
    else if(!segment.empty())
    {
      segmentedLine->push_back(segment);
      segment = "";
    }
  }

  if (!segment.empty())
  {
    segmentedLine->push_back(segment);
  }
  return segmentedLine;
}


bool hasParentesis(const string& codeLine)
{
  for(unsigned int x=0; x < codeLine.size(); x++)
  {
    if(codeLine[x] == '(')
    {
      return 1;
    }
  }
  return 0;
}

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

void assembler()
{
  Vector<string> allCodelines= readFromFile();
  BST<string> Rtype, Itype, Jtype, Stype, Utype, Btype, pseudoInstructions;
  Rtype = InstructionsColector("r");
  Itype = InstructionsColector("i");
  Jtype = InstructionsColector("j");
  Stype = InstructionsColector("s");
  Utype = InstructionsColector("u");
  Btype = InstructionsColector("b");
  pseudoInstructions = InstructionsColector("p");
  //A continuacion se hara la identificacion de las instrucciones y su conversion a binario o hexadecimal
  for (unsigned int actualLine=0; actualLine < allCodelines.getSize(); actualLine++)
  {
    
    string codeLine = allCodelines.at(actualLine);
    bool isPseudoinstruction;
    isPseudoinstruction = false;
    Vector<string>* segmentedLine = new Vector<string>;
    segmentedLine = splitCodeline(codeLine);
    cout<<"linea de codigo "<<actualLine<<" "<<segmentedLine->at(0)<<endl;
    Stack<int>* Binario = new Stack<int>(32);
    if(pseudoInstructions.find(segmentedLine->at(0)))
    {
      if (segmentedLine->at(0)[3]=='z')
      {
        int searchLine;
        searchLine=0;
        while(allCodelines.at(searchLine) != (segmentedLine->at(2)+':'))
        {
          searchLine++;  
        }
        searchLine = searchLine-actualLine;
        searchLine = searchLine*4;
        segmentedLine->pop_back();
        segmentedLine->push_back(to_string(searchLine));
      }
      else if(segmentedLine->at(0)[0]=='b' && segmentedLine->getSize() == 4)
      {
        int searchLine;
        searchLine=0;
        while(allCodelines.at(searchLine) != (segmentedLine->at(3)+':'))
        {
          searchLine++;  
        }
        searchLine = searchLine-actualLine;
        searchLine = searchLine*4;
        segmentedLine->pop_back();
        segmentedLine->push_back(to_string(searchLine));
      }
      else if(segmentedLine->getSize() == 2 && !(segmentedLine->at(0) == "jr" || segmentedLine->at(0) == "jalr"))
      {
        cout<<"entro"<<endl;
        int searchLine;
        searchLine=0;
        while(allCodelines.at(searchLine) != (segmentedLine->at(1)+':'))
        {
          searchLine++;  
        }
        searchLine = searchLine-actualLine;
        searchLine = searchLine*4;
        segmentedLine->pop_back();
        segmentedLine->push_back(to_string(searchLine));
      }
      isPseudoinstruction = pseudoInstructionsTreatments(segmentedLine);
    }
    else  if(Rtype.find(segmentedLine->at(0)))
    {
      Binario = RtypeGeneration(*segmentedLine);
    }
    else if(Utype.find(segmentedLine->at(0)))
    {
      Binario = UtypeGeneration( *segmentedLine );
    }
    else if(Btype.find(segmentedLine->at(0)) && !isPseudoinstruction)
    {
      int searchLine;
      searchLine=0;
      while(allCodelines.at(searchLine) != (segmentedLine->at(3)+':'))
      {
        searchLine++;  
      }
      searchLine = searchLine-actualLine;
      searchLine = searchLine*4;
      Binario = BtypeGeneration(*segmentedLine, searchLine);
    }
    if(Itype.find(segmentedLine->at(0)) && !isPseudoinstruction)
    {
      Binario = ItypeGeneration(*segmentedLine);
      
    }
    else if(Jtype.find(segmentedLine->at(0)) && !isPseudoinstruction)
    {
      cout<<"entro a Jtype"<<endl;
      int searchLine;
      searchLine=0;
      while(allCodelines.at(searchLine) != (segmentedLine->at(2)+':'))
      {
        searchLine++;  
      }
      searchLine = searchLine-actualLine;
      searchLine = searchLine*4;
      Binario = JtypeGeneration(*segmentedLine, searchLine);
    }
    else if(Stype.find(segmentedLine->at(0)) && !isPseudoinstruction)
    {
      Binario = StypeGeneration(*segmentedLine);
    }
    //Aqui escribimos el binario en el archivo Output.dat linea por linea
    if (!Binario->empty())
    {
      writeToFile(Binario);
    }
    Binario->~Stack();
    
  }
}

int main()
{
  assembler();
  cout<<"Fin del programa"<<endl;  
  return 0;
}
