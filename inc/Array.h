#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <string>
#include <iostream>


// An abstraction for length and capacity's type
typedef unsigned int ArraySize;


/*
  DEFAULT_CAPACITY - The default capacity of this Array if no other value is
    specified in the constructor.

  MULT_FACTOR - The factor by which the capacity of Array is increased
*/
enum {DEFAULT_CAPACITY = 50, MULT_FACTOR = 10};


/**
 *  A dynamic array for storing a list of string objects. This class will have
 *  nearly constant insertion time, because the array will have to be increased
 *  in size when its capacity is reached. Array should have constant access
 *  time, which will be ideal for accessing the array quickly even with a large
 *  number of elements.
 */
class Array {

  public:

    /**
     *  Constructor
     *
     *  @param `maxLength` The initial capacity of this Array. Defaults to
     *    DEFAULT_CAPACITY.
     */
    Array (ArraySize maxLength = DEFAULT_CAPACITY);

	
    /**
     *  Copy constructor
     *
     *  @param `arr` The Array to be copied into this one
     */
    Array (const Array & arr);


    // Destructor
    ~Array ();


    /**
     *  Overloaded assignment operator
     *
     *  @param `arr` The Array to be copied into this one
     *  @return A reference to this Array
     */
    Array & operator = (const Array & arr);


    /**
     *  Overloaded version of Push()
     */
    void Push (const char* value);    


    /**
     *  Inserts `value` into the left-most, non-occupied slot in this Array
     *  until the capacity is reached. Then this Array's capacity increases.
     *
     *  @param `value` The new value to be inserted
     */
    void Push (const std::string & value);


    /**
     *  Overloaded version of Contains()
     */    
    bool Contains (const char* value) const;


    /**
     *  Uses a binary search algorithm to determine if `value` is in this Array.
     *
     *  @param `value` The new value to be inserted
     *  @return true if `value` is found in this Array; false otherwise.
     */
    bool Contains (const std::string & value) const;


    // @return The length of this Array
    ArraySize GetLength () const;


    // @return A pointer to the elements in this Array
    std::string* GetElements () const;


    /**
     *  Unit test for this class
     *
     *  @param `os` The output stream to which test results will be sent
     */
    static bool Test (std::ostream & os);

  protected:

    /**
     *  Deallocates heap memory used by this Array.
     */
    void free ();


    /**
     *  Makes a deep copy of an Array object
     *
     *  @param `arr` The Array to be copied
     *  @return A reference to this Array
     */
    Array & copy (const Array & arr);

  private:

    std::string* elements;
    ArraySize length;
    ArraySize capacity;


    /**
     *  Increases this Array's capacity by a factor of `multiplyFactor`
     *
     *  @param `multiplyFactor` The factor by which this Array's capacity will
     *    be increased
     */
    void IncreaseCapacity (const short multiplyFactor);




};


/**
 *  Compares `key` and an element of this Array.
 *
 *  @param `key` Pointer to value being searched for
 *  @param `element` Pointer to the current element in Array
 *  @return -1 if `key` is less than `element`. 1 if `key` is greater than
      `element`. 0 otherwise
 */
int Compare (const void* key, const void* element);


/**
 *  Overloaded insertion operator. Intended for debugging.
 *
 *  @param `os` The output stream to which `arr` will be written
 *  @param `arr` The Array object
 *  @return A reference to `os`
 */
std::ostream & operator << (std::ostream & os, const Array & arr);

#endif
