#ifndef _OCCURRENCE_H_
#define _OCCURRENCE_H_

#include <iostream>
#include "URL.h"

class Occurrence {
  public:

    /**
     *  Overloaded constructor
     *
     *  @param IN `site` The url in which a word is found
     *  @param IN `occurrences` The number of times the word appeared. Defaults to 0.
     */
    Occurrence (URL site, int occurrences = 0);


    /**
     *  Copy Constructor
     *
     *  @param `oCopy` A reference to the Occurrence object to be copied
     */
    Occurrence (const Occurrence & oCopy);


    // Destructor
    ~Occurrence ();


    /**
     *  Overloaded assignment operator
     *
     *  @param `oCopy` A reference to the Occurrence object to be copied
     *  @return A reference to this Occurrence object
     */
    Occurrence & operator = (const Occurrence & oCopy); 


    // increments `count` by 1
    void increment ();


    // getter for `count`
    int getCount () const;


    // getter for `url`
    URL & getURL () const; 


    /**
     *  Unit test for this class
     *
     *  @param `os` The output stream where the result will be sent
     *  @return true if all tests pass; false otherwise
     */
    static bool Test (ostream & os);

  private:
    URL url;
    int count;

    /**
     *  Makes a deep copy of this Occurrence
     *
     *  @param `oCopy` A reference to the Occurrence object to be copied
     *  @return A reference to this Occurrence object
     */
    Occurrence & copy (const Occurrence & oCopy);


    // Deallocate heap memory used by this Occurrence
    void free ();
};

#endif
