#include <iostream>
#include <string>
#include "URL.h"
#include "BST.h"
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

  if (true == success) {
    cout << "All tests passed!" << endl;
  } else {
    cout << "Fail!" << endl;
  }

  return 0;
}
