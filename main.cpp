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
using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
using std::map;
using std::bitset;
using std::ios;
using std::to_string;


//Funcion que convierte un numero binario a hexadecimal
string binToHex(Stack<int>* Binario)
{
  string hex;
  hex = "0x";
  for(int x=0; x < 8; x++)
  {
    int decimal = 0;
    for(int y=0; y < 4; y++)
    {
      decimal += Binario->top()*pow(2,3-y);
      Binario->pop();
    }
    if(decimal < 10)
    {
      hex += to_string(decimal);
    }
    else
    {
      hex += (char)(decimal+55);
    }
  }
  return hex;
}
void writeToFile(Stack<int>* Binario)
{
  string hex;
  hex = "";
  hex = binToHex(Binario);
  ofstream fich("Output.dat", ios::app);
  if (!fich.is_open())
  {
    cout <<"Error al abrir Output.dat\n";
    exit(EXIT_FAILURE);
  }
  fich<<hex<<endl;
  fich.close();
}


bool empty(string codeline)
{
  for (unsigned int positionInString=0; positionInString < codeline.size(); positionInString++)
  {
    //se considera vacia si tiene un numeral
    if(codeline[positionInString] == '#')
    {
      return true;
    }
    else if(codeline[positionInString] != ' '&& codeline[positionInString] != '\t' && codeline[positionInString] != '\n' && codeline[positionInString] != '\r' && codeline[positionInString] != '\v' && codeline[positionInString] != '\f')
    {
      return false;
    }
    
  }
  return true;
}
string deleteIdentation(string &codeline)
{
  unsigned int numberOfSpaces=0;
  while(codeline[numberOfSpaces] == ' ' || codeline[numberOfSpaces] == '\t' || codeline[numberOfSpaces] == '\n' || codeline[numberOfSpaces] == '\r' || codeline[numberOfSpaces] == '\v' || codeline[numberOfSpaces] == '\f')
  {
    numberOfSpaces++;
  }
  codeline = codeline.substr(numberOfSpaces);
  return codeline;
}
// Funcion que recolecta las instrucciones de un tipo especifico y las almacena en un arbol binario de busqueda
// para su posterior comparacion 

// Funcion que recolecta la funtion3 de las instrucciones y las monta en un arbol binario de busqueda
// para posterior comparacion en la funcion func3Calculation
void fun3Colector(BST<string>& arbol, int x)
{
  if(x == 0)
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
  else if(x == 1)
  {
    arbol.insert("sll");
    arbol.insert("slli");
    arbol.insert("lh");
    arbol.insert("sh");
    arbol.insert("bne");
    arbol.insert("mulh");
  }
  else if(x == 2)
  {
    arbol.insert("slt");
    arbol.insert("slti");
    arbol.insert("lw");
    arbol.insert("sw");
    arbol.insert("mlsu");
  }
  else if(x == 3)
  {
    arbol.insert("sltu");
    arbol.insert("sltiu");
    arbol.insert("mulu");

  }
  else if(x == 4)
  {
    arbol.insert("xor");
    arbol.insert("xori");
    arbol.insert("lbu");
    arbol.insert("blt");
    arbol.insert("div");
  }
  else if(x == 5)
  {
    arbol.insert("srl");
    arbol.insert("sra");
    arbol.insert("srli");
    arbol.insert("srai");
    arbol.insert("lhu");
    arbol.insert("bge");
    arbol.insert("divu");
  }
  else if(x == 6)
  {
    arbol.insert("or");
    arbol.insert("ori");
    arbol.insert("bltu");
    arbol.insert("rem");
  }
  else if(x == 7)
  {
    arbol.insert("and");
    arbol.insert("andi");
    arbol.insert("bgeu");
    arbol.insert("remu");
  }  
}
// Funcion que calcula los 7 bits de la funcion7 de las instrucciones ripo R
void func7Calculation(const string& codeLine, Stack<int>* Binario)
{
  if(codeLine == "sra" || codeLine == "sub")
  {
    Binario->push(0);
    Binario->push(0);
    Binario->push(1);
    Binario->push(0);
    Binario->push(1);
    Binario->push(0);
    Binario->push(0);

  }
  else if(codeLine == "mul" || codeLine == "mulh" || codeLine == "mulhsu" || codeLine == "mulhu" || codeLine == "div" || codeLine == "divu" || codeLine == "rem" || codeLine == "remu")
  {
    Binario->push(1);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
  }
  else
  {
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
  
  }
}
// Funcion que divide una linea de codigo en segmentos para su posterior manejo 
// la informacion se guarda en Vectores
Vector<string>* split(const string& codeLine)
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
map<string,int>* regColector()
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
unsigned int intOfRegCalculation(const string& codeLine)
{
  map<string,int>* registers= new map<string,int>;
  registers = regColector();
  //aqui voy
  if(registers->find(codeLine) != registers->end())
  {
    return registers->at(codeLine);
  }
  else
  {
    cout<<codeLine<<endl;
    cout<<"Error, registro no encontrado"<<endl;
    return 0;
  }
}
//funcion que calcula los 5 bits de los registros o los 12 bits de los valores inmediatos
//segun sea el caso
void Rcalculation(const string& codeLine, Stack<int>* Binario)
{
  unsigned int regNumber;
  regNumber = intOfRegCalculation(codeLine);
  for(int x=0; x < 5; x++)
  {
    Binario->push(regNumber%2);
    regNumber = regNumber/2;
  }
}  
void inmediateValueCalculation(const string& codeLine, Stack<int>* Binario)
{
  string complement2;
  if (stoi(codeLine) >= 0) {
        complement2= bitset<12>(stoi(codeLine)).to_string(); // Asumiendo un tamaño de 12 bits
    } else 
    {
        int complemento = (1 << 12) + stoi(codeLine); // Calcula el complemento a 2
        complement2= bitset<12>(complemento).to_string(); // Asumiendo un tamaño de 12 bits
    }
  for(int x=11; x >= 0; x--)
  {
    Binario->push(complement2[x]-'0');
  }
}
//Identifica que valor de func3 tiene la instruccion y lo convierte a binario
void func3Calculation(const string& codeLine, Stack<int>* Binario)
{
  BST<string> x0, x1, x2, x3, x4, x5, x6, x7;
  fun3Colector(x0, 0);
  fun3Colector(x1, 1);
  fun3Colector(x2, 2);
  fun3Colector(x3, 3);
  fun3Colector(x4, 4);
  fun3Colector(x5, 5);
  fun3Colector(x6, 6);
  fun3Colector(x7, 7);
  if(x0.find(codeLine))
  {
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
  }
  else if(x1.find(codeLine))
  {
    Binario->push(1);
    Binario->push(0);
    Binario->push(0);
  }
  else if(x2.find(codeLine))
  {
    Binario->push(0);
    Binario->push(1);
    Binario->push(0);
  }
  else if(x3.find(codeLine))
  {
    Binario->push(1);
    Binario->push(1);
    Binario->push(0);
  }
  else if(x4.find(codeLine))
  {
    Binario->push(0);
    Binario->push(0);
    Binario->push(1);
  }
  else if(x5.find(codeLine))
  {
    Binario->push(1);
    Binario->push(0);
    Binario->push(1);
  }
  else if(x6.find(codeLine))
  {
    Binario->push(0);
    Binario->push(1);
    Binario->push(1);
  }
  else if(x7.find(codeLine))
  {
    Binario->push(1);
    Binario->push(1);
    Binario->push(1);
  }

}
//obtiene las contantes de las instrucciones tipo I que lo necesitan o las tipo S
void getConstant(const string& codeLine, string* constant)
{
  string stringVersion="";
  char actualChar;
  int x = 0;
  while(actualChar != '(')
  {
    actualChar = codeLine[x];
    stringVersion += actualChar;
    x++; 
  }
  stringVersion = stringVersion.substr(0, stringVersion.size()-1);
  //usa bitset para convertir a stringversion a complemento a 2
  if (stoi(stringVersion) >= 0) {
        stringVersion= bitset<12>(stoi(stringVersion)).to_string(); // Asumiendo un tamaño de 12 bits
    } else 
    {
        int complemento = (1 << 12) + stoi(stringVersion); // Calcula el complemento a 2
        stringVersion= bitset<12>(complemento).to_string(); // Asumiendo un tamaño de 12 bits
    }
  
  *constant = stringVersion;
}
//Funcion que convierte los registros RS, rs1 y rs2 a enteros para su posterior conversion a binario
bool isLetter(char x)
{
  if(x >= 'a' && x <= 'z')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
void getR(const string& codeLine, int* rs2)
{
  string stringVersion="";
  char actualChar;
  int x;
  while(!isLetter(codeLine[x]))
  {
    actualChar = codeLine[x];
    x++;
  }
  while(actualChar != ')')
  {
    actualChar = codeLine[x];
    stringVersion += actualChar;
    x++;
  }
  stringVersion = stringVersion.substr(0, stringVersion.size()-1);
  *rs2 = intOfRegCalculation(stringVersion);
}
//Funcion que trata las instrucciones tipo S o las de tipo I que lo requieran
void sTreatment(const Vector<string>& codeline, Stack<int>* Binario)
{
  string* constant= new string;
  int* rs1= new int;
  getConstant(codeline.at(2),constant);
  getR(codeline.at(2),rs1);
  int y;
  
  for(int x=11; x >= 7;x--)
  {
    Binario->push(constant->at(x)-'0');
  }
  func3Calculation(codeline.at(0), Binario);
  y=0;
  while(y < 5)
  {
    Binario->push((*rs1)%2);
    *rs1 = (*rs1)/2;
    y++;
  }
  Rcalculation(codeline.at(1), Binario);
  
  for(int x=6; x >= 0;x--)
  {
    Binario->push(constant->at(x)-'0');
  }

} 
//Funciones que convierten las instrucciones a binario segun su tipo
//funcionan de la siguiente manera:
//Se crea un stack de 32 bits
//Se verifica el codigo de operacion de la instruccion especifica y se monta en el stack
//Se monta en binario los parametros necesarios de cada instruccion
Stack<int>* RtypeGeneration(Vector<string>& codeline)
{
  Stack<int>* Binario = new Stack<int>(32);
  if((codeline.at(0)[0] == 'a'||codeline.at(0)[2] == '.') && (codeline.at(0) != "add" && codeline.at(0) != "and" ))
  {
    Binario->push(1);
    Binario->push(1);
    Binario->push(1);
    Binario->push(1);
    Binario->push(0);
    Binario->push(1);
    Binario->push(0);
  }
  else
  {
    Binario->push(1);
    Binario->push(1);
    Binario->push(0);
    Binario->push(0);
    Binario->push(1);
    Binario->push(1);
    Binario->push(0);
  } 
  Rcalculation(codeline.at(1), Binario);
  func3Calculation(codeline.at(0), Binario);
  Rcalculation(codeline.at(2), Binario);
  Rcalculation(codeline.at(3), Binario);
  func7Calculation(codeline.at(0), Binario);
  //Aqui se imprime el binario(usado para testear el programa)
  /* while(!Binario->empty())
  {
    cout<<Binario->top()<<" ";
    Binario->pop();
  } 
  cout<<endl;*/

  return Binario;

  

}  
Stack<int>* ItypeGeneration(Vector<string>& codeline)
{
  Stack<int>* Binario= new Stack<int>(32);
  if(codeline.at(0)[0] == 'l')
  {
    
    Binario->push(1);
    Binario->push(1);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    Binario->push(0);
    string* constant= new string;
    int* rs1= new int;
    Rcalculation(codeline.at(1), Binario);
    getConstant(codeline.at(2),constant);
    getR(codeline.at(2),rs1);
    func3Calculation(codeline.at(0), Binario);
    for(int x=0;x < 5;x++)
    {
      Binario->push((*rs1)%2);
      *rs1 = (*rs1)/2; 
    }
    for(int x=11; x >= 0;x--)
    {
      Binario->push(constant->at(x)-'0');
    }
  }
  else
  {
    if(codeline.at(0)[0] == 'e')
    {
      
      Binario->push(1);
      Binario->push(1);
      Binario->push(0);
      Binario->push(0);
      Binario->push(1);
      Binario->push(1);
      Binario->push(1);
      Rcalculation("x0", Binario);
      func3Calculation(codeline.at(0), Binario);
      Rcalculation("x0", Binario);
      inmediateValueCalculation("0", Binario);
    }
    else
    {
      if(codeline.at(0) == "jalr")
      {
        Binario->push(1);
        Binario->push(1);
        Binario->push(1);
        Binario->push(0);
        Binario->push(0);
        Binario->push(1);
        Binario->push(1);
      }
      else
      {
        Binario->push(1);
        Binario->push(1);
        Binario->push(0);
        Binario->push(0);
        Binario->push(1);
        Binario->push(0);
        Binario->push(0);
      }
      //calculo RD
      Rcalculation(codeline.at(1), Binario);
      func3Calculation(codeline.at(0), Binario);
      //calculo RS1
      Rcalculation(codeline.at(2), Binario);
      //calculo inmediato
      if(codeline.at(0) == "slli" || codeline.at(0) == "srli" || codeline.at(0) == "srai")
      {
        Rcalculation(('x'+codeline.at(3)), Binario);
        for(int x=0; x < 5; x++)
        {
          Binario->pop();
        }
        inmediateValueCalculation(codeline.at(3), Binario);
      }
      else
      {
        inmediateValueCalculation(codeline.at(3), Binario);
      }
    }
  }
  //Aqui se imprime el binario(usado para testear el programa)
  /* while(!Binario->empty())
  {
    cout<<Binario->top()<<" ";
    Binario->pop();
  }
  cout<<endl; */
  
  return Binario;
}
Stack<int>* JtypeGeneration(const Vector<string>& codeline, int& offset)
{
  Stack<int>* Binario= new Stack<int>(32);
  Binario->push(1);
  Binario->push(1);
  Binario->push(1);
  Binario->push(1);
  Binario->push(0);
  Binario->push(1);
  Binario->push(1);
  Rcalculation(codeline.at(1), Binario);
  string complement2;
  if (offset >= 0) 
  {
    complement2= bitset<21>(offset).to_string(); // Asumiendo un tamaño de 20 bits
  } 
  else 
  {
    int complemento = (1 << 21) + offset; // Calcula el complemento a 2
    complement2= bitset<21>(complemento).to_string(); // Asumiendo un tamaño de 20 bits
  }
  for(int x=8; x >= 1; x--)
  {
    Binario->push(complement2[x]-'0');
  }
  Binario->push(complement2[9]-'0');
  for(int x=19; x >= 10; x--)
  {
    Binario->push(complement2[x]-'0');
  }
  Binario->push(complement2[0]-'0');
  
  return Binario;
}
Stack<int>* StypeGeneration(const Vector<string>& codeline)
{
  Stack<int>* Binario= new Stack<int>(32);
  Binario->push(1);
  Binario->push(1);
  Binario->push(0);
  Binario->push(0);
  Binario->push(0);
  Binario->push(1);
  Binario->push(0);
  sTreatment(codeline, Binario);
  return Binario;
}
Stack<int>* UtypeGeneration(const Vector<string>& codeline)
{
  Stack<int>* Binario= new Stack<int>(32);
  if(codeline.at(0)[0] == 'l')
  {
    Binario->push(1);
    Binario->push(1);
    Binario->push(1);
    Binario->push(0);
    Binario->push(1);
    Binario->push(1);
    Binario->push(0);
  }
  else
  {
    Binario->push(1);
    Binario->push(1);
    Binario->push(1);
    Binario->push(0);
    Binario->push(1);
    Binario->push(0);
    Binario->push(0);

  }
  Rcalculation(codeline.at(1), Binario);
  string complement2;
  if (stoi(codeline.at(2)) >= 0) 
  {
    complement2= bitset<20>(stoi(codeline.at(2))).to_string();
  } 
  else 
  {
    int complemento = (1 << 20) + stoi(codeline.at(2));
    complement2= bitset<20>(complemento).to_string();
  }
  for(int x=19; x >= 0; x--)
  {
    Binario->push(complement2[x]-'0');
  }
  return Binario;
}
Stack<int>* BtypeGeneration(const Vector<string>& codeline,int& offset)
{
  Stack<int>* Binario= new Stack<int>(32);
  Binario->push(1);
  Binario->push(1);
  Binario->push(0);
  Binario->push(0);
  Binario->push(0);
  Binario->push(1);
  Binario->push(1);
    //aqui hay que usar bitset
  string complement2;
  if (offset >= 0) {
      complement2= bitset<13>(offset).to_string(); // Asumiendo un tamaño de 12 bits y que vamos a descartar el primero
  } else 
  {
      int complemento = (1 << 13) + offset; // Calcula el complemento a 2
      complement2= bitset<13>(complemento).to_string(); 
  }
  Binario->push(complement2[1]-'0');
  for(int x=11; x >= 8; x--)
  {
    Binario->push(complement2[x]-'0');
  }
  func3Calculation(codeline.at(0), Binario);
  Rcalculation(codeline.at(1), Binario);
  Rcalculation(codeline.at(2), Binario);
  for(int x=7; x >= 2; x--)
  {
    Binario->push(complement2[x]-'0');
  }
  Binario->push(complement2[0]-'0');
  return Binario;
}
//debido a que las pseudoinstrucciones no tienen un patron definido se hace una funcion 
//que trate a cada una especialmente
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

int main()
{
  ifstream fich("Input.dat", ios::in);
  if (!fich.is_open())
  {
    cout <<"Error al abrir Input.dat\n";
    exit(EXIT_FAILURE);
  }
  
  string line;
  int num_elementos = 0;
  // Cuenta el numero de lineas no vacias
  while (getline(fich, line)) {
    if(!line.empty() && !empty(line))
    {
      num_elementos++;   
    }   
  }
  fich.clear();
  fich.seekg(0, ios::beg);
  Vector<string> data;
  string valor;
  // Lee los datos no vacios como strings y hace push back a un vector
  for (int x=0; x < num_elementos; x++)
  {
    getline(fich, valor);
    if(!valor.empty() && !empty(valor))
    {
      valor = deleteIdentation(valor);
      data.push_back(valor);
    }
    else
    {
      x--;
    }
  }
  fich.close();
  //hasta esta parte es la lectura del archivo, de aqui en adelante pasamos a las conversiones a binario
  //A continuacion clasificaremos que tipo de instruccion es y la convertiremos a binario
  //Para ello usaremos un arbol binario de busqueda
  BST<string> Rtype, Itype, Jtype, Stype, Utype, Btype, pseudoInstructions;
  Rtype = InstructionsColector("r");
  Itype = InstructionsColector("i");
  Jtype = InstructionsColector("j");
  Stype = InstructionsColector("s");
  Utype = InstructionsColector("u");
  Btype = InstructionsColector("b");
  pseudoInstructions = InstructionsColector("p");
  //A continuacion se hara la identificacion de las instrucciones y su conversion a binario o hexadecimal
  for (unsigned int x=0; x < data.getSize(); x++)
  {
    
    string codeLine = data.at(x);
    bool flag;
    flag = false;
    Vector<string>* segmentedLine = new Vector<string>;
    segmentedLine = split(codeLine);
    cout<<"linea de codigo "<<x<<" "<<segmentedLine->at(0)<<endl;
    Stack<int>* Binario = new Stack<int>(32);
     if(pseudoInstructions.find(segmentedLine->at(0)))
    {
      if (segmentedLine->at(0)[3]=='z')
      {
        int y;
        y=0;
        while(data.at(y) != (segmentedLine->at(2)+':'))
        {
          y++;  
        }
        y = y-x;
        y = y*4;
        segmentedLine->pop_back();
        segmentedLine->push_back(to_string(y));
      }
      else if(segmentedLine->at(0)[0]=='b' && segmentedLine->getSize() == 4)
      {
        int y;
        y=0;
        while(data.at(y) != (segmentedLine->at(3)+':'))
        {
          y++;  
        }
        y = y-x;
        y = y*4;
        segmentedLine->pop_back();
        segmentedLine->push_back(to_string(y));
      }
      else if(segmentedLine->getSize() == 2 && !(segmentedLine->at(0) == "jr" || segmentedLine->at(0) == "jalr"))
      {
        cout<<"entro"<<endl;
        int y;
        y=0;
        while(data.at(y) != (segmentedLine->at(1)+':'))
        {
          y++;  
        }
        y = y-x;
        y = y*4;
        segmentedLine->pop_back();
        segmentedLine->push_back(to_string(y));
      }
      flag = pseudoInstructionsTreatments(segmentedLine);
    }
    else  if(Rtype.find(segmentedLine->at(0)))
    {
      Binario = RtypeGeneration(*segmentedLine);
    }
    else if(Utype.find(segmentedLine->at(0)))
    {
      Binario = UtypeGeneration( *segmentedLine );
    }
    else if(Btype.find(segmentedLine->at(0)) && !flag)
    {
      int y;
      y=0;
      while(data.at(y) != (segmentedLine->at(3)+':'))
      {
        y++;  
      }
      y = y-x;
      y = y*4;
      Binario = BtypeGeneration(*segmentedLine, y);
    }
    if(Itype.find(segmentedLine->at(0)) && !flag)
    {
      Binario = ItypeGeneration(*segmentedLine);
      
    }
    else if(Jtype.find(segmentedLine->at(0)) && !flag)
    {
      cout<<"entro a Jtype"<<endl;
      int y;
      y=0;
      while(data.at(y) != (segmentedLine->at(2)+':'))
      {
        y++;  
      }
      y = y-x;
      y = y*4;
      Binario = JtypeGeneration(*segmentedLine, y);
    }
    else if(Stype.find(segmentedLine->at(0)) && !flag)
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
cout<<"Fin del programa"<<endl;  
return 0;
}
