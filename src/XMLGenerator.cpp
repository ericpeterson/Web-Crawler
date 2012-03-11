#include <string>
#include <iostream>
#include <fstream>

#include "URL.h"
#include "Page.h"
#include "PageSet.h"
#include "WordIndex.h"
#include "XMLGenerator.h"

#include "StringUtil.h"
#include "CS240Exception.h"

using namespace StringUtil;


XMLGenerator::XMLGenerator (std::string & outFile) : xmlFile(outFile) {}


XMLGenerator::~XMLGenerator () {}


XMLGenerator::XMLGenerator (const XMLGenerator & xgCopy) {
  copy(xgCopy);
}


XMLGenerator & XMLGenerator::operator = (const XMLGenerator & xgCopy) {
  free();
  return copy(xgCopy);
}


void XMLGenerator::generate (URL & startURL, PageSet & pages, WordIndex & words) {
  std::ofstream of(this->xmlFile.c_str());

  if (!of.is_open()) {
    throw CS240Exception("Could not open XML out file");
  }

  of << ("<website>\n");
  of << ("  <start-url>\n    ");
  try {
    of << EncodeToXmlCopy(startURL.getFullURL());
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }
  of << ("\n  </start-url>\n");

  of << ("  <pages>\n");
  of << pages; 
  of << ("  </pages>\n");

  of << ("  <index>\n");

  try {
    of << words;
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }
  of << ("  </index>\n");
  of << ("</website>\n");

  of.close();
}


XMLGenerator & XMLGenerator::copy (const XMLGenerator & xgCopy) {
  if (this != &xgCopy) {
    xmlFile = xgCopy.xmlFile;
  }

  return *this;
}


void XMLGenerator::free () {}

