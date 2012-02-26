#include <iostream>
#include <string>
#include "URL.h"
#include "LinkedList.h"
#include "BST.h"
#include "Page.h"
#include "Set.h"
using namespace std;

int main (int argc, char* argv[]) {
  bool success = true;
  bool testResult = true;

  testResult = URL::Test(cout);
  if (false == testResult) {
    success = false;
  }

  testResult = BST<string>::Test(cout);
  if (false == testResult) {
    success = false;
  }

  testResult = BST<int>::Test(cout);
  if (false == testResult) {
    success = false;
  }

  testResult = LinkedList<string>::Test(cout);
  if (false == testResult) {
    success = false;
  }

  testResult = Page::Test(cout);
  if (false == testResult) {
    success = false;
  }

  testResult = Set<int>::Test(cout);
  if (false == testResult) {
    success = false;
  }

  if (true == success) {
    cout << "All tests passed!" << endl;
  } else {
    cout << "Fail!" << endl;
  }

  return 0;
}
