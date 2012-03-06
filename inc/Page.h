#ifndef _PAGE_H_
#define _PAGE_H_

#include <string>
#include <iostream>
#include "URL.h"

using namespace std;

// Class responsibilites:
//   * store web page url and description 
class Page {
  public:


    /**
     *  Default constructor.
     */   
    Page ();


    /**
     *  Overloaded constructor
     */
    Page (string base, string relative, string descr = "");


    /**
     *  Destructor
     */
    ~Page ();


    /**
     *  Copy constructor. Makes a deep copy of a Page object
     *
     *  @param pageCopy The Page object to be copied
     */
    Page (const Page & pageCopy);


    /**
     *  Overloaded assignment operator
     *  
     *  @param pageCopy The Page object to be copied
     *  @return A reference to this Page object
     */
    Page & operator = (const Page & pageCopy);


    /**
     *  Overloaded does not equal operator
     *  
     *  @param `pageCopy` The Page object to be compared
     *  @return true this Page does not equal pageCopy; false otherwise
     */
    bool operator != (const Page & pageCopy) const;


    // setter method
    void setDescription (string pageDescription);


    // Overloaded < operator. This is used in collections requiring comparator
    // operators.
    //
    // @return true if this page is less than `page`; false otherwise
    bool operator < (const Page & page) const;


    /**
     *  Tests the methods of this class. This automated testing will help in
     *  regression testing.
     *
     *  @param os The output stream to which the test output will be written
     *
     *  @return true if all tests pass; false otherwise.
     */
    static bool Test (ostream & os);


  private:

    // The absolute url to this Page
    URL url;

    // The URL page's description that will be used in XML output
    string description;
   

    /**
     *  Makes a deep copy of a Page object
     *
     *  @param pageCopy The Page object to be copied
     *  @return A reference to this Page object
     */
    Page & copy (const Page & pageCopy);


    /**
     *  Deallocates any heap memory used by this Page object
     */
    void free ();
};

#endif
