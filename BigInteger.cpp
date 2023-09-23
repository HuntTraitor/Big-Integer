/*
Name: Hunter Tratar
CruzID: htratar
File: BigInteger.cpp
Assignment: pa6
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <ctype.h>
#include "BigInteger.h"

const ListElement base = 1000000000;
const int power = 9;


void negateList(List& L);
void sumList(List& S, List A, List B, int sgn);
int normalizeList(List& L);
void shiftList(List &L, int p);
void scalarMultList(List& L, ListElement m);

//-------------------------------------------------------------------------

BigInteger::BigInteger(){
	signum = 0;
	List digits;
}

BigInteger::BigInteger(std::string s){

	if(s.size() == 0){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}

	if(s[0] == '-'){
		signum = -1;
		s.erase(0, 1);
		if(s.size() == 0){
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
	}
	else if(s[0] == '+'){
		signum = 1;
		s.erase(0,1);
		if(s.size() == 0){
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
	}
	else{
		signum = 1;
	}

	for(unsigned int i = 0; i < s.size(); i++){
		if(!isdigit(s[i]))
		{
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
	}

	for(int i = s.length(); i > 0; i-=power){
		int counter = i-power;
		std::string temp = "";
		for(int j = counter; j < i; j++){
			if(j < 0){
				j = 0;
			}
			temp += std::to_string(s[j]-48);
		}
		long final = (stoi(temp));
		digits.insertAfter(final);
	}
	normalizeList(digits);
}

BigInteger::BigInteger(const BigInteger& N){
	signum = N.signum;
	this->digits = N.digits;
}

//------------------------------------------------------------------------

int BigInteger::sign() const{
	return signum;
}

int BigInteger::compare(const BigInteger& N) const{
    
	List A = this->digits;
	List B = N.digits;

	if(this->signum > N.signum){
		return 1;
	}
	else if(this->signum < N.signum){
		return -1;
	}
	else{
		if(A.length() > B.length()){
			return 1;
		}
		else if(A.length() < B.length()){
			return -1;
		}
		else{
			A.moveFront();
			B.moveFront();

			while(A.position() != A.length()){
				if(A.peekNext() > B.peekNext()){
					return 1;
				}
				else if(A.peekNext() < B.peekNext()){
					return -1;
				}
				A.moveNext();
				B.moveNext();
			}
		}
	}
    return 0;
}

//-------------------------------------------------------------------------------

void BigInteger::makeZero(){
	signum = 0;
	digits.clear();
}

void BigInteger::negate(){
	if(signum == 1){
		signum = -1;
	}
	else if(signum == -1){
		signum = 1;
	}
}

//---------------------------------------------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const{
	List S;
	BigInteger A(N);

	if(N.signum == 0){
		return *this;
	}
	else if(this->signum == 0){
		return A;
	}

	if(this->signum == -1){
		if(N.signum == -1){
			sumList(S, this->digits, N.digits, 1);
			A.signum = normalizeList(S) * -1;
			A.digits = S;
		}
		else{
			sumList(S, N.digits, this->digits, this->signum);
			A.signum = normalizeList(S);
			A.digits = S;
		}
	}
	else{
		sumList(S, this->digits, N.digits, N.signum);
		A.signum = normalizeList(S);
		A.digits = S;
	}


	if(A.digits.length() == 0){
		A.signum = 0;
	}

	return A;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
	List S;
	BigInteger A(N);

	if(N.signum == 0){
		return *this;
	}
	else if(this->signum == 0){
		A.negate();
		return A;
	}

	if(this->signum == -1){
		if(N.signum == -1){
			sumList(S, N.digits, this->digits, this->signum);
			A.signum = normalizeList(S);
			A.digits = S;
		}
		else{
			sumList(S, this->digits, N.digits, 1);
			A.signum = normalizeList(S) * -1;
			A.digits = S;
		}
	}
	else{
		sumList(S, this->digits, N.digits, N.signum*-1);
		A.signum = normalizeList(S);
		A.digits = S;
	}

	if(A.digits.length() == 0){
		A.signum = 0;
	}
	return A;
}

BigInteger BigInteger::mult(const BigInteger& N) const{
	int shift = 0;
	BigInteger A(*this);
	BigInteger B(N);
	List sm;
	BigInteger result;
	result.signum = 1;

	A.digits.moveBack();
	B.digits.moveBack();

	while(B.digits.position() != 0){
		sm = A.digits;
		scalarMultList(sm, B.digits.peekPrev());
		shiftList(sm, shift);
		sumList(result.digits, sm, result.digits, 1);
		normalizeList(result.digits);
		B.digits.movePrev();
		shift++;
	}

	if(this->signum != N.signum){
		result.signum = -1;
	}

	result.digits.moveFront();

	if(result.digits.length() == 0){
		result.signum = 0;
	}

	return result;
}

//------------------------------------------------------------------------------

void negateList(List& L){
	while(L.position() != L.length()){
		L.setAfter(L.peekNext() * -1);
		L.moveNext();
	}
}

void sumList(List& S, List A, List B, int sgn){
	S.clear();
	A.moveBack();
	B.moveBack();
	while(A.position() != 0 && B.position() != 0){
		S.insertAfter(A.peekPrev() + B.peekPrev()*sgn);
		A.movePrev();
		B.movePrev();
	}

	while(B.position() != 0){
		S.insertAfter(B.peekPrev()*sgn);
		B.movePrev();
	}
	while(A.position() != 0){
		S.insertAfter(A.peekPrev());
		A.movePrev();
	}
}

int normalizeList(List& L){
	long carry = 0;

	L.moveBack();
	while(L.position() != 0){
		if(carry != 0){
			L.setBefore(L.peekPrev() + carry);
			carry = 0;
		}
		if(L.peekPrev() >= base){
			carry = (L.peekPrev()/base);
			L.setBefore(L.peekPrev() - (carry*base));
		}
		else if(L.peekPrev() < 0 && L.position() > 1){
			L.setBefore(L.peekPrev() + base);
			carry--;
		}
		L.movePrev();
	}

	if(carry > 0){
		L.insertBefore(carry);
		carry = 0;
	}

	if(L.peekNext() < 0){
		negateList(L);
		normalizeList(L);
		return -1;
	}

	L.moveFront(); 
	while(L.peekNext() == 0 && L.length() != 1){ 
		L.eraseAfter();
	}

	if(L.peekNext() == 0){
		L.eraseAfter();
	}
	return 1;
}

void shiftList(List &L, int p){
	L.moveBack();
	for(int i = 0; i < p; i++){
		L.insertBefore(0);
	}
}

void scalarMultList(List& L, ListElement m){
	L.moveBack();
	while(L.position() != 0){
		L.setBefore(L.peekPrev() * m);
		L.movePrev();
	}
}


//------------------------------------------------------------------------------

std::string BigInteger::to_string() {
	ListElement x;
	std::string s = "";

	if(digits.length() == 0){
		return "0";
	}

	digits.moveFront();

	while(digits.position() != digits.length()){
		x = digits.peekNext();
		std::ostringstream ss;
		ss << std::setw(power) << std::setfill('0') << x;
		s += ss.str();
		digits.moveNext();
	}

	while(s[0] == '0'){
		s.erase(0,1);
	}

	if(sign() == -1){
		s.insert(0,1,'-');
	}
	return s;
}

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream &stream, BigInteger N){
	stream << N.BigInteger::to_string();
	return stream;
}

bool operator==(const BigInteger &A, const BigInteger& B){
	if(A.compare(B) == 0) {
        return true;
    }
    return false;
}

bool operator<(const BigInteger &A, const BigInteger& B){
	if(A.compare(B) == -1){
		return true;
	}
	return false;
}

bool operator<=(const BigInteger& A, const BigInteger& B){
	if(A.compare(B) == -1 || A.compare(B) == 0){
		return true;
	}
	return false;
}

bool operator>(const BigInteger& A, const BigInteger& B){
	if(A.compare(B) == 1){
		return true;
	}
	return false;
}

bool operator>=(const BigInteger& A, const BigInteger& B){
	if(A.compare(B) == 1 || A.compare(B) == 0){
		return true;
	}
	return false;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B){
	BigInteger C;
	C = A.add(B);
	return C;
}

BigInteger operator+=(BigInteger& A, const BigInteger& B){
	A = A.add(B);
	return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B){
	BigInteger C;
	C = A.sub(B);
	return C;
}

BigInteger operator-=(BigInteger &A, const BigInteger& B){
	A = A.sub(B);
	return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B){
	BigInteger C;
	C = A.mult(B);
	return C;
}

BigInteger operator*=(BigInteger& A, const BigInteger& B){
	A = A.mult(B);
	return A;
}
