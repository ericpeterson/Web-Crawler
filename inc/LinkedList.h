#ifndef CS240_LINKED_LIST_H
#define CS240_LINKED_LIST_H

#include "UnitTest.h"
#include <iostream>
using namespace std;

template <class Type>
class LinkedList;

//! LLNode implements a doubly-linked list node
template <class Type>
class LLNode {
  friend class LinkedList<Type>;  //!< LinkedList can access private members of LLNode
  public:

    //!  Constructor
    LLNode(const Type & v, LLNode * p, LLNode * n) :
      value(v), prev(p), next(n) {
    }

    //! Copy Constructor 
    LLNode(const LLNode & other) : 
    value(other.value),prev(other.prev),next(other.next) {
    }

    //!  Read-only public methods for use by clients of the LinkedList class
    Type & GetValue() {
      return value;
    }


    LLNode * GetPrevious()const {
      return prev;
    }

    LLNode * GetNext()const {
      return next;
    }

    //! Assignment operator 
    LLNode & operator=(const LLNode & other) {
      if(this!=&other) {
        value=other.value;
        prev=other.prev;
        next=other.next;
      }
      return *this;
    }

  private:
    Type value;        //!< value stored in the node
    LLNode * prev;            //!< pointer to previous node in the list
    LLNode * next;            //!< pointer to next node in the list
};


//! LinkedList implements a doubly-linked list
template <class Type>
class LinkedList {
  public:

    //!  No-arg constructor.  Initializes an empty linked list
    LinkedList();


    //!  Copy constructor.  Makes a complete copy of its argument
    LinkedList(const LinkedList & other);


    //!  Destructor
    ~LinkedList();


    //! Assignment operator.  Makes a complete copy of its argument
    //! @return A reference to oneself
    LinkedList& operator =(const LinkedList & other);


    //!  @return true if the list is empty, or false if the list is not empty
    bool IsEmpty() const;


    //!  Removes all values from the list
    void Clear();


    //!  @return the number of values in the list
    int GetSize() const;



    //!  @return a pointer to the first node in the list, or NULL if the list is empty
    LLNode<Type> * GetFirst()const;



    //!  @returns a pointer to the last node in the list, or NULL if the list is empty
    LLNode<Type> * GetLast()const;


    //!  Inserts value v into the list after node n
    //!  
    //!  @param v The new value being inserted
    //!  @param n A node that is already in the list after which the new node should 
    //!      be inserted.
    //!      If n is NULL, the new node should be inserted at the beginning of the list.
    //!
    //!  @return a pointer to the newly inserted node
    LLNode<Type> * Insert(const Type & v, LLNode<Type> * n = NULL);


    //! Searches for the first occurrence of value v that appears in the list 
    //!   after node n
    //!   
    //!  @param v The value being searched for
    //!  @param n The node in the list after which the search should begin.
    //!      If n is NULL, the list should be searched from the beginning.
    //!
    //!  @return a pointer to the node containing v, or NULL if v is not found
    LLNode<Type> * Find(const Type & v, LLNode<Type> * n) const;


    //!  Removes node n from the list
    //!  
    //!  @param n The node being removed from the list
    void Remove(LLNode<Type> * n);


    /**
    *  Tests this class
    *
    *  @param os The output stream to write test results
    *  @return true if all tests pass; false otherwise
    */
    static bool Test (ostream & os);

  protected:
    
    //! Makes a deep copy of the linked list
    //!
    //! @param llCopy The linked list to be copied
    //!
    //! @return A reference to this linked list
    LinkedList& copy (const LinkedList & llCopy);


    // Deallocates memory used by LinkedList and puts members in default state
    void free ();

  private:
    LLNode<Type>* head; //! Head of the linked list
    LLNode<Type>* tail; //! Tail of the linked list
    int size;     //! Size of the linked list

    //! Recursive method to help the copy method
    //!
    //! @param node The current node to be copied
    void recursiveCopy (LLNode<Type>* node);


    // frees memory allocated by this LinkedList object
    void freeLL (LLNode<Type>* node);
};


template <class Type>
LinkedList<Type>::LinkedList() : head(NULL), tail(NULL), size(0) {
}

template <class Type>
LinkedList<Type>::LinkedList(const LinkedList<Type> & other) {
  copy(other);
}

template <class Type>
LinkedList<Type>::~LinkedList() {
  free();
}

template <class Type>
LinkedList<Type>& LinkedList<Type>::operator =(const LinkedList<Type> & other) {
  free();
  return copy(other);
}

template <class Type>
bool LinkedList<Type>::IsEmpty() const {
  return (0 == size);
}

template <class Type>
void LinkedList<Type>::Clear() {
  free();
}

template <class Type>
int LinkedList<Type>::GetSize() const {
  return size;
}

template <class Type>
LLNode<Type> * LinkedList<Type>::GetFirst() const {
  return head;
}

template <class Type>
LLNode<Type> * LinkedList<Type>::GetLast() const {
  return tail;
}

template <class Type>
LLNode<Type> * LinkedList<Type>::Insert(const Type & v, LLNode<Type> * n) {
  LLNode<Type>* current = head;
  LLNode<Type>* newNode = NULL;
  if (NULL == current) { // this is the first node added to the list
    newNode = new LLNode<Type>(v, NULL, NULL);
    head = newNode;
    tail = newNode;
  } else if (NULL == n) { // insert at beginning of list
    newNode = new LLNode<Type>(v, NULL, head);
    head->prev = newNode;
    head = newNode;
  } else {
    while (current->value != n->value) {
      current = current->next;
    }
    newNode = new LLNode<Type>(v, current, current->next);
    if (NULL == (current->next)) { // insert at end of list
      current->next = newNode;
      tail = newNode; 
    } else { // normal insertion
      current->next->prev = newNode;
      current->next = newNode;
    }
  }
  size++;
  return newNode;
}

template <class Type>
LLNode<Type> * LinkedList<Type>::Find(const Type & v, LLNode<Type> * n) const {
  LLNode<Type>* current = head;
  if (NULL == head) { return NULL; }
  if (NULL != n) {
    while (current->value != n->value) {
      current = current->next;
    }
    current = current->next;
  }
  if (NULL == current) { return NULL; }
  while (current->value != v) {
    current = current->next;
    if (NULL == current) { break; }
  }
  return current;
}

template <class Type>
void LinkedList<Type>::Remove(LLNode<Type> * n) {
  if (NULL == n) { return; }
  if (NULL != n->next) {
    n->next->prev = n->prev;
  } else { // tail needs adjusting
    tail = n->prev; 
  }
  if (NULL != n->prev) {
    n->prev->next = n->next;
  } else { // head needs adjusting
    head = n->next;
  }
  size--;
  delete n;
}

template <class Type>
bool LinkedList<Type>::Test (ostream & os) {
  bool success = true;

  Type myType;

  LinkedList<Type> linkedList;
  TEST(linkedList.IsEmpty() == true);

  linkedList.Insert(myType);
  TEST(linkedList.GetSize() == 1);

  return success;
}


template <class Type>
void LinkedList<Type>::recursiveCopy (LLNode<Type>* node) {
  if (NULL == node) { return; }
  this->Insert(node->value, tail);
  recursiveCopy(node->next); 
}

template <class Type>
LinkedList<Type>& LinkedList<Type>::copy (const LinkedList<Type> & llCopy) {
  if (this != &llCopy) {
    head = NULL;
    tail = NULL;
    size = 0;
    this->recursiveCopy(llCopy.head);
  }
  return *this;
}

template <class Type>
void LinkedList<Type>::freeLL (LLNode<Type>* node) {
  if (NULL == node) { return; }
  LLNode<Type>* next = node->next;
  delete node;
  freeLL(next);
}


template <class Type>
void LinkedList<Type>::free () {
  freeLL(head);
  head = NULL;
  tail = NULL;
  size = 0;
}


#endif

