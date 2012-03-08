#ifndef _HTML_PARSER_H_
#define _HTML_PARSER_H_

#include <iostream>
#include <string>
#include "URLInputStream.h"
#include "WordIndex.h"
#include "Queue.h"
#include "Page.h"
#include "StopWords.h"
#include "UnitTest.h"
using namespace std;

typedef Queue<Page> LinksList;

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
     *  @param IN `base` The base URL
     *  @param IN `Url` The current URL being parsed
     *  @param IN `stop` The list of stop words
     */
    HTMLParser (URLInputStream & input, string & base, string & Url, StopWords & stop);


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

    // Current URL being parsed
    string currentURL;

    // Base URL for the webcrawler
    string baseURL;

    // Indexed words use in XML output
    WordIndex words;

    // Words that should not be indexed
    StopWords stopWords;

    // Links to potentially unprocessed pages. Pages from this collection will
    // be indexed if they have not been indexed before.
    LinksList links;


    // A stream of the html document to be parsed
    URLInputStream* document;


    /**
     *  Determines if a char is a word character
     *
     *  @param IN `character` The char under examination
     *  @return true if `character` is a word character; false otherwise
     */
    static bool isWordCharacter (char character);


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
