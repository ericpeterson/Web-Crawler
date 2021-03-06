#ifndef _WEB_CRAWLER_H_
#define _WEB_CRAWLER_H_

#include <string>
#include <iostream>

#include "URL.h"
#include "PageSet.h"
#include "WordIndex.h"

using namespace std;

typedef string FileName;

/**
 *  The driver for the dowloading and indexing of documents
 *
 *  (TA Use) Class Responsibilities:
 *
 *    * Drive the overall crawling process
 */
class WebCrawler {
  public:
    
    /**
     *  Overloaded constructor
     *  
     *  @param IN `startURL` The start URL for this crawler
     */
    WebCrawler (URL & startURL);


    /**
     *  Copy Constructor
     *
     *  @param wcCopy The WebCrawler object to be copied
     */
    WebCrawler (const WebCrawler & wcCopy);


    // Destructor
    ~WebCrawler ();


    /**
     *  Overloaded assignment operator
     *
     *  @param wcCopy The WebCrawler object to be copied
     *
     *  @return A reference to this WebCrawler
     */
    WebCrawler & operator = (const WebCrawler & wcCopy);


    /**
     *  Download the start URL and begins indexing the words
     *
     *  @param IN `stopWord` File containing list of words that will not be indexed
     */
    void crawl (FileName & stopWord);


    /**
     *  Writes the web crawler results to an XML file
     *
     *  @param IN `output` The name of the file where the xml output will be written
     */
    void printXML (FileName & output);


    /**
     *  Unit test for this class
     *
     *  @param `os` The out stream we write results to
     *  @return true if all tests pass; false otherwise
     */
    static bool Test (ostream & os);

  private:

    // Start URL of this crawler
    URL startURL;

    // A set of pages that have already been processed. Helps prevent the same
    // page from indexed twice.
    PageSet processedPages;

    // A mapping of the indexed words to their web pages. Used to generate XML output.
    WordIndex wordIndex;
};

#endif
