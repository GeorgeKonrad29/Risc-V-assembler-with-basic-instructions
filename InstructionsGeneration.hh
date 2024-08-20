#ifndef INSTRUCTIONSGENERATION_HH
#define INSTRUCTIONSGENERATION_HH
#include <string>
#include <map>
#include <iostream>
#include <bitset>
#include "Vector.hh"
#include "Stack.hh"
#include "Colectors.hh"
#include "bst.hh"
using std::string;
using std::map;
using std::bitset;

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

unsigned int intOfRegCalculation(const string& codeLine)
{
  map<string,int>* registers= new map<string,int>;
  registers = registerColector();
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
void registerCalculation(const string& codeLine, Stack<int>* Binario)
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
        stringVersion= bitset<12>(complemento).to_string();
    }
  
  *constant = stringVersion;
}

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
  registerCalculation(codeline.at(1), Binario);
  func3Calculation(codeline.at(0), Binario);
  registerCalculation(codeline.at(2), Binario);
  registerCalculation(codeline.at(3), Binario);
  func7Calculation(codeline.at(0), Binario);

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
    registerCalculation(codeline.at(1), Binario);
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
      registerCalculation("x0", Binario);
      func3Calculation(codeline.at(0), Binario);
      registerCalculation("x0", Binario);
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
      registerCalculation(codeline.at(1), Binario);
      func3Calculation(codeline.at(0), Binario);
      //calculo RS1
      registerCalculation(codeline.at(2), Binario);
      //calculo inmediato
      if(codeline.at(0) == "slli" || codeline.at(0) == "srli" || codeline.at(0) == "srai")
      {
        registerCalculation(('x'+codeline.at(3)), Binario);
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
  registerCalculation(codeline.at(1), Binario);
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
  registerCalculation(codeline.at(1), Binario);
  
  for(int x=6; x >= 0;x--)
  {
    Binario->push(constant->at(x)-'0');
  }
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
  registerCalculation(codeline.at(1), Binario);
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
  registerCalculation(codeline.at(1), Binario);
  registerCalculation(codeline.at(2), Binario);
  for(int x=7; x >= 2; x--)
  {
    Binario->push(complement2[x]-'0');
  }
  Binario->push(complement2[0]-'0');
  return Binario;
}
#endif
