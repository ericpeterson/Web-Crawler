#ifndef _STOP_WORDS_H_
#define _STOP_WORDS_H_

#include <string>
#include <iostream>

#include "Array.h"

using namespace std;

typedef string Word;

/**
 *  Loads and stores the stop words from a file into memory
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Load and store stop words
 */
class StopWords : public Array {
  public:

    /**
     *  Overloaded constructor
     *
     *  @param IN `file` The file containing the stop words
     */
    StopWords (const char* file);


    /**
     *  Destructor
     */
    ~StopWords ();


    /**
     *  Copy constructor
     *
     *  @param swCopy The StopWords object to be copied
     */
    StopWords (const StopWords & swCopy);


    /**
     *  Overloaded assignment operator
     *
     *  @param swCopy The StopWords object to be copied
     *
     *  @return A reference to this StopWords object
     */
    StopWords & operator = (const StopWords & swCopy);


    /**
     *  Unit test for the StopWords class
     *
     *  @param `os` A reference to the output stream where the test result will
     *    be written
     *  @return true if all tests pass; false otherwise. 
     */
    static bool Test (ostream & os);


    /**
     *  Checks if this Set contains a given word. This check is case-insensitive.
     *
     *  @param `word` The word to check
     *  @return true if the word is in the list; false otherwise
     */
    bool Contains (string & word) const;

    // Overloaded Contains()
    bool Contains (const char* word) const;

  private:

    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *  @param swCopy The StopWords object to be copied
     *
     *  @return A reference to this StopWords
     */
    StopWords & copy (const StopWords & swCopy);


    /**
     *  Deallocates heap memory used by this StopWords
     */
    void free ();
};

#endif
