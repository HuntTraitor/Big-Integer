/*
Name: Hunter Tratar
CruzID: htratar
File: BigIntegerTest.cpp
Assignment: pa6
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"

using namespace std;

int main(){

	BigInteger A("+143");
	BigInteger B("23");
	BigInteger C,D,E,F;

	C = A+B;
	D = A-B;
	E = A*B;

	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	cout << "C = " << C << endl;
	cout << "D = " << D << endl;
	cout << "E = " << E << endl;
	cout << "F = " << F << endl;

	A *= B;
	cout << "New A = " << A << endl;
	D += E;
	cout << "New D = " << D << endl;
	F -= C;
	cout << "New F = " << F << endl;

	int result = A > B;
	cout << "A>B: " << result << endl;
	result = A < B;
	cout << "A<B: " << result << endl;
	result = A==B;
	cout << "A==B: " << result << endl << endl;

	D.makeZero();
	cout << "MakeZero D = " << D << endl;
	return 0;
}
