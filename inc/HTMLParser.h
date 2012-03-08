#ifndef _HTML_PARSER_H_
#define _HTML_PARSER_H_

#include <iostream>
#include <string>
#include "URLInputStream.h"
#include "WordIndex.h"
#include "Queue.h"
#include "URL.h"
#include "UnitTest.h"
using namespace std;

typedef Queue<URL> LinksList;

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
     *  Default constructor
     */
    HTMLParser ();


    /**
     *  Initializes an HTMLParser object with an already downloaded HTML stream
     *  @param IN `input` The stream from the downloaded page.
     */
    HTMLParser (URLInputStream & input);


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
     */
    void parse ();


    /**
     *  Getter for description
     */
    Description & getDescription ();


    /**
     *  Getter for words
     */
    WordIndex & getWords ();


    /**
     *  Getter for links
     */
    LinksList & getLinks ();


    /**
     *  Unit test for this class
     * 
     *  @param `os` The output stream where test result is sent
     *  @return true if all tests pass; false otherwise
     */
    static bool Test (ostream & os);

  private:

    // Web page description used in XML output
    Description description;

    // Indexed words use in XML output
    WordIndex words;

    // Links to potentially unprocessed pages. Pages from this collection will
    // be indexed if they have not been indexed before.
    LinksList links;


    // A stream of the html document to be parsed
    URLInputStream* document;

    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *  @param hpCopy The HTMLParser object to be copied
     *
     *  @return A reference to this HTMLParser
     */
    HTMLParser & copy (const HTMLParser & hpCopy);


    /**
     *  Deallocates heap memory used by this HTMLParser
     */
    void free ();
};

#endif
