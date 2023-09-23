/*
Name: Hunter Tratar
CruzID: htratar
File: ListTest.cpp
Assignment: pa6
*/

#include<iostream>
#include<string>
#include<stdexcept>
#include "List.h"

using namespace std;

int main(){
	List A;

	int test = A.length();

	cout << "The length of A is: " << test << endl;

	cout << A << endl;

	A.insertAfter(3);
	A.insertAfter(5);
	A.insertAfter(4);
	A.insertBefore(10);

	cout << A << endl;

	cout << "The new length of A is: " << A.length() << endl;

	A.moveFront();
	cout << "The element after cursor is: " << A.peekNext() << endl;

	A.moveBack();
	cout << "The element before cursor is: " << A.peekPrev() << endl;

	A.moveFront();
	A.moveNext();

	cout << A.peekNext() << endl;

	A.setAfter(9);
	cout << A << endl;

	A.insertAfter(11);
	cout << A << endl;
	cout << A.peekNext() << endl;

	A.moveNext();
	A.insertBefore(23);

	cout << endl << A << endl;
	cout << "Current Position: " << A.position() << endl;
	cout << "Peek Next: " << A.peekNext() << endl;
	cout << "Peek Prev: " << A.peekPrev() << endl;
	A.eraseBefore();
	A.eraseAfter();

	cout << A << endl;
	cout << "New Current Position: " << A.position() << endl << endl;

	A.movePrev();
	cout << endl << A << endl;
	cout << "Current Position: " << A.position() << endl;
	cout << "Peek Next: " << A.peekNext() << endl;
	cout << "Peek Prev: " << A.peekPrev() << endl;

	List B = A;
	cout << B << endl;

	B.moveFront();
	B.moveNext();

	cout << endl << B << endl;
	cout << "Current Position: " << B.position() << endl;
	cout << "Peek Next: " << B.peekNext() << endl;
	cout << "Peek Prev: " << B.peekPrev() << endl;

	B.movePrev();


	cout << endl << B << endl;

	cout << B.findNext(4) << endl;

	cout << B.findPrev(10) << endl;

   B.insertBefore(5);
   B.insertAfter(11);
   cout << "B beofre Cleanup(): " << B << endl;
   cout << B.position() << endl;
   B.cleanup();

   cout << "B after Cleanup(): " << B << endl;
   cout << B.position() << endl;

   List C;
   C.insertAfter(56);
   C.insertBefore(100);
   C.insertBefore(23);

   cout << B.concat(C) << endl;

   B = B.concat(C);

   if(C == B){
      cout << "TURE" << endl;
   }
   else{
      cout << "FALSE" << endl;
   }

   C.clear();
   C.insertBefore(5);
   C.insertBefore(11);
   C.insertBefore(10);
   C.insertBefore(3);
   C.insertBefore(100);
   C.insertBefore(23);
   C.insertBefore(56);

   cout << C << endl;

    if(C == B){
      cout << "TURE" << endl;
   }
   else{
      cout << "FALSE" << endl;
   }

	return(EXIT_SUCCESS);
}