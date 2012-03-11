#include <iostream>
#include <string>
#include <cstdlib>

#include "WebCrawler.h"

#include "CS240Exception.h"

using namespace std;

int main (int argc, char* argv[]) {
  const int EXPECTED_ARGC = 4;
  if (argc != EXPECTED_ARGC) {
    cout << "Usage: " << argv[0] << " <start-url> <output-file> <stopword-file>";
    cout << endl;
    exit(EXIT_FAILURE);
  }

  string startURLStr = argv[1];
  URL startURL(startURLStr);
  string outFile = argv[2];
  string stopWord = argv[3];

  try {
    WebCrawler crawler(startURL);
    crawler.crawl(stopWord);
    crawler.printXML(outFile);
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  } catch (...) {
    cout << "Unknown exception in Web Crawler" << endl;
  }

  return 0;
}
