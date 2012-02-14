#include <string>
#include "URL.h"
#include "Page.h"
#include "PageSet.h"
#include "WordIndex.h"
#include "StringUtil.h"

using namespace std;

typedef string XMLDoc;
typedef string Word;


XMLGenerator::XMLGenerator () : document("") {}


XMLGenerator::~XMLGenerator () {}


XMLGenerator::XMLGenerator (const XMLGenerator & xgCopy) {
  copy(xgCopy);
}


XMLGenerator & XMLGenerator::operator = (const XMLGenerator & xgCopy) {
  free();
  return copy();
}


XMLDoc XMLGenerator::generate (URL startURL, PageSet pages, WordIndex words) {
  XMLDoc output("");
  Page currentPage;
  Word currentWord;

  output += "<website>\n";
  output += "\t<startURL>\n\t\t";
  output += startURL.getURLString();
  output += "\n\t</startURL>\n";

  output += "\t<pages>\n";
  while (!pages.isEmpty()) {
    currentPage = pages.getCurrent();

    output += "\t\t<page>\n";
    output += "\t\t\t<url>\n\t\t\t";
    output += currentPage.getURL().getURLString();
    output += "\n\t\t\t</url>\n";

    output += "\t\t\t<description>";
    output += currentPage.getDescription();
    output += "</description>\n";
  }
  output += "\t<pages>\n";

  output += "\t<index>\n";
  while (!words.isEmpty()) {
    currentWord = words.getCurrent();

    output += "\t\t<word>\n";
    output += "\t\t\t<value>";
    output += currentWord.getWord();
    output += "</value>\n";
    output += "\t\t\t<occurrence>\n";
    output += "\t\t\t\t<url>\n\t\t\t\t\t";
    output +=  currentWord.getURL();
    output += "\n\t\t\t\t</url>\n";
    output += "\t\t\t\t<count>";
    output += currentWord.getCount();
    output += "</count>\n";
    output += "\t\t\t</occurrence>\n";
    output += "\t\t</word>\n";
  }
  output += "\t</index>\n";
  output += "</website>\n";

  document = EncodeToXmlCopy(output);
  return document;
}


XMLGenerator & XMLGenerator::copy (const XMLGenerator & xgCopy) {
  if(this != &xgCopy) {
    document = xgCopy.document;
  }

  return *this;
}


void XMLGenerator::free () {}

