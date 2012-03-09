#ifndef _HTML_PARSER_H_
#define _HTML_PARSER_H_

#include <iostream>
#include <string>
#include "URLInputStream.h"
#include "WordIndex.h"
#include "PageQueue.h"
#include "StopWords.h"
using namespace std;

typedef string Description;

/**
 *  Parses the downloaded HTML document
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Parses words, links, and description from HTML pages
 *    * Populate word index
 */
class HTMLParser {
  public:


    /**
     *  Initializes an HTMLParser object with an already downloaded HTML stream
     *  @param IN `base` The base URL of the Web Crawler
     *  @param IN `stopFile` The file name of the stop words
     */
    HTMLParser (string & base, string & stopFile);


    // Alternate version of constructor
    HTMLParser (string & base, const char* stopFile);


    /**
     *  Destructor
     */
    ~HTMLParser ();


    /**
     *  Copy Constructor
     *
     *  @param hpCopy The HTMLParser object to be copied
     */
    HTMLParser (const HTMLParser & hpCopy);


    /**
     *  Overloaded assignment operator
     *
     *  @param hpCopy The HTMLParser object to be copied
     *
     *  @return A reference to this HTMLParser
     */
    HTMLParser & operator = (const HTMLParser & hpCopy);


    /**
     *  Parses the HTML document into a description, words and links
     *
     *  @param IN `currentURL` The current URL being parsed
     *  @param IN `document` A stream of the html document to be parsed
     *  @param OUT `description` The description of the current web page. Used
     *    in the XML output.
     *  @param OUT `words` The continuing word index for the web crawler
     *  @param OUT `unprocessedPages` A list of pages that have not been indexed
     */
    void parse (
        string & currentURL
      , URLInputStream & document 
      , Description & description
      , WordIndex & words
      , PageQueue & unprocessedPages
    );


    /**
     *  Unit test for this class
     * 
     *  @param `os` The output stream where test result is sent
     *  @return true if all tests pass; false otherwise
     */
    static bool Test (ostream & os);

  private:

    // Base URL for the webcrawler
    string baseURL;

    // Words that should not be indexed
    StopWords stopWords;


    /**
     *  Determines if a char is a word character
     *
     *  @param IN `character` The char under examination
     *  @return true if `character` is a word character; false otherwise
     */
    static bool isWordCharacter (char character);


    /**
     *  Deallocates heap memory used by this HTMLParser
     */
    void free ();
};

#endif
