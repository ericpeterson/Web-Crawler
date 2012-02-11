#include "Queue.h"
#include "URLInputStream.h"
#include "HTMLParser.h"

WebCrawler::WebCrawler () {}


WebCrawler::~WebCrawler () {}
    

WebCrawler::WebCrawler (const WebCrawler & wcCopy) {
  copy(wcCopy);
}


WebCrawler & WebCrawler::operator = (const WebCrawler & wcCopy) {
  free();
  return copy(wcCopy);
}


Status WebCrawler::crawl (URL startURL, FileName output, FileName stopWord) {
  Queue<Pages> pageQueue(startURL);
  URL current;

  // select start url
  while (!pageQueue.isEmpty()) {
    current = pageQueue.dequeue();
    // resolve current url if necessary
    // determine http:// or file://
    // download selected page
    URLInputStream UIStream(current);
    // for all text areas in page, parse out words
    // for <a> tags add page to set that still needs to be indexed (queue)
    // Save Summary information
    HTMLParser htmlParser;
    htmlParser.parse(UIStream);
    // Repeat until no pages left to index
  }
}


WebCrawler & WebCrawler::copy (const WebCrawler & wcCopy) {
  if (this != &wcCopy) {
    
  }

  return *this;
}


void WebCrawler::free () {}
