#ifndef _WEB_CRAWLER_H_
#define _WEB_CRAWLER_H_

#include <string>
#include "URL.h"

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

    URL startURL;
    FileName output;
    FileName stopWord;

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
}

#endif
