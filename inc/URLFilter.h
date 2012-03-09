#ifndef _URL_FILTER_H_
#define _URL_FILTER_H_

#include <string>
#include <iostream>

#include "URL.h"

using namespace std;

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
     *  Overloaded constructor
     *
     *  @param IN `startURL` The starting web site of the crawler
     */
    URLFilter (URL & start);


    /**
     *  Checks whether a URL is acceptable to index
     *
     *  @param url The url to be checked
     *
     *  @return false if url is in the scope of the starting web site, is valid
     *          html and has not been indexed previously; true otherwise 
     */
    bool filter (const URL & url);


    /**
     *  Unit test for this class
     *
     *  @param `os` The output stream
     *  @return true if all tests pass; false otherwise
     */
    static bool Test (ostream & os);

  private:

    // The start website for the web crawler
    URL startURL;


    /**
     *  Checks if `fileName` has a specific extension
     *
     *  @param `fileName` The file whose extension we are examining
     *  @return true if `fileName` contains a specific extension; false otherwise
     */
    bool checkExtension (string & fileName);
};

#endif

