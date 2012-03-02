#ifndef _MAP_H_
#define _MAP_H_

#include "Set.h"

/**
 *  Maps objects of type Key to objects of type Value
 */
template <class Key, class Value>
class Map : public Set<Key> {
  public:

    // Default constructor
    Map ();


    /**
     *  Copy constructor
     *
     *  @param mCopy A reference to the Map object to be copied
     */
    Map (const Map & mCopy);


    // Destructor
    ~Map ();


    /**
     *  Overloaded assignment operator
     *
     *  @param mCopy A reference to the Map object to be copied
     *  @return A reference to this Map object
     */
    Map & operator = (const Map & mCopy);


  private:


    /**
     *  Makes a deep copy of a Map object
     *
     *  @param mCopy A reference to the Map object to be copied
     */
    Map & copy (const Map & mCopy);


    // Deallocates heap memory used by this Map object
    void free ();
};


template <class Key, class Value>
Map<Key, Value>::Map () : Set<Key>::Set() {}


template <class Key, class Value>
Map<Key, Value>::Map (const Map & mCopy) {
  copy(mCopy);
}


template <class Key, class Value>
Map<Key, Value>::~Map () {
  Set<Key>::~Set();
}


template <class Key, class Value>
Map<Key, Value> & Map<Key, Value>::operator = (const Map & mCopy) {
  free();
  return copy();
}


template <class Key, class Value>
Map<Key, Value> & Map<Key, Value>::copy (const Map & mCopy) {
  return Set<Key>::copy(mCopy);
}


#endif
