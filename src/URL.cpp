#include <string>
#include <cstring>
#include <cassert>
#include "URL.h"
#include "UnitTest.h"
using namespace std;

typedef size_t Index;


URL::URL () : 
    prefix("")
  , pageName("") 
  , fullURL("") {}


URL::URL (string absoluteURL) {
  string urlPrefix = "";
  string urlPageName = "";

  bool isValidURL = checkIfValid(absoluteURL);

  // Only parse if absoluteURL is a valid absolute URL
  if (true == isValidURL) {
    this->parseURL(absoluteURL, urlPrefix, urlPageName);
  }

  this->prefix = urlPrefix;
  this->pageName = urlPageName;
  this->fullURL = absoluteURL;
}


URL::URL (string url, string baseURL) {
  string resolvedURL(url);
  string urlPrefix;
  string urlPageName;

  /*
    We expect url to be an invalid absolute url (a relative url) and baseURL to
    be valid
  */
  bool urlIsValid = checkIfValid(url);
  bool baseURLIsValid = checkIfValid(baseURL);

  /*
    Resolve the url in the normal way if the input is valid. If the base URL is
    invalid, resolve the url to the empty string. Otherwise url is an absolute
    url and there is no need to resolve it.
  */
  if ((false == urlIsValid) && (true == baseURLIsValid)) {
    char* relativeURLCstring = (char*)url.c_str();
    char* baseURLCstring = (char*)baseURL.c_str();

    // Added this temp variable in to clean up a memory leak from the old url
    // resolver code
    char* tmpResolvedURL = this->resolve(baseURLCstring, relativeURLCstring);
    const int MAX_RESOLVED_LENGTH = 2048;
    char resolvedURLStr[MAX_RESOLVED_LENGTH] = {0};
    strcpy(resolvedURLStr, tmpResolvedURL);
    delete[] tmpResolvedURL;
    tmpResolvedURL = NULL;

    resolvedURL = resolvedURLStr;
  } else if ((false == urlIsValid) && (false == baseURLIsValid)) {
    resolvedURL = "";
  } else {
    // url is absolute. No need to resolve
  }

  this->parseURL(resolvedURL, urlPrefix, urlPageName);

  this->prefix = urlPrefix;
  this->pageName = urlPageName;
  this->fullURL = resolvedURL;
}


URL::~URL () {}


URL::URL (const URL & uCopy) {
  copy(uCopy);
}


URL & URL::operator = (const URL & uCopy) {
  free();
  return copy(uCopy);
}


bool URL::operator != (const URL & uCopy) {
  string thisURL = this->getFullURL();
  string otherURL = uCopy.getFullURL();

  return thisURL != otherURL;
}


string URL::getFullURL () const {
  return this->fullURL;
}


string URL::getPrefix () const {
  return this->prefix;
}


string URL::getPageName () const {
  return this->pageName;
}


bool URL::checkIfValid (string url) const {
  string scheme;
  Index start = 0;
  Index schemeLength = 7;
  int urlLength = url.length();
  bool isValid = true;
  const int net_locIndex = 7;

  /*
    scheme http must have at least 8 characters. i.e. `http://<net_loc>` where
    <net_loc> has at least one character. 
  */
  const int acceptableHTTPLength = 8;

  /*
    scheme file must have at least 7 characters. i.e. `file://`
  */
  const int acceptableFILELength = 7;

  scheme = url.substr(start, schemeLength);

  if (("file://" != scheme) && ("http://" != scheme)) {
    isValid = false; 
  } else if ("http://" == scheme) {
    if ((urlLength < acceptableHTTPLength) || ('/' == url.at(net_locIndex))) {
      isValid = false;
    }
  } else {
    if (urlLength < acceptableFILELength) {
      isValid = false;
    } else if ((urlLength > acceptableFILELength) && ('/' != url.at(net_locIndex))) {
      isValid = false;
    }
  }

  return isValid;
}


char* URL::calculateBasePtr (int baseLength, char* basePtr) {
    int counter = 0;
    char* basePtrCopy = basePtr;
 
    basePtrCopy += baseLength - 1;
    while (('/' != *basePtrCopy) && (baseLength-1 != counter)) {
        basePtrCopy--;
        counter++;
    }
   
    if ((basePtrCopy - basePtr) > 6) {
        *basePtrCopy = '\0';
        basePtrCopy--;
    }

    return basePtrCopy;
}


char* URL::doSlashCase (int baseLength, const char* baseURL) {
    char* absoluteTmp = new char[baseLength];
    int counter = 0;
    
    for (int i=0; i<baseLength; i++) {
        absoluteTmp[i] = baseURL[i];
        if ('/' == baseURL[i]) {
            counter++;
            if (3 == counter) {
                absoluteTmp[i] = '\0';
                break;
            }
        }
    }

    return absoluteTmp;
}


char* URL::doDotCase (char* basePtr, int baseLength, int relativeLength) {
    int counter = 0;
    basePtr = calculateBasePtr(baseLength, basePtr); 
        
    for (int i=0; i<relativeLength; i++) {
        if ('.' == *this->relativePtr) {
            if ('.' == *(this->relativePtr+1)) {
                while (('/' != *basePtr) && 
                       (baseLength-1 != counter)) {
                    basePtr--;
                    counter++;
                }
                *basePtr = '\0';
                basePtr--;
                this->relativePtr += 3;
            } else { this->relativePtr += 2; }
        } else { break; } 
    }
    
    return basePtr;
} 


char* URL::resolve (char* baseURL, char* relativeURL) {
  int baseLength = strlen(baseURL);
  int relativeLength = strlen(relativeURL);
  int absoluteURLLength = baseLength + relativeLength + 1;
  char* absoluteURL = new char[absoluteURLLength];
  char* absoluteTmp = NULL;
  int counter = 0;
  char* basePtr = const_cast<char*>(baseURL);
  char forwardSlash[2] = {'/', '\0'};

  for (counter = 0; counter < absoluteURLLength; counter++) {
    absoluteURL[counter] = '\0';
  }
  counter = 0;

  this->relativePtr = const_cast<char*>(relativeURL);

  switch (*relativeURL) {
      case '/':
          absoluteTmp = doSlashCase(baseLength, baseURL); 
          strcpy(absoluteURL, absoluteTmp);
          strcat(absoluteURL, relativeURL);
          delete[] absoluteTmp;
          absoluteTmp = NULL;
          break;
      case '.':
          basePtr = doDotCase(basePtr, baseLength, relativeLength);
          while ((&baseURL[counter] != (basePtr+1)) && (counter != (absoluteURLLength - 1))) {
              absoluteURL[counter] = baseURL[counter];
              counter++;
          } 

          strcat(absoluteURL, forwardSlash);
          strcat(absoluteURL, this->relativePtr);
          break;
      case '#':
          strcpy(absoluteURL, baseURL);
          strcat(absoluteURL, relativeURL);
          break;
      default:
          basePtr = calculateBasePtr(baseLength, basePtr); 

          counter = 0;
          while ((&baseURL[counter] != (basePtr+1)) && (counter != (absoluteURLLength-1))) {
              absoluteURL[counter] = baseURL[counter];
              counter++;
          }

          strcat(absoluteURL, forwardSlash);
          strcat(absoluteURL, this->relativePtr);
  }
 
  return absoluteURL;
}


bool URL::Test (ostream & os) {
  bool success = true;
  string startURL("file:///home/eric/myWebPages/coolEric.html");
  string relativeURL("./.././././../natalie/herWebPages/nattles.html");

  // One arg constructor
  URL startURLConstructor(startURL);
  TEST(startURLConstructor.prefix == "file:///home/eric/myWebPages/");
  TEST(startURLConstructor.pageName == "coolEric.html");
  TEST(startURLConstructor.fullURL == "file:///home/eric/myWebPages/coolEric.html");

  URL url2("file://");
  TEST(url2.prefix == "file://");
  TEST(url2.pageName == "");
  TEST(url2.fullURL == "file://");

  // Two arg constructor
  URL urlOverloadedConstructor(relativeURL, startURL);
  TEST(urlOverloadedConstructor.prefix == "file:///home/natalie/herWebPages/");
  TEST(urlOverloadedConstructor.pageName == "nattles.html");
  TEST(urlOverloadedConstructor.fullURL == "file:///home/natalie/herWebPages/nattles.html");

  // Assignment operator - addresses shouldn't match but values should
  startURLConstructor = urlOverloadedConstructor;
  TEST((&(urlOverloadedConstructor.prefix)) != (&(startURLConstructor.prefix)));
  TEST((&(urlOverloadedConstructor.pageName)) != (&(startURLConstructor.pageName)));
  TEST((&(urlOverloadedConstructor.fullURL)) != (&(startURLConstructor.fullURL)));
  TEST(urlOverloadedConstructor.prefix == startURLConstructor.prefix);
  TEST(urlOverloadedConstructor.pageName == startURLConstructor.pageName);
  TEST(urlOverloadedConstructor.fullURL == startURLConstructor.fullURL);

  return success;
}




void URL::parseURL (const string & url, string & urlPrefix, string & urlPageName) const {
    char forwardSlash = '/';
    Index lastSlashPosition;
    Index lastSlashPositionPlusOne;
    Index start = 0;
    Index net_locIndex = 7;

    lastSlashPosition = url.find_last_of(forwardSlash);

    // url is an invalid URL
    if (string::npos == lastSlashPosition) {
      urlPrefix = "";
      urlPageName = "";
      return;
    } else if (lastSlashPosition < net_locIndex) {
      urlPrefix = url;
      urlPageName = "";
      return;
    }

    /*
      This value will be used to include the '/' in the prefix and exclude the
      '/' in the page name
    */
    lastSlashPositionPlusOne = lastSlashPosition + 1;

    urlPrefix = url.substr(start, lastSlashPositionPlusOne);
    urlPageName = url.substr(lastSlashPositionPlusOne);
}


URL & URL::copy (const URL & uCopy) {
  if (this != &uCopy) {
    this->prefix = uCopy.prefix;
    this->pageName = uCopy.pageName;
    this->fullURL = uCopy.fullURL;    
  }

  return *this;
}


void URL::free () {}

