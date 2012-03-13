#include <string>
#include <iostream>
#include <exception>
#include <cstdlib>

#include "Array.h"

#include "UnitTest.h"

using namespace std;


// An abstraction for length and capacity's type
typedef unsigned int ArraySize;


Array::Array (ArraySize maxLength) : length(0), capacity(maxLength) {
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


Array & Array::operator = (const Array & arr) {
  free();
  return copy(arr);
}


void Array::Push (const char* value) {
  string valueStr = value;
  Push(valueStr);
}


void Array::Push (const string & value) {
  ArraySize index = this->length;
  this->elements[index] = value;

  this->length++;

  // Array is full -- needs to increase capacity
  if (this->length == this->capacity) {
    IncreaseCapacity(MULT_FACTOR);
  }
}


bool Array::Contains (const char* value) const {
  string valueStr = value;
  return Contains(valueStr);
}


bool Array::Contains (const string & value) const {
  string key = value;
  string* base = this->elements;
  size_t num = this->length;
  int (*comparator)(const void*, const void*) = Compare;

  string* result = (string*)bsearch(&key, base, num, sizeof(string), comparator);

  // return true if `value` is found; false otherwise
  bool containsValue = (NULL != result) ? true : false;

  return containsValue;
}


ArraySize Array::GetLength () const {
  return this->length;
}


string* Array::GetElements () const {
  return this->elements;
}


bool Array::Test (ostream & os) {
  bool success = true;

  Array arr;

  TEST(arr.elements != NULL);
  TEST(arr.length == 0);
  TEST(arr.capacity == DEFAULT_CAPACITY);

  const ArraySize CAP = 5;
  Array arr2(CAP);

  TEST(arr2.elements != NULL);
  TEST(arr2.length == 0);
  TEST(arr2.capacity == CAP);

  const ArraySize TEST = 200;
  for (ArraySize i = 0; i < TEST; i++) {arr2.Push("I know my abc's");}
 
  TEST(arr2.length == TEST);
  TEST(arr2.capacity == (CAP*MULT_FACTOR*MULT_FACTOR));

  arr.Push("a");
  arr.Push("be");
  arr.Push("cat");
  arr.Push("dog");
  arr.Push("elephant");
  arr.Push("ferret");
  arr.Push("goat");
  arr.Push("house");
  arr.Push("igloo");

  TEST(arr.length == 9);
  TEST(arr.capacity == DEFAULT_CAPACITY);
  TEST(arr.Contains("a"));
  TEST(arr.Contains("be"));
  TEST(arr.Contains("cat"));
  TEST(arr.Contains("dog"));
  TEST(arr.Contains("elephant"));
  TEST(arr.Contains("ferret"));
  TEST(arr.Contains("goat"));
  TEST(arr.Contains("house"));
  TEST(arr.Contains("igloo"));
  TEST(!arr.Contains(""));
  TEST(!arr.Contains("Eric"));
  TEST(!arr.Contains("%$%$@#jasfj;qwoeij;;akdjIIJIJOIJ||ej1214938u54083u**(*3"));

  Array arr3(arr);
  TEST(&arr3.elements != &arr.elements);
  TEST(arr3.length == arr.length);
  TEST(arr3.capacity == arr.capacity);
  TEST(arr3.Contains("dog"));

  arr3 = arr2;
  TEST(&arr3.elements != &arr2.elements);
  TEST(arr3.length == arr2.length);
  TEST(arr3.capacity == arr2.capacity);
  TEST(arr3.Contains("I know my abc's"));

  return success;
}


void Array::IncreaseCapacity (const short multiplyFactor) {
  ArraySize newCapacity = (this->capacity * multiplyFactor);
  ArraySize newLength = this->length;

  string* newElements = new string[newCapacity];
  string* oldElements = this->elements;

  // copy length old elements into larger array
  for (ArraySize i = 0; i < newLength; i++) {
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
    ArraySize arrCapacity = arr.capacity;
    ArraySize arrLength = arr.length;

    string* newElements = new string[arrCapacity];
    string* oldElements = arr.elements;

    // Copy elements to new array
    for (ArraySize i = 0; i < arrLength; i++) {
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
  ArraySize arrLength = arr.GetLength();
  string* arrElements = arr.GetElements();

  for(ArraySize i = 0; i < arrLength; i++) {
    os << arrElements[i] << endl;
  }

  return os;
}

