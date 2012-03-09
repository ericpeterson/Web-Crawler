#include <iostream>
#include <string>
#include "URL.h"
#include "Occurrence.h"
#include "UnitTest.h"
using namespace std;

Occurrence::Occurrence (URL site, int occurrences) : url(site), count(occurrences) {}


Occurrence::Occurrence (const Occurrence & oCopy) {
  copy(oCopy);
}


Occurrence::~Occurrence () {
  free();
}


Occurrence & Occurrence::operator = (const Occurrence & oCopy) {
  free();
  return copy(oCopy);
} 


bool Occurrence::operator < (const Occurrence & oCopy) const {
  string thisURL = url.getFullURL();
  string otherURL = oCopy.url.getFullURL();

  return thisURL < otherURL; 
}


void Occurrence::increment () {
  count = count + 1;
}


int Occurrence::getCount () const {
  return count;
}


URL & Occurrence::getURL () const {
  return (URL &)url;
} 


bool Occurrence::Test (ostream & os) {
  bool success = true;

  URL url("http://www.lds.org/en/ensigns-are-cool.html");
  Occurrence happen(url);

  TEST(happen.url.getFullURL() == "http://www.lds.org/en/ensigns-are-cool.html");
  TEST(happen.count == 1);

  happen.increment();
  happen.increment();

  URL url2("/happen", "http://www.google.com/hithere.html");
  Occurrence happening(url2);
  happening = happen;

  const int TEST = 10; 
  for (int i = 0; i < TEST; i++) {
    happen.increment();
  }

  TEST(happen.url.getFullURL() == happening.url.getFullURL());
  TEST(&happen != &happening);
  TEST(happen.count == TEST + 3);
  TEST(happening.count == 3);

  return success;
}


ostream & operator << (ostream & stream, Occurrence & occurrence) {
  stream << "(" << occurrence.getCount() << ", " << 
    occurrence.getURL().getFullURL() << ")" << endl;
  return stream;
}


Occurrence & Occurrence::copy (const Occurrence & oCopy) {
  if (this != &oCopy) {
    url = oCopy.url;
    count = oCopy.count;
  }

  return *this;
}


void Occurrence::free () {}

