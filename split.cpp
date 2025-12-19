/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE

  if (in == NULL){ //Base case
    return; 
  }
  else if(in -> value % 2 ==0){
    //it is an EVEN number at first node
    Node* add_even = in; 
    in = in -> next; //move in to next NODE
    add_even -> next = nullptr; 

    if(evens == NULL){ //first number being put into evens list
      evens = add_even;
    }
    else{ 
      addToEnd(evens, add_even);
    }
  }
  else{ //ODDS list updating

    Node* add_odd = in; 
    in = in -> next; //move in to next NODE
    add_odd -> next = nullptr; 

    if(odds == NULL){ //first number being put into odds list
      odds = add_odd;
    }
    else{
      addToEnd(odds, add_odd);
    }
  }

  split(in, odds, evens); //recursive call
}

/* If you needed a helper function, write it here */
void addToEnd(Node*& func, Node* add){ //make sure you are calling evens/odds as func
  if(func -> next == NULL){
    //reached the last Node of even/odd
    func -> next = add;
    return;
  }
  else{
    //move to next node
    addToEnd(func -> next, add);
  }

}
