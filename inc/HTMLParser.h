#ifndef _HTML_PARSER_H_
#define _HTML_PARSER_H_

#include <iostream>
#include <string>

#include "WordIndex.h"
#include "PageQueue.h"
#include "StopWords.h"

#include "URLInputStream.h"
#include "HTMLToken.h"

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
     *  Checks if the current tag should be ignored (script tag)
     *  
     *  @param IN `currentTag` The tag being examined
     *  @return true if this tag should be ignored (script tag); false otherwise
     */   
    bool checkTag (string & currentTag);


    /**
     *  Inserts `currentWord` into the words map
     *
     *  @param IN `currentURL` The URL to associate with `currentWord`
     *  @param OUT `currentWord` The word to insert into the map
     *  @param OUT `words` The WordIndex map where the word will be inserted
     */
    void insertWord (string & currentURL, string & currentWord, WordIndex & words);


    /**
     *  Index the words in a <title> or <body> tag within <html> tag
     *  
     *  @param IN `currentToken` The current html token in parsing
     *  @param IN `currentURL` The web page that will be mapped to the word
     *    (on which the word was found)
     *  @param OUT `words` The Map of words already indexed
     */
    void indexWords (HTMLToken & currentToken, string & currentURL, WordIndex & words); 


    /**
     *  Sets appropriate booleans for start tags and parses links
     *
     *  @param IN `currentToken` The current HTML token in parsing
     *  @param IN `currentURL` The web page that will be mapped to the word
     *    (on which the word was found)
     *  @param IN-OUT `currentTag` The current html tag we are parsing
     *  @param IN-OUT `inBody` Boolean that tells that we are in <body> tag
     *  @param IN-OUT `inHTML` Boolean that tells that we are in <html> tag
     *  @param IN-OUT `inTitle` Boolean that tells that we are in <title> tag
     *  @param OUT `unprocessedPages` The queue of pages yet to be indexed
     */
    void configureTagStart (
        HTMLToken & currentToken
      , string & currentURL
      , string & currentTag
      , bool & inBody
      , bool & inHTML
      , bool & inTitle
      , PageQueue & unprocessedPages
    ); 


    /**
     *  Sets appropriate booleans for end tags
     *
     *  @param IN `currentToken` The current HTML token in parsing
     *  @param OUT `currentTag` The current html tag we are parsing
     *  @param OUT `inBody` Boolean that tells that we are in <body> tag
     *  @param OUT `inHTML` Boolean that tells that we are in <html> tag
     *  @param OUT `inTitle` Boolean that tells that we are in <title> tag
     *  @param OUT `ignoreCurrentTag` Boolean that tells us to ignore script tags
     */
    void configureTagEnd (
        const HTMLToken & currentToken
      , string & currentTag
      , bool & inBody
      , bool & inHTML
      , bool & inTitle
      , bool & ignoreCurrentTag
    );


    /**
     *  Verifies that we need to index words
     *
     *  @param IN `inBody` Boolean that tells that we are in <body> tag
     *  @param IN `inHTML` Boolean that tells that we are in <html> tag
     *  @param IN `inTitle` Boolean that tells that we are in <title> tag
     *  @param IN `currentToken` The current HTML token in parsing
     *  @param IN `currentURL` The current URL being parsed
     *  @param IN `words` The continuing word index for the web crawler
     */
    void checkToIndexWords (
        const bool & inBody
      , const bool & inHTML
      , const bool & inTitle
      , HTMLToken & currentToken
      , string & currentURL
      , WordIndex & words
    );


    /**
     *  Determines whether we should use the title for the description of a web page
     *
     *  @param IN `currentTag` The current html tag we are parsing
     *  @param IN `gotDescription` A boolean indicating when the description is complete
     *  @param IN `inHTML` Boolean that tells that we are in <html> tag
     *  @param IN `ignoreCurrentTag` Boolean that tells us to ignore script tags
     */
    bool shouldWeUseTitle (
        const string & currentTag
      , const bool gotDescription
      , const bool inHTML
      , const bool ignoreCurrentTag
    ) const;


    /**
     *
     *
     *  @param IN `currentToken` The current html token in parsing
     *  @param IN `descrLength` The max length of web page description
     *  @param IN-OUT `charCount` Keeps track of how many characters are used
     *    in web page description.
     *  @param OUT `description` The web page description
     *  @param OUT `gotDescription` A boolean indicating when the description is complete
     */   
    void buildDescription (
        HTMLToken & currentToken
      , const int & descrLength
      , int & charCount
      , string & description
      , bool & gotDescription
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
