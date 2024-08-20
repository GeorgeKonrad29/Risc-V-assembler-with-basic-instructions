#ifndef __FILEUSAGE_HH__
#define __FILEUSAGE_HH__
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Stack.hh"
#include "Vector.hh"
#include "Stack.hh"
using std::string;
using std::ifstream;
using std::ofstream;
using std::to_string;
using std::cout;
using std::endl;
using std::ios;
using std::pow;
string binToHex(Stack<int>* Binario)
{
  string hex;
  //siempre empieza con 0x
  hex = "0x";
  for(int x=0; x < 8; x++)
  {
    int decimalVersion = 0;
    for(int y=0; y < 4; y++)
    {
      decimalVersion += Binario->top()*pow(2,3-y);
      Binario->pop();
    }
    if(decimalVersion < 10)
    {
      hex += to_string(decimalVersion);
    }
    else
    {
      hex += (char)(decimalVersion+55);
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
  for (unsigned int codelinePosition=0; codelinePosition < codeline.size(); codelinePosition++)
  {
    //se considera vacia si tiene un numeral
    if(codeline[codelinePosition] == '#')
    {
      return true;
    }
    else if(codeline[codelinePosition] != ' '&& codeline[codelinePosition] != '\t' && codeline[codelinePosition] != '\n' && codeline[codelinePosition] != '\r' && codeline[codelinePosition] != '\v' && codeline[codelinePosition] != '\f')
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
Vector<string> readFromFile()
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
    string codeline;
    // Lee los datos no vacios como strings y hace push back a un vector
    for (int inputLine=0; inputLine < num_elementos; inputLine++)
    {
      getline(fich, codeline);
      if(!codeline.empty() && !empty(codeline))
      {
        codeline = deleteIdentation(codeline);
        data.push_back(codeline);
      }
      else
      {
        inputLine--;
      }
    }
    fich.close();
    return data;
}
#endif