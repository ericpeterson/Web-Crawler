#ifndef _SET_H_
#define _SET_H_

#include <iostream>
#include "BST.h"
#include "UnitTest.h"

// Implemented from the inherited binary search tree (BST) class
// Add elements to this set
// Remove elements from this set
// Static test method
template <class Key>
class Set : public BST<Key> {
  public:

    // Default constructor
    Set ();


    /**
     *  Copy constructor
     *
     *  @param sCopy A reference to the Set object to be copied
     */
    Set (const Set & sCopy);


    // Destructor
    ~Set ();


    /**
     *  Overloaded assignment operator
     *
     *  @param sCopy The Set object to be copied
     *  @return A reference to this Set object
     */
    Set & operator = (const Set & sCopy);


    /**
     *  Inserts a value v into the Set. Duplicates are not allowed.
     *
     *  @param v The new value being inserted
     *  @return true if v was added; false otherwise.
     */
    bool Insert (const Key & v);


    /**
     *  Removes a value v from the Set.
     *
     *  @param v The value being removed
     *  @return true if v was removed; false otherwise.
     */
    bool Remove (const Key & v);


    /**
     *  Checks if a value v is in this set
     *
     *  @param v The value to be checked
     *  @return true if the value is in the set; false otherwise
     */
    bool Contains (const Key & v);


    /**
     *  Unit test for this class
     *
     *  @param os The output stream to write test results
     *  @return true if all test cases pass; false otherwise
     */
    static bool Test (ostream & os);

  protected:

    /**
     *  Makes a deep copy of a Set object
     *
     *  @param sCopy The Set object to be copied
     */
    Set & copy (const Set & sCopy);


    /**
     *  Deallocates any heap memory used by this Set object
     */
    void free ();


  private:

    /**
     *  Balances the underlying binary search tree of this Set. This maintains
     *  a log(N) lookup time.
     */
    void balanceTree ();


};


template <class Key>
Set<Key>::Set() : BST<Key>::BST() {}


template <class Key>
Set<Key>::Set (const Set<Key> & sCopy) {
  copy(sCopy);
}


template <class Key>
Set<Key> & Set<Key>::operator = (const Set<Key> & sCopy) {
  free();
  return copy(sCopy);
}


template <class Key>
Set<Key>::~Set() {
  free();
}


template <class Key>
bool Set<Key>::Test (ostream & os) {
  bool success = true;

  Set<Key> set;
  TEST(set.IsEmpty() == true);
  TEST(set.GetRoot() == NULL);

  return success;
}


template <>
bool Set<int>::Test (ostream & os) {
  bool success = true;
  const int NUM_VALUES = 10;
  int testValues[NUM_VALUES] = {15, 22, 42, 1, 7, 4, 13, 19, 21, 5};

  Set<int> set;
  Set<int> set2 = set;

  for (int i = 0; i < NUM_VALUES; i += 1) {
    set.Insert(testValues[i]);
  }

  TEST(set.GetSize() == NUM_VALUES);
  TEST(set.Contains(1) == true);
  TEST(set.Contains(19) == true);
  TEST(set.Contains(22) == true);
  TEST(set.Contains(3) == false);

  set.Insert(3);
  TEST(set.Contains(3) == true);

  set.Remove(22);
  TEST(set.Contains(22) == false);
  TEST(set.GetSize() == NUM_VALUES);

  bool inserted = set.Insert(5);
  TEST(inserted == false);
  inserted = set.Insert(42);
  TEST(inserted == false);
  inserted = set.Insert(1);
  TEST(inserted == false);

  return success;
}



template <class Key>
bool Set<Key>::Insert (const Key & v) {
  BSTNode<Key>* nodeInserted = BST<Key>::Insert(v);
  bool nodeWasInserted = true;

  if (NULL == nodeInserted) {
    nodeWasInserted = false;
  }

  balanceTree();

  return nodeWasInserted;
}


template <class Key>
bool Set<Key>::Remove (const Key & v) {
  bool nodeWasRemoved = BST<Key>::Remove(v);

  balanceTree();

  return nodeWasRemoved;
}


template <class Key>
bool Set<Key>::Contains (const Key & v) {
  BSTNode<Key>* found = BST<Key>::Find(v);
  bool valueInSet = true;

  if (found == NULL) {
    valueInSet = false;
  }

  return valueInSet;
}


template <class Key>
void Set<Key>::balanceTree () {
  // TODO: implement a balanced tree if performance is unacceptable
}


template <class Key>
Set<Key> & Set<Key>::copy (const Set<Key> & sCopy) {
  BST<Key>::copy(sCopy);
  return *this;
}


template <class Key>
void Set<Key>::free () {
  BST<Key>::free();
}

#endif
