/*
Name: Hunter Tratar
CruzID: htratar
File: Arithmetic.cpp
Assignment: pa6
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){
   ifstream in;
   ofstream out;
   string num1;
   string line;
   string num2;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   getline(in, num1);
   getline(in, line);
   getline(in, num2);

   BigInteger three("3");
   BigInteger two("2");
   BigInteger nine("9");
   BigInteger sixteen("16");

   BigInteger A(num1);
   BigInteger B(num2);
   BigInteger C,D,E,F,G,H,I,J,K;

   C = A+B;
   D = A-B;
   E = A-A;
   F = three*A-two*B;
   G = A*B;
   H = A*A;
   I = B*B;
   J = nine*(A*A*A*A) + sixteen*(B*B*B*B*B);

   out << A << "\n\n";
   out << B << "\n\n";
   out << C << "\n\n";
   out << D << "\n\n";
   out << E << "\n\n";
   out << F << "\n\n";
   out << G << "\n\n";
   out << H << "\n\n";
   out << I << "\n\n";
   out << J << "\n\n";

   // close files 
   in.close();
   out.close();
   
	return 0;


}