#include <string>
#include <iostream>
#include <cassert>

#include "URLFilter.h"
#include "URL.h"

#include "UnitTest.h"

using namespace std;

URLFilter::URLFilter (URL & start) : startURL(start) {}


bool URLFilter::filter (const URL & url) {
  // check scope -- we stop here if out of scope
  if (url.getPrefix() != this->startURL.getPrefix()) {
    return true;
  }

  // we assume the url is already resolved
  string fullURL = url.getFullURL();
  assert(URL::checkIfValid(fullURL) == true);

  // Ignore ?<query>
  size_t indexOfQuestionMark = fullURL.find('?');
  string fullWithoutQuery = fullURL.substr(0, indexOfQuestionMark);
  indexOfQuestionMark = url.getPageName().find('?');
  string pageNameWithoutQuery = url.getPageName().substr(0, indexOfQuestionMark);

  // valid if:
  //  1. <path> end's with a '/'. The full URL end's in '/'. This may not be
  //    entirely necessary for already resolved URL's
  size_t fullLength = fullWithoutQuery.length();
  bool shouldFilter = true;
  if (!fullWithoutQuery.empty() && (fullWithoutQuery.at(fullLength-1) == '/')) {
    shouldFilter = false;
  }
  
  //  2. file name contains no period's (no extensions)
  size_t indexOfPeriod = pageNameWithoutQuery.find('.');
  if (!pageNameWithoutQuery.empty() && (string::npos == indexOfPeriod)) {
    shouldFilter = false;
  }

  //  3. file name has a specific extension
  bool hasSpecificExtension = checkExtension(pageNameWithoutQuery);
  if (hasSpecificExtension) {
    shouldFilter = false;
  }

  return shouldFilter;
}


bool URLFilter::checkExtension (string & fileName) {
  const int NUM_EXTENSIONS = 10;
  string extensions[NUM_EXTENSIONS] = {
    ".html", ".htm", ".shtml", ".cgi", ".jsp", 
    ".asp", ".aspx", ".php", ".pl", ".cfm"
  };

  bool hasExtension = false;
  for (int i = 0; i < NUM_EXTENSIONS; i++) {
    size_t indexOfExtension = fileName.find(extensions[i]);
    if (string::npos != indexOfExtension) {
      hasExtension = true;
      break;
    }
  }

  return hasExtension;
}


bool URLFilter::Test (ostream & os) {
  bool success = true;

  const int NUM_VALID = 12;
  const int NUM_INVALID = 5;
  URL validURLS[NUM_VALID] = {
      URL("http://www.google.com/a/b/c/")
    , URL("http://www.google.com/a/b/c/howdy_doody")
    , URL("http://www.google.com/a/b/c/file.html")
    , URL("http://www.google.com/a/b/c/file.htm")
    , URL("http://www.google.com/a/b/c/file.shtml")
    , URL("http://www.google.com/a/b/c/file.cgi?myParam=\"hi\"&yourParam=\"bye\"")
    , URL("http://www.google.com/a/b/c/file.jsp")
    , URL("http://www.google.com/a/b/c/file.asp")
    , URL("http://www.google.com/a/b/c/file.aspx?thisisalongparameter")
    , URL("http://www.google.com/a/b/c/file.php")
    , URL("http://www.google.com/a/b/c/file.pl?minWait=1100")
    , URL("http://www.google.com/a/b/c/file.cfm")
  };
  URL invalidURLS[NUM_INVALID] = {
      URL("file:///")
    , URL("http://www.google.com/a/b/c/file.txt")
    , URL("http://www.byu.edu")
    , URL("http://www.google.com/a/b/c/file.txt?file.html")
    , URL("http://www.byu.edu?mycoolfile.php")
  };

  URL startURL("http://www.google.com/a/b/c/d.cgi");
  URLFilter filter(startURL);
  for (int i = 0; i < NUM_VALID; i++) {
    bool needsToBeFiltered = filter.filter(validURLS[i]);
    TEST(needsToBeFiltered == false);
  }

  for (int i = 0; i < NUM_INVALID; i++) {
    bool needsToBeFiltered = filter.filter(invalidURLS[i]);
    TEST(needsToBeFiltered == true);
  }

  return success;
}

