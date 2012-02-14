#ifndef _URL_H_
#define _URL_H_

#include <string>
using namespace std;


/**
 *  Stores url and web page description
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Store the URL and description for a page
 *    * Resolve relative URLs
 */
class URL {
  public:

    /**
     *  Default constructor
     */
    URL ();


    /**
     *  Destructor
     */
    ~URL ();


    /**
     *  Copy constructor
     *
     *  @param uCopy The URL object to be copied
     */
    URL (const URL & uCopy);


    /**
     *  Overloaded assignment operator
     *
     *  @param uCopy The URL object to be copied
     *
     *  @return A reference to this URL object
     */
    URL & operator = (const URL & uCopy);


    /**
     *  Resolves relative URL to the starting URL of the web crawler
     *
     *  @param relative The relative url to be resolved
     *
     *  @return The absolute, resolved URL
     */
    string resolve (string relative);

  private:

    // The string representation of the url
    string url;

    // The URL page's description that will be used in XML output
    string description;

    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *  @param uCopy The URL object to be copied
     *
     *  @return A reference to this URL
     */
    URL & copy (const URL & uCopy);


    /**
     *  Deallocates heap memory used by this URL
     */
    void free ();
};

#endif

