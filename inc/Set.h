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
     *  Unit test for this class
     *
     *  @param os The output stream to write test results
     *  @return true if all test cases pass; false otherwise
     */
    static bool Test (ostream & os);
};

template <class Key>
Set<Key>::Set() : BST<Key>::BST() {}


template <class Key>
bool Set<Key>::Test (ostream & os) {
  bool success = true;

  Set<Key> set;
  TEST(set.IsEmpty() == true);
  TEST(set.GetRoot() == NULL);

  return success;
}

#endif
