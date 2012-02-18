#ifndef _URL_H_
#define _URL_H_

#include <string>
#include <iostream>
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
     *  Overloaded constructor. Use this constructor except when creating a URL
     *  object for the start URL.
     *
     *  @param url The string representation of this url
     *
     *  @param baseURL The base URL to which url will be resolved, if necessary
     */
    URL (string url, string baseURL);


    /**
     *  Start URL constructor. Use this constructor only for the Start URL or
     *  an absolute URL.
     *
     *  @param absoluteURL The absolute URL (typically the start URL)
     */
    URL (string absoluteURL);


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
     *  Tests the methods of this class. This automated testing will help in
     *  regression testing.
     *
     *  @param os The output stream to which the test output will be written
     *
     *  @return true if all tests pass; false otherwise.
     */
    static bool Test (ostream & os);


    void setDescription (string urlDescription);


  private:

    // The entire url except the page name
    string prefix;

    /* 
      The name of the web page (minus the prefix). i.e. The page name of the
      URL http://www.google.com/apps/myCoolApp.html is `myCoolApp.html` 
    */
    string pageName;

    // The URL page's description that will be used in XML output
    string description;
    
    // A leftover global variable from the original url resolver code
    char* relativePtr;


    /**
     *  Parses a url into its prefix and page name. For example,
     *
     *    url - http://www.google.com/apps/myCoolApp.html
     *    prefix - http://www.google.com/apps/
     *    page name - myCoolApp.html
     *
     *  @param IN url The absolute url to parse. This can have http:// or file:// protocol.
     *
     *  @param OUT urlPrefix The prefix of url.
     *
     *  @param OUT urlPageName The page name of url.
     */
    void parseURL (string url, string & urlPrefix, string & urlPageName) const;


    /**
     *  Resolves this URL to the starting URL of the web crawler. Resolving
     *  a URL involves transforming a relative path into a complete URL in
     *  reference to some base URL. For example,
     *
     *    base URL - http://www.lds.org/en/scriptures/
     *  
     *    relative URL - ../ensign.html 
     *
     *    resolved URL - http://www.lds.org/en/ensign.html
     *
     *  For more information on URL resolving, see 
     *    http://students.cs.byu.edu/~cs240ta/winter2012/projects/URLResolver.pdf
     *
     *  @param baseURL The base URL to which the this URL will be resolved
     *  
     *  @param relativeURL The relative URL to be resolved
     *
     *  @return The absolute, resolved URL
     */
    char* resolve (char* baseURL, char* relativeURL) const;


    /**
     * Helper function for resolve(). Handles the dot case.
     *
     * @param basePtr The moving pointer at the tail end of the base url
     * @param baseLength The length of the base url (in characters)
     * @param relativeLength The length of the relative url (in characters)
     */
    char* doDotCase (char* basePtr, int baseLength, int relativeLength);


    /**
     *  Helper function for resolve. Handles the forward slash case.
     *
     *  @param absoluteURLLength The maximum length for the absolute url
     *  @param baseURL The base url
     *  @return The modified base url to pre-pend to the relative url 
     */
    char* doSlashCase (int absoluteURLLength, const char* baseURL);


    /**
     *  Helper function for resolve(). This creates a pointer that points at the
     *  current directory (./) relative to the base document.
     *
     *  @param baseLength The number of characters in the base url
     *  @param basePtr The pointer to the base url string 
     *  @return the adjusted base pointer
     */
    char* calculateBasePtr (int baseLength, char* basePtr);


    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *
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

