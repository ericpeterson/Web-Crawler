#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "UnitTest.h"

/**
 *  Queue data structure implemented from a LinkedList.
 */
template <class Type>
class Queue : public LinkedList<Type> {
  public:
    // Default constructor
    Queue ();


    /**
     *  Copy constructor
     *
     *  @param `qCopy` A reference to the Queue object to be copied
     */
    Queue (const Queue & qCopy);


    /**
     *  Destructor
     */
    ~Queue ();


    /**
     *  Overloaded assignment operator
     *
     *  @param `qCopy` A reference to the Queue object to be copied
     *  @return A reference to this Queue object
     */
    Queue & operator = (const Queue & qCopy);


    /**
     *  @return A pointer to the first value in the Queue if Queue has
     *    elements; NULL if Queue is empty
     */
    Type * front ();


    /**
     *  @return A pointer to the last value in the Queue if Queue has
     *    elements; NULL if Queue is empty
     */
    Type * back ();


    /**
     *  Insert a value to the front of the Queue
     *
     *  @param `value` The value to be pushed onto the Queue
     */
    void push (const Type & value);


    /**
     *  Removes last value from the Queue
     *
     *  @return The last value in Queue
     */
    Type pop ();


    /**
     *  @return The number of elements in this Queue
     */
    int size () const;


    /**
     *  Checks whether this Queue is empty or not.
     *
     *  @return true if the Queue is empty; false otherwise
     */
    bool empty () const;


    /**
     *  Unit test for the Queue class
     *
     *  @param `os` A reference to the output stream where the test result will
     *    be written
     *  @return true if all tests pass; false otherwise. 
     */
    static bool Test (ostream & os);

  protected:

    /**
     *  Makes a deep copy of this Queue
     *
     *  @param `qCopy` The Queue to be copied
     *  @return A reference to this Queue object
     */
    Queue & copy (const Queue & qCopy);


    /**
     *  Deallocates memory used by this Queue
     */
    void free ();
};


// Queue () - default constructor for LinkedList
template <class Type>
Queue<Type>::Queue () : LinkedList<Type>() {}


// Copy constructor - copy() LinkedList
template <class Type>
Queue<Type>::Queue (const Queue & qCopy) {
  LinkedList<Type>::copy(qCopy);
}


// Destructor - free() LinkedList
template <class Type>
Queue<Type>::~Queue () {
  LinkedList<Type>::free();
}


// Assignment operator - free() and copy() LinkedList
template <class Type>
Queue<Type> & Queue<Type>::operator = (const Queue & qCopy) {
  LinkedList<Type>::free();
  LinkedList<Type>::copy(qCopy);
  return *this;
}


// front () - GetFirst()->GetValue() LinkedList 
template <class Type>
Type * Queue<Type>::front () {
  LLNode<Type>* frontNode = LinkedList<Type>::GetFirst();
  Type* first = NULL;

  if(NULL != frontNode) {
    first = frontNode->GetValue(); 
  }

  return first;
}


// back () - GetLast()->GetValue() LinkedList
template <class Type>
Type * Queue<Type>::back () {
  LLNode<Type>* backNode = LinkedList<Type>::GetLast();
  Type* back = NULL;

  if (NULL != backNode) {
    back = backNode->GetValue();
  }

  return back;
}


// push () - Insert() LinkedList (no return value)
template <class Type>
void Queue<Type>::push (const Type & value) {
  LinkedList<Type>::Insert(value);
}


// pop () - GetLast() and Remove(LLNode*) LinkedList
template <class Type>
Type Queue<Type>::pop () {
  LLNode<Type>* lastValue = LinkedList<Type>::GetLast();
  Type value;

  if (NULL != lastValue) {
    value = lastValue->GetValue();
  }

  LinkedList<Type>::Remove(lastValue);

  return value;
}


// size () - GetSize() LinkedList
template <class Type>
int Queue<Type>::size () const {
  return LinkedList<Type>::GetSize();
}


// empty () - IsEmpty() LinkedList
template <class Type>
bool Queue<Type>::empty () const {
  return LinkedList<Type>::IsEmpty();
}


template <class Type>
bool Queue<Type>::Test (ostream & os) {
  bool success = true;
  Queue<Type> queue;

  TEST(queue.empty() == true);

  return success;
}


template <>
inline bool Queue<string>::Test (ostream & os) {
  bool success = true;

  Queue<string> queue;
  Queue<string> queue2;
  
  queue.push("This is cool");
  queue.push("Wicked Awesome");
  queue.push("I'm the man");

  queue2 = queue; 

  queue.push("This is unique to queue");
  queue2.push("I'm totally queue2");

  TEST(&queue != &queue2);
  TEST(queue.size() == queue2.size());

  TEST(queue.pop() == "This is cool");
  TEST(queue.pop() == "Wicked Awesome");
  TEST(queue.pop() == "I'm the man");
  TEST(queue.pop() == "This is unique to queue");
  TEST(queue.pop() == "");

  TEST(queue.empty() == true);

  TEST(queue2.pop() == "This is cool");
  TEST(queue2.pop() == "Wicked Awesome");
  TEST(queue2.pop() == "I'm the man");
  TEST(queue2.pop() == "I'm totally queue2");
  TEST(queue2.pop() == "");

  TEST(queue2.empty() == true);

  queue.pop();
  queue.pop();
  queue.pop();
  queue2.pop();
  queue2.pop();
  queue2.pop();

  TEST(queue.empty() == true);
  TEST(queue2.empty() == true);

  return success;
}


// copy () - copy() LinkedList
template <class Type>
Queue<Type> & Queue<Type>::copy (const Queue & qCopy) {
  LinkedList<Type>::copy(qCopy);
  return *this;
}


// free () - free() LinkedList
template <class Type>
void Queue<Type>::free () {
  LinkedList<Type>::free();
}

#endif
