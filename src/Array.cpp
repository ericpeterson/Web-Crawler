#include <string>
#include <iostream>
#include <exception>
#include <cstdlib>

#include "Array.h"

#include "UnitTest.h"

using namespace std;


// An abstraction for length and capacity's type
typedef unsigned int Size;


Array::Array (Size maxLength) : length(0), capacity(maxLength) {
  // initialize elements on heap
  try {
    elements = new string[capacity];
  } catch (bad_alloc & ex) {
    cout << "Memory allocation failure. " << ex.what() << endl;
  } catch (exception & ex) {
    cout << ex.what() << endl;
  }
}


Array::Array (const Array & arr) : elements(NULL), length(0), capacity(0) {
  copy(arr);
}


Array::~Array () {
  free();
}


//	Array & Overloaded assignment operator(const Array &)
//		call free
//		return copy
Array & Array::operator = (const Array & arr) {
  free();
  return copy(arr);
}


void Array::Push (const string & value) {
  Size index = this->length;
  this->elements[index] = value;

  this->length++;

  // Array is full -- needs to increase capacity
  if (this->length == this->capacity) {
    IncreaseCapacity(MULT_FACTOR);
  }
}


bool Array::Contains (const string & value) {
  string key = value;
  string* base = this->elements;
  size_t num = this->length;
  int (*comparator)(const void*, const void*) = Compare;

  string* result = (string*)bsearch(&key, base, num, sizeof(string), comparator);

  // return true if `value` is found; false otherwise
  bool containsValue = (NULL != result) ? true : false;

  return containsValue;
}


Size Array::GetLength () const {
  return this->length;
}


string* Array::GetElements () const {
  return this->elements;
}


bool Array::Test (ostream & os) {
  bool success = true;
  return success;
}


void Array::IncreaseCapacity (const short multiplyFactor) {
  Size newCapacity = (this->capacity * multiplyFactor);
  Size newLength = this->length;

  string* newElements = new string[newCapacity];
  string* oldElements = this->elements;

  // copy length old elements into larger array
  for (Size i = 0; i < newLength; i++) {
    newElements[i] = oldElements[i];
  }

  free();

  this->elements = newElements;
  this->length = newLength;
  this->capacity = newCapacity;
}


void Array::free () {
  // put this Array into a default state
  delete[] elements;
  this->elements = NULL;
  this->length = 0; 
  this->capacity = 0; 
}


Array & Array::copy (const Array & arr) {
  if (this != &arr) {
    Size arrCapacity = arr.capacity;
    Size arrLength = arr.length;

    string* newElements = new string[arrCapacity];
    string* oldElements = arr.elements;

    // Copy elements to new array
    for (Size i = 0; i < arrLength; i++) {
      newElements[i] = oldElements[i];
    }

    this->elements = newElements;
    this->length = arrLength;
    this->capacity = arrCapacity;
  }

  return *this;
}


int Compare (const void* key, const void* element) {
  const string* keyPtr = static_cast<const string*>(key);
  const string* elementPtr = static_cast<const string*>(element);
  const string keyStr = *keyPtr;
  const string elementStr = *elementPtr;
  int result = 0;

  // result is 0 by default so there is no need for the == case
  if (keyStr < elementStr) {
    result = -1;
  } else if (elementStr < keyStr) {
    result = 1;
  }

  return result;
}


ostream & operator << (ostream & os, const Array & arr) {
  Size arrLength = arr.GetLength();
  string* arrElements = arr.GetElements();

  for(Size i = 0; i < arrLength; i++) {
    os << arrElements[i] << endl;
  }

  return os;
}


/*Array class for Stop Words
Empty Array
    empty string
    string of length 1
    string of length 2+

Array with 1 element
    empty string
    string of length 1
            one string in Array
            one string not in Array
    string of length 2+

Array with 2+ elements
    empty string
    string of length 1
    string of length 2+
            one string in Array
            one string not in Array

*/
