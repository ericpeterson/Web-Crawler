#include <string>
#include <iostream>

#include "URL.h"
#include "HTMLParser.h"
#include "PageSet.h"
#include "PageQueue.h"
#include "Page.h"
#include "WordIndex.h"
#include "WebCrawler.h"

#include "URLInputStream.h"
#include "UnitTest.h"
#include "CS240Exception.h"

using namespace std;

typedef string FileName;


WebCrawler::WebCrawler () : processedPages(PageSet()), wordIndex(WordIndex()) {}


WebCrawler::WebCrawler (const WebCrawler & wcCopy) : 
  processedPages(wcCopy.processedPages), wordIndex(wcCopy.wordIndex) {}


WebCrawler::~WebCrawler () {}
    

WebCrawler & WebCrawler::operator = (const WebCrawler & wcCopy) {
  if (this != &wcCopy) {
    processedPages = wcCopy.processedPages;
    wordIndex = wcCopy.wordIndex;
  }

  return *this;
}


void WebCrawler::crawl (URL & startURL, FileName & stopWord) {
  // Initialize the queue with the start page
  string startURLStr = startURL.getFullURL();
  Page startPage(startURLStr);
  PageQueue unprocessedPages;
  unprocessedPages.enqueue(startPage);

  while (!unprocessedPages.isEmpty()) {

    // Select a page that has not been indexed
    Page currentPage = unprocessedPages.dequeue();
    URL currentURL = currentPage.getURL();

    // Check the processed pages. If we already did it, move on to the next page
    // in the queue
    bool alreadyProcessed = processedPages.Contains(currentPage);
    if (alreadyProcessed) {
      continue;
    }

    // Download selected page
    string currentURLStr = currentURL.getFullURL();
    string description;

    try {
      URLInputStream document(currentURLStr);
      
      // For all text areas in the page, parse out all of the words
      HTMLParser htmlParser(startURLStr, stopWord);
      htmlParser.parse(
          currentURLStr
        , document
        , description
        , this->wordIndex
        , unprocessedPages
      );

      document.Close();
    } catch (CS240Exception & exception) {
      cout << exception.GetMessage() << endl;
    }
 
    // Save summary information for the page
    currentPage.setDescription(description);
    this->processedPages.Insert(currentPage); 

    // Repeat until there are no pages left to index
  }
}


void WebCrawler::printXML (FileName & output) {

}


bool WebCrawler::Test (ostream & os) {
  bool success = true;

  URL startURL("file:///home/eric/school/Web-Crawler/test/test.html");
  string stopWord = "test/stopWords.txt";
  WebCrawler crawler;
  try {
    crawler.crawl(startURL, stopWord);
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }

  //cout << crawler.wordIndex << endl; 

  return success;
}

