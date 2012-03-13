#include <iostream>
#include <string>
#include "URL.h"
#include "LinkedList.h"
#include "BST.h"
#include "Page.h"
#include "Set.h"
#include "Map.h"
#include "Queue.h"
#include "PageQueue.h"
#include "PageSet.h"
#include "StopWords.h"
#include "WordIndex.h"
#include "Occurrence.h"
#include "HTMLParser.h"
#include "URLFilter.h"
#include "WebCrawler.h"
#include "Array.h"
using namespace std;


/**
 *  Determines if the tests are successful based on current test result
 *
 *  @param IN `result` The current test result
 *  @param OUT `success` The success of the test. False if `result` is false;
 *    otherwise it will keep its most recent value.
 */
inline void evaluateSuccess (bool result, bool & success) {
  if (false == result) {
    success = false;
  }
}


int main (int argc, char* argv[]) {
  bool success = true;
  bool testResult = true;

  testResult = URL::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = BST<string>::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = BST<int>::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = LinkedList<string>::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = Page::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = Set<string>::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = Set<int>::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = Map<int, string>::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = Queue<string>::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = PageQueue::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = PageSet::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = StopWords::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = Occurrence::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = WordIndex::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = HTMLParser::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = URLFilter::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = WebCrawler::Test(cout);
  evaluateSuccess(testResult, success);

  testResult = Array::Test(cout);
  evaluateSuccess(testResult, success);

  if (true == success) {
    cout << "All tests passed!" << endl;
  } else {
    cout << "Fail!" << endl;
  }

  return 0;
}
