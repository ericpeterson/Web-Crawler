#ifndef _MAP_H_
#define _MAP_H_

#include "Set.h"
#include "CS240Exception.h"
#include "UnitTest.h"

template <class Key, class Value>
class MapNode;

/**
 *  Maps objects of type Key to objects of type Value
 */
template <class Key, class Value>
class Map : public Set< MapNode<Key, Value> > {
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


    /**
     *  Retrieves the value associated with a key
     *
     *  @param `key` The key whose value will be retrieved
     *  @return The value associated with `key` if it is in the Map; NULL otherwise
     *  @throws CS240Exception if `key` is not in this Map
     */
    Value GetValue (const Key & key) const;


    /**
     *  Inserts a key-value pair into the Map
     *
     *  @param `key` The identifying key
     *  @param `value` The value associated with `key`
     *  @return true if the key-value pair was inserted; false otherwise
     */
    bool Insert (Key key, Value value);


    /**
     *  Unit Test for Map class
     *
     *  @param `os` A reference to the output stream where test results will be sent
     *  @return true if all the tests passed; false otherwise.
     */
    static bool Test(ostream & os);


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
Map<Key, Value>::Map () : Set< MapNode<Key, Value> >::Set() {}


template <class Key, class Value>
Map<Key, Value>::Map (const Map & mCopy) {
  this->copy(mCopy);
}


template <class Key, class Value>
Map<Key, Value>::~Map () {
  this->free();
}


template <class Key, class Value>
Map<Key, Value> & Map<Key, Value>::operator = (const Map & mCopy) {
  this->free();
  return this->copy(mCopy);
}


template <class Key, class Value>
Map<Key, Value> & Map<Key, Value>::copy (const Map & mCopy) {
  Set< MapNode<Key, Value> >::copy(mCopy);
  return *this;
}


template <class Key, class Value>
void Map<Key, Value>::free () {
  Set< MapNode<Key, Value> >::free();
}


template <class Key, class Value>
Value Map<Key, Value>::GetValue (const Key & key) const {
  // Wrap `key` in a dummy MapNode object for input to Find()
  MapNode<Key, Value> mapNode(key, "");

  BSTNode< MapNode<Key, Value> > * node = BST< MapNode<Key, Value> >::Find(mapNode);

  if (NULL == node) {
    // `key` was not in Map -- throw exception
    throw CS240Exception("Key was not in Map");
  }

  return node->GetValue().value;
}


template <class Key, class Value>
bool Map<Key, Value>::Test(ostream & os) {
  bool success = true;

  Map<int, string> map;
  Map<int, string> map2;

  map.Insert(0, "hello");
  map.Insert(1, "hola");

  map2 = map;

  map.Insert(2, "reflejo");
  map2.Insert(2, "reflexion");

  // address of map should be different from map2
  TEST(&map != &map2);

  // sizes of map and map2 should be the same
  TEST(map.GetSize() == map2.GetSize());

  // Retrieve values based on keys
  TEST(map.GetValue(0) == "hello");
  TEST(map.GetValue(1) == "hola");
  TEST(map.GetValue(2) == "reflejo");
  TEST(map2.GetValue(0) == "hello");
  TEST(map2.GetValue(1) == "hola");
  TEST(map2.GetValue(2) == "reflexion");

  bool threwException = false; 
  // should throw an exception if key is not in Map
  try {
    map2.GetValue(100);
  } catch (CS240Exception e) {
    threwException = true;
  } catch (...) {
    // should never reach this point
    TEST(false);
  }

  TEST(threwException);

  return success;
}



/**
 *  A single Map element containing a key and a value.
 */
template <class Key, class Value>
class MapNode {
  friend class Map<Key, Value>;

  public:

    /**
     *  Constructor
     *
     *  @param `k` The key. This uniquely identifies the node and is used in sorting.
     *  @param `val` The value associated with `k`
     */ 
    MapNode (Key k, Value val);


    /**
     *  Copy constructor
     *
     *  @param `mnCopy` The MapNode object to be copied
     */
    MapNode (const MapNode & mnCopy);


    /**
     *  Overloaded assignment operator
     * 
     *  @param `mnCopy` The MapNode object to be copied
     *  @return A reference to this MapNode
     */
    MapNode & operator = (const MapNode & mnCopy);


    /**
     *  Overloaded less-than operator
     * 
     *  @param `node` The MapNode object to be compared to this MapNode object.
     *                The keys of the MapNode objects are used in the comparison.
     *  @return true if this MapNode object is less than `node`; false otherwise.
     */
    bool operator < (const MapNode & node) const;


    // returns `key` of this MapNode
    Key GetKey () const;

    // return `value` of this MapNode
    Value GetValue () const;

  private:

    // The unique identifier of this MapNode
    Key key;

    // The value associated with `key`
    Value value;
};


template <class Key, class Value>
MapNode<Key, Value>::MapNode (Key k, Value val) : key(k), value(val) {}


template <class Key, class Value>
MapNode<Key, Value>::MapNode (const MapNode & mnCopy) : key(mnCopy.key), value(mnCopy.value) {}


template <class Key, class Value>
MapNode<Key, Value> & MapNode<Key, Value>::operator = (const MapNode & mnCopy) {
  if (this != &mnCopy) {
    this->key = mnCopy.key;
    this->value = mnCopy.value;
  }

  return *this;
}


template <class Key, class Value>
bool MapNode<Key, Value>::operator < (const MapNode<Key, Value> & node) const {
  bool isLessThan = false;

  Key thisKey = this->key;
  Key nodeKey = node.key;

  if (thisKey < nodeKey) {
    isLessThan = true;
  }

  return isLessThan;
}


template <class Key, class Value>
Key MapNode<Key, Value>::GetKey () const {
  return key;
}


template <class Key, class Value>
Value MapNode<Key,Value>::GetValue () const {
  return value;
}


template <class Key, class Value>
bool Map<Key, Value>::Insert (Key key, Value value) {
  MapNode<Key, Value> node(key, value);
  return Set< MapNode<Key, Value> >::Insert(node);
}


#endif
