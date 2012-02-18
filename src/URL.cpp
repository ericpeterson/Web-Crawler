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
  , description("")
{}


URL::URL (string absoluteURL) : description("") {
  string urlPrefix;
  string urlPageName;
  
  this->parseURL(absoluteURL, urlPrefix, urlPageName);

  this->prefix = urlPrefix;
  this->pageName = urlPageName;
}


URL::URL (string url, string baseURL) {
  string resolvedURL(url);
  string scheme;
  string urlPrefix;
  string urlPageName;
  
  /*
    When searching the url for 'http://' or 'file://', we search the substring
    from index 0 plus 7 characters
  */
  const Index start = 0;
  const Index schemeLength = 7;

  scheme = url.substr(start, schemeLength);  

  if (("http://" != scheme) && ("file://" != scheme)) {
    char* relativeURLCstring = (char*)url.c_str();
    char* baseURLCstring = (char*)baseURL.c_str();
    resolvedURL = this->resolve(relativeURLCstring, baseURLCstring);
  }

  this->parseURL(resolvedURL, urlPrefix, urlPageName);

  this->prefix = urlPrefix;
  this->pageName = urlPageName;
}


URL::~URL () {}


URL::URL (const URL & uCopy) {
  copy(uCopy);
}


URL & URL::operator = (const URL & uCopy) {
  free();
  return copy(uCopy);
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


char* URL::doSlashCase (int absoluteURLLength, const char* baseURL) {
    char* absoluteTmp = new char[absoluteURLLength];
    int counter = 0;
    
    for (int i=0; i<absoluteURLLength; i++) {
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


char* URL::resolve (char* baseURL, char* relativeURL) const {
  int baseLength = strlen(baseURL);
  int relativeLength = strlen(relativeURL);
  int absoluteURLLength = baseLength + relativeLength + 1;
  char* absoluteURL = new char[absoluteURLLength];
  char* absoluteTmp;
  int counter = 0;
  char* basePtr = const_cast<char*>(baseURL);
  char forwardSlash = '/';

  this->relativePtr = const_cast<char*>(relativeURL);

  switch (*relativeURL) {
      case '/':
          absoluteTmp = doSlashCase(absoluteURLLength, baseURL); 
          strncpy(absoluteURL, absoluteTmp, strlen(absoluteTmp));
          strncat(absoluteURL, relativeURL, relativeLength);
          delete[] absoluteTmp;
          absoluteTmp = NULL;
          break;
      case '.':
          basePtr = doDotCase(basePtr, baseLength, relativeLength);
          while ((baseURL != basePtr) && (counter != absoluteURLLength)) {
              absoluteURL[counter] = baseURL[counter];
              counter++;
          } 

          strncat(absoluteURL, &forwardSlash, 1);
          strncat(absoluteURL, this->relativePtr, relativeLength);
          break;
      case '#':
          strncpy(absoluteURL, baseURL, baseLength);
          strncat(absoluteURL, relativeURL, relativeLength);
          break;
      default:
          basePtr = calculateBasePtr(baseLength, basePtr); 

          counter = 0;
          while ((baseURL != basePtr) && (counter != absoluteURLLength)) {
              absoluteURL[counter] = baseURL[counter];
              counter++;
          }

          strncat(absoluteURL, &forwardSlash, 1);
          strncat(absoluteURL, this->relativePtr, relativeLength);
  }
 
  return absoluteURL;
}


bool URL::Test (ostream & os) {
  bool success = true;
  string startURL("file:///home/eric/myWebPages/coolEric.html");
  string relativeURL("./.././././../natalie/herWebPages/nattles.html");

  // Default constructor
  URL urlDefaultConstructor;
  TEST(urlDefaultConstructor.prefix == "");
  TEST(urlDefaultConstructor.pageName == "");
  TEST(urlDefaultConstructor.description == "");

  // setDescription() function
  urlDefaultConstructor.setDescription("This is a cool description");
  TEST(urlDefaultConstructor.description == "This is a cool description");

  // One arg constructor
  URL startURLConstructor(startURL);
  TEST(startURLConstructor.prefix == "file:///home/eric/myWebPages/");
  TEST(startURLConstructor.pageName == "coolEric.html");
  TEST(startURLConstructor.description == "");

  // Two arg constructor
  URL urlOverloadedConstructor(relativeURL, startURL);
  TEST(urlOverloadedConstructor.prefix == "file:///home/natalie/herWebPages/");
  TEST(urlOverloadedConstructor.pageName == "nattles.html");
  TEST(urlOverloadedConstructor.description == "");

  return success;
}


void URL::setDescription (string urlDescription) {
  this->description = urlDescription;
}


void URL::parseURL (string url, string & urlPrefix, string & urlPageName) const {
    char forwardSlash = '/';
    Index lastSlashPosition;
    Index lastSlashPositionPlusOne;
    Index start = 0;

    lastSlashPosition = url.find_last_of(forwardSlash);
    assert(lastSlashPosition > 7);

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
    this->description = uCopy.description;
  }

  return *this;
}


void URL::free () {}

