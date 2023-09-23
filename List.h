/*
Name: Hunter Tratar
CruzID: htratar
File: List.h
Assignment: pa6
*/

//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT. List is a double ended queue with a vertical
// cursor standing between elements. The cursor position is always defined
// to be an int in the range 0 (at front) to length of List (at back).
// An empty list consists of the vertical cursor only, with no elements.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>

#ifndef List_H_INCLUDE_
#define List_H_INCLUDE_

// Exported types -------------------------------------------------------------
typedef long ListElement;

class List{

private:

   struct Node{
      ListElement data;
      Node* next;
      Node* prev;
      Node(ListElement x);
   };

   Node* frontDummy;
   Node* backDummy;
   Node* beforeCursor;
   Node* afterCursor;
   int pos_cursor;
   int num_elements;

public:

   // Class Constructors & Destructors ----------------------------------------
   
   List();

   List(const List& L);

   ~List();


   // Access functions --------------------------------------------------------

   int length() const;
   ListElement front() const;
   ListElement back() const;
   int position() const;
   ListElement peekNext() const;
   ListElement peekPrev() const;


   // Manipulation procedures -------------------------------------------------

   void clear();
   void moveFront();
   void moveBack();
   ListElement moveNext();
   ListElement movePrev();
   void insertAfter(ListElement x);
   void insertBefore(ListElement x);
   void setAfter(ListElement x);
   void setBefore(ListElement x);
   void eraseAfter();
   void eraseBefore();


   // Other Functions ---------------------------------------------------------

   int findNext(ListElement x);

   int findPrev(ListElement x);

   void cleanup();
 
   List concat(const List& L) const;

   std::string to_string() const;

   bool equals(const List& R) const;


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   friend std::ostream& operator<<( std::ostream& stream, const List& L );

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   friend bool operator==( const List& A, const List& B );

   // operator=()
   // Overwrites the state of this List with state of L.
   List& operator=( const List& L );

};


#endif