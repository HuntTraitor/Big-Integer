/*
Name: Hunter Tratar
CruzID: htratar
File: List.cpp
Assignment: pa6
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

//Private Constrctor----------------------------------------------------------------------

List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

//Class Constructors & Destructors------------------------------------------------------------------

List::List(){
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

//copy constructor
List::List(const List &L){
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;

	Node *N = nullptr;
	for(N = L.frontDummy->next; N != L.backDummy; N = N->next){
		this->insertBefore(N->data);
	}
}

List::~List(){
	clear();
	delete frontDummy;
	delete backDummy;
}

//Access Functions-------------------------------------------------------------------------------------------

int List::length() const{
	return(num_elements);
}

ListElement List::front() const{
	if(length() <= 0){
		throw std::length_error("List: front(): empty List");
	}

	return(frontDummy->next->data);
}

ListElement List::back() const{
	if(length() <= 0){
		throw std::length_error("List: back(): empty List");
	}

	return(backDummy->prev->data);
}

int List::position() const{
	return(pos_cursor);
}

ListElement List::peekNext() const{
	if(position() >= length()){
		throw std::range_error("List: peekNext(): cursor at back");
	}

	return(afterCursor->data);
}

ListElement List::peekPrev() const{
	if(position() <= 0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}

	return(beforeCursor->data);
}

//Manipulation Procedures--------------------------------------------------------------------------------------------------------------

void List::clear(){
	moveFront();
	while(afterCursor != backDummy){
		eraseAfter();
	}
}

void List::moveFront(){
	pos_cursor = 0;
	afterCursor = frontDummy->next;
	beforeCursor = frontDummy;

}

void List::moveBack(){
	pos_cursor = num_elements;
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;;
}

ListElement List::moveNext(){
	if(position() >= length()){
		throw std::range_error("List: moveNext(): cursor at back");
	}

	afterCursor = afterCursor->next;
	beforeCursor = beforeCursor->next;
	pos_cursor++;
	return beforeCursor->data;
}

ListElement List::movePrev(){
	if(position() <= 0){
		throw std::range_error("List: movePrev(): cursor at front");
	}

	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	pos_cursor--;
	return afterCursor->data;
}

void List::insertAfter(ListElement x){
	Node *N = new Node(x);
	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements++;
}

void List::insertBefore(ListElement x){
	Node *N = new Node(x);
	N->next = afterCursor;
	N->prev = beforeCursor;
	afterCursor->prev = N;
	beforeCursor->next = N;
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

void List::setAfter(ListElement x){
	if(position() >= length()){
		throw std::range_error("List: setAfter(): cursor at back");
	}

	afterCursor->data = x;
}

void List::setBefore(ListElement x){
	if(position() <= 0){
		throw std::range_error("List: setBefore(): cursor at front");
	}

	beforeCursor->data = x;
}

void List::eraseAfter(){
	if(position() >= length()){
		throw std::range_error("List: eraseAfter(): cursor at back");
	}

	Node *N = afterCursor;
	afterCursor->prev->next = afterCursor->next;
	afterCursor->next->prev = beforeCursor;
	afterCursor = afterCursor->next;
	num_elements--;
	delete N;
}

void List::eraseBefore(){
	if(position() <= 0){
		throw std::range_error("List: eraseBefore(): cursor at front");
	}

	Node *N = beforeCursor;
	beforeCursor->next->prev = beforeCursor->prev; //this one
	beforeCursor->prev->next = afterCursor;
	beforeCursor = beforeCursor->prev;
	pos_cursor--;
	num_elements--;
	delete N;
}

//other functions------------------------------------------------------------------------------------------------------

int List::findNext(ListElement x){
	while(pos_cursor != num_elements){
		Node *N = afterCursor;
		if(N->data == x){
			moveNext();
			return pos_cursor;
		}
		moveNext();
	}
	return -1;
}

int List::findPrev(ListElement x){
	while(pos_cursor != 0){
		Node *N = beforeCursor;
		if(N->data == x){
			movePrev();
			return pos_cursor;
		}
		movePrev();
	}
	return -1;
}

void List::cleanup(){
	int counter;
	List L1(*this);
	List L2(*this);
	L1.moveFront();

	while(L1.afterCursor != L1.backDummy){
		L2.moveFront();
		counter = 0;
		while(L2.afterCursor != L2.backDummy){
			if(L2.peekNext() == L1.peekNext()){
				counter++;
			}
			if(counter > 1){
				if(L2.position() < (*this).position()){
					pos_cursor--;
					counter--;
				}
				L2.eraseAfter();
			}
			if(L2.afterCursor == L2.backDummy){
				break;
			}
			L2.moveNext();
		}
		L1.moveNext();
	}

	int finalCount = pos_cursor;
	(*this) = L2;
	(*this).moveFront();

	for(int i = 0; i < finalCount; i++){
		(*this).moveNext();
	}

}

List List::concat(const List &L) const{	
	List final(*this);
	final.moveBack();

	Node *N = nullptr;
	for(N = L.frontDummy->next; N != L.backDummy; N = N->next){
		final.insertBefore(N->data);
	}
	final.moveFront();

	return final;
}

std::string List::to_string() const{

	if(length() == 0){
		std::string s = "()";
		return s;
	}

	Node *N = nullptr;
	std::string s = "(";
	for(N = frontDummy->next; N != backDummy; N = N->next){
		s += std::to_string(N->data) + ", ";
	}
	s.pop_back();
	s.pop_back();
	s += ")";

	return s;
}

bool List::equals(const List &R) const{

	bool eq = false;
	Node *N = nullptr;
	Node *M = nullptr;

	eq = (this->num_elements == R.length());
	N = this->frontDummy;
	M = R.frontDummy;

	while(eq && N != nullptr){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

std::ostream& operator<< (std::ostream &stream, const List &L){
	stream << L.List::to_string();
	return stream;
}

bool operator==(const List &A, const List &B){
	return A.List::equals(B);
}

List &List::operator=(const List &L){ //similar to copy constructor
	if(this != &L){
		List temp = L;
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(num_elements, temp.num_elements);
	}
	return *this;
}



