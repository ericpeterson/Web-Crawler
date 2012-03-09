#include <string>
#include <iostream>

#include "URL.h"
#include "Page.h"

#include "UnitTest.h"
#include "StringUtil.h"
#include "CS240Exception.h"

using namespace std;


Page::Page () : url(), description("")  {}


Page::Page (string base, string relative, string descr) : url(relative, base), description(descr) {}


Page::Page (string absolute, string descr) : url(absolute), description(descr) {}


Page::~Page () {}


Page::Page (const Page & pageCopy) {
  copy(pageCopy);
}


Page & Page::operator = (const Page & pageCopy) {
  free();
  return copy(pageCopy);
}


void Page::setDescription (string & pageDescription) {
  this->description = pageDescription;
}


bool Page::operator != (const Page & pageCopy) const {
  string thisURL = this->url.getFullURL();
  string pageURL = pageCopy.url.getFullURL();

  return thisURL != pageURL;
}


bool Page::operator < (const Page & page) const {
  // get the absolute url of both `this` and `page`
  string thisURL = this->url.getFullURL();
  string pageURL = page.url.getFullURL();

  bool thisIsLessThanPage = false;

  //   if this url string is less than page url string, then return true
  if (thisURL < pageURL) {
    thisIsLessThanPage = true;
  }

  return thisIsLessThanPage;
}


bool Page::Test (ostream & os) {
  bool success = true;
  string baseURL = "file:///source/eric.cool";
  string relative = "./../natalie.cool";
  string description = "My cool description";
  string baseURL2 = "http://babies.com/diapers/poop.html";
  string relative2 = "./.././babies-are-cute.apx";

  Page pageDefault;
  Page pageOverloaded(relative, baseURL, "");
  Page pageWithDescription(relative2, baseURL2, description);

  pageDefault = pageWithDescription;

  TEST(pageOverloaded.description == "");
  TEST(pageOverloaded.url.getPrefix() == "file:///source/");
  TEST(pageOverloaded.url.getPageName() == "eric.cool");

  TEST(&pageDefault != &pageWithDescription);
  TEST(pageDefault.description == pageWithDescription.description);
  TEST(pageDefault.url.getPrefix() == pageWithDescription.url.getPrefix());
  TEST(pageDefault.url.getPageName() == pageWithDescription.url.getPageName());

  TEST((pageOverloaded < pageWithDescription) == true); 

  return success; 
}


URL & Page::getURL() {
  return url;
}


string & Page::getDescription () {
  return description;
}


Page & Page::copy (const Page & pageCopy) {
  if (this != &pageCopy) {
    this->url = pageCopy.url;
    this->description = pageCopy.description;
  }

  return *this;
}


ostream & operator << (ostream & stream, Page & page) {
  stream << StringUtil::EncodeToXmlCopy("\t\t<page>\n");
  stream << StringUtil::EncodeToXmlCopy("\t\t\t<url>\n\t\t\t");
  try {
    stream << StringUtil::EncodeToXmlCopy(page.getURL().getFullURL());
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }
  stream << StringUtil::EncodeToXmlCopy("\n\t\t\t</url>\n");

  stream << StringUtil::EncodeToXmlCopy("\t\t\t<description>");
  try {
    stream << StringUtil::EncodeToXmlCopy(page.getDescription());
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }
  stream << StringUtil::EncodeToXmlCopy("</description>\n");

  return stream;
}


void Page::free () {}

