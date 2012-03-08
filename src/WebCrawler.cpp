#include <string>
#include "URL.h"
#include "Status.h"
#include "URLInputStream.h"
#include "HTMLParser.h"
#include "Page.h"

typedef string FileName;


WebCrawler::WebCrawler (URL start) : 
    startURL(start), unprocessedPages(new PageQueue())
  , processedPages(new PageSet()), stopWords(new StopWords())
  , wordIndex(new WordIndex()) 
  {}


WebCrawler::~WebCrawler () {
  free();
}
    

WebCrawler::WebCrawler (const WebCrawler & wcCopy) {
  copy(wcCopy);
}


WebCrawler & WebCrawler::operator = (const WebCrawler & wcCopy) {
  free();
  return copy(wcCopy);
}


Status WebCrawler::crawl () {
  Page currentPage;
  URL currentURL;
  URL baseURL;
  bool startURLFound = false;
  StopWords stopWords("stopwords file");

  while (!unprocessedPages.isEmpty()) {

    // Select a page that has not been indexed
    currentPage = unprocessedPages.dequeue();
    currentURL = currentPage.getURL();

    if (!startURLFound) {
      baseURL = currentURL;
      startURLFound = true;
    }

    // Make sure the url is a valid html page (HTML vs. non-HTML files) and in correct scope


    // Download selected page
    URLInputStream documentStream(currentURL.getURLString());
    
    // For all text areas in the page, parse out all of the words
    HTMLParser htmlParser(documentStream, baseURL.getFullURL(), currentURL.getFullURL(), stopWords);
    htmlParser.parse();
 
    // For all <A> tags with HREF attributes, add the URLs in the HREF attributes
    // to the set of pages that still need to be indexed (but only if they're HTML
    // files with the same prefix as the start URL)
    LinksList hrefLinks = htmlParser.getLinks();
    while (!hrefLinks.hasNext()) {
      unprocessedPages.enqueue(hrefLinks.next());
    }

    // Save summary information for the page
    currentPage.setDescription(htmlParser.getDescription());
    currentPage.setWords(htmlParser.getWords());
    
    visitedPages.add(currentPage);

    documentStream.Close();
    delete documentStream;

    // Repeat until there are no pages left to index
  }
}


WebCrawler & WebCrawler::copy (const WebCrawler & wcCopy) {
  if (this != &wcCopy) {
    startURL = wcCopy.startURL;
    unprocessedPages = wcCopy.unprocessedPages;
    processedPages = wcCopy.processedPages;
    stopWords = wcCopy.stopWords;
    wordIndex = wcCopy.wordIndex;
  }

  return *this;
}


void WebCrawler::free () {
  delete unprocessedPages;
  delete processedPages;
  delete stopWords;
  delete wordIndex;
}
