#ifndef _URL_FILTER_H_
#define _URL_FILTER_H_

#include "URL.h"

/**
 *  Filters URLs before they are added to the processed pages collection.
 *  A URL will be filtered if:
 *
 *    * The URL is out of the scope of the starting web site
 *    * The URL's page is non-html
 *    * The URL has already been processed
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Distinguish between HTML and non-HTML links
 *    * Distinguish between in-scope and out-of-scope links
 */
class URLFilter {
  public:

    /**
     *  Default constructor
     */
    URLFilter ();


    /**
     *  Destructor
     */
    ~URLFilter ();


    /**
     *  Copy constructor
     *
     *  @param ufCopy The URLFilter object to be copied
     */
    URLFilter (const URLFilter & ufCopy);


    /**
     *  Overloaded assignment operator
     *  
     *  @param ufCopy The URLFilter object to be copied
     *
     *  @return A reference to this URLFilter object
     */
    URLFilter & operator = (const URLFilter & ufCopy);


    /**
     *  Checks whether a URL is acceptable to index
     *
     *  @param url The url to be checked
     *
     *  @return true if url is in the scope of the starting web site, is valid
     *          html and has not been indexed previously; false otherwise 
     */
    static bool filter (string & url);

  private:

    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *  @param ufCopy The URLFilter object to be copied
     *
     *  @return A reference to this URLFilter
     */
    URLFilter & copy (const URLFilter & ufCopy);


    /**
     *  Deallocates heap memory used by this URLFilter
     */
    void free ();
};

#endif

