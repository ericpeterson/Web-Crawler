#ifndef _PAGE_SET_H_
#define _PAGE_SET_H_

#include <ostream>
#include "Page.h"
#include "Set.h"

typedef int Size;

/**
 *  Stores the pages already indexed by the Web Crawler
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Keep track of already indexed pages
 */
class PageSet : Set<Page> {
  public:

    /**
     *  Default constructor
     */
    PageSet ();


    /**
     *  Destructor
     */
    ~PageSet ();


    /**
     *  Copy constructor
     *  
     *  @param psCopy The PageSet object to be copied
     */
    PageSet (const PageSet & psCopy);


    /**
     *  Overloaded assignment operator
     *
     *  @param psCopy The PageSet object to be copied
     *  
     *  @return A reference to this PageSet object
     */
    PageSet & operator = (const PageSet & psCopy);


    /**
     *  Checks whether this PageSet is empty
     *
     *  @return true if set is empty; false otherwise
     */
    bool isEmpty();


    /**
     *  Unit test for this class
     *
     *  @param `os` A reference to the output stream where test results will be sent
     *  @return true if all tests pass; false otherwise
     */
    static bool Test (ostream & os);


    /**
     *  Checks if a value is in this PageSet
     *
     *  @param `val` The value to be checked
     *  @return true if `val` is in PageSet; false otherwise
     */
    bool Contains (const Page & val) const;

    
    /**
     *  Inserts a value v into the PageSet. Duplicates are not allowed.
     *
     *  @param IN `v` The new value being inserted
     *  @return true if v was added; false otherwise.
     */
    bool Insert (const Page & v);

  private:

    // Size of this PageSet
    Size size;

    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *  @param psCopy The PageSet object to be copied
     *
     *  @return A reference to this PageSet
     */
    PageSet & copy (const PageSet & psCopy);


    /**
     *  Deallocates heap memory used by this PageSet
     */
    void free ();
};

#endif

