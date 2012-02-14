#ifndef _WEB_CRAWLER_H_
#define _WEB_CRAWLER_H_

#include <string>
#include "URL.h"
#include "Status.h"
#include "PageQueue.h"
#include "PageSet.h"
#include "StopWords.h"
#include "WordIndex.h"

typedef string FileName;

/**
 *  The driver for the dowloading and indexing of documents
 */
class WebCrawler {
  public:
    
    /**
     *  Default constructor
     */
    WebCrawler ();


    /**
     *  Destructor
     */
    ~WebCrawler ();
    

    /**
     *  Copy Constructor
     *
     *  @param wcCopy The WebCrawler object to be copied
     */
    WebCrawler (const WebCrawler & wcCopy);


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
     *  @param startURL The starting URL
     *
     *  @param output The name of the file where the xml output will be written
     *
     *  @param stopWord File containing list of words that will not be indexed
     *
     *  @return The status of the indexing. S_OK if the crawling was
     *          successful. S_ERROR otherwise.
     */
    Status crawl (URL startURL, FileName output, FileName stopWord);

  private:

    // The starting URL of the web crawler
    URL startURL;

    // A collection of web pages yet to be indexed
    PageQueue unprocessedPages;

    // A set of pages that have already been processed. Helps prevent the same
    // page from indexed twice.
    PageSet processedPages;

    // A collection of words the indexer should ignore
    StopWords stopWords;

    // A mapping of the indexed words to their web pages. Used to generate XML output.
    WordIndex wordIndex;


    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *
     *  @param wcCopy The WebCrawler object to be copied
     *
     *  @return A reference to this WebCrawler
     */
    WebCrawler & copy (const WebCrawler & wcCopy);


    /**
     *  Deallocates heap memory used by this WebCrawler
     */
    void free ();
};

#endif
