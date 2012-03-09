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
    Page (string base, string relative, string descr);


    /**
     *  Overloaded constructor -- use this for absolute urls
     *
     *  @param IN `absolute` URL of the Page
     *  @param IN `descr` Description of page defaults to ""
     */
    Page (string absolute, string descr = "");


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
    void setDescription (string & pageDescription);


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


    // Getter for `url`
    URL & getURL ();


    // Getter for `description`
    string & getDescription ();

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


/**
 *  Overloaded insertion operator
 *
 *  @param `stream` The stream where the page info will be written
 *  @param `page` The page whose information will be written to `stream`
 *  @return A reference to `stream`
 */
ostream & operator << (ostream & stream, Page & page);

#endif
