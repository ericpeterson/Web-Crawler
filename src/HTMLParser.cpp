#include <string>
#include <iostream>
#include <cctype>
#include "URLInputStream.h"
#include "WordIndex.h"
#include "Queue.h"
#include "URL.h"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include "HTMLParser.h"
#include "UnitTest.h"
using namespace std;

typedef Queue<URL> LinksList;
typedef string Description;
typedef string Tag;
typedef int Size;

HTMLParser::HTMLParser () : 
    description(""), words(WordIndex())
  , links(LinksList()), document(NULL) {}


HTMLParser::HTMLParser (URLInputStream & input) :
    description(""), words(WordIndex())
  , links(LinksList()), document(&input) {}


HTMLParser::~HTMLParser () {
  free();
}


HTMLParser::HTMLParser (const HTMLParser & hpCopy) {
  copy(hpCopy);
}


HTMLParser & HTMLParser::operator = (const HTMLParser & hpCopy) {
  free();
  return copy(hpCopy);
}


void HTMLParser::parse () {
  HTMLTokenizer tokenizer(document);
  Tag currentTag;
  const Size numIgnoreTags = 1; 
  Tag ignoreTags[numIgnoreTags] = {"script"};
  bool ignoreCurrentTag = false;
  bool firstHeader = true;

  while (tokenizer.HasNextToken()) {
    HTMLToken currentToken = tokenizer.GetNextToken();
 
    switch (currentToken.GetType()) {
      case TAG_START:
        currentTag = currentToken.GetValue();
        break;
      case TAG_END:
        currentTag.clear();
        break;
      case COMMENT:
        // ignore comments
        break;
      case TEXT:
        for (int i = 0; i < numIgnoreTags; i++) {
          if (0 == currentTag.compare(ignoreTags[i])) {
            ignoreCurrentTag = true;
          }
        }

        if (true == ignoreCurrentTag) {
          break;
        }

        if ((true == firstHeader) && ('h' == currentTag.at(0)) && 
          (isdigit(currentTag.at(1)))) {

          firstHeader = false;
        }

        if (0 == currentTag.compare("a")) {
          links.push(currentToken.GetAttribute("href"));
        }

        if (0 == currentTag.compare("title")) {
          description = currentToken.GetValue();
        } else if (
          description.empty() && 
          ('h' == currentTag.at(0)) && 
          (isdigit(currentTag.at(1))) &&
          (true == firstHeader)
          ) {

          description = currentToken.GetValue(); 
        } else if (description.empty() && ("body" == currentTag)) {
          description = currentToken.GetValue();
        }
 
        break;
      case END:
        // and we're done!
        break;
      default:
        cout << "Unexpected HTML Token" << currentToken.GetType() << endl;
    }
  }
}


Description & HTMLParser::getDescription () {
  return description;
}


WordIndex & HTMLParser::getWords () {
  return words;
}


LinksList & HTMLParser::getLinks () {
  return links;
}


HTMLParser & HTMLParser::copy (const HTMLParser & hpCopy) {
  if (this != &hpCopy) {
    description = hpCopy.description;
    words = hpCopy.words;
    links = hpCopy.links;
    document = hpCopy.document;
  }

  return *this;
}


void HTMLParser::free () {}


bool HTMLParser::Test (ostream & os) {
  bool success = true;
  return success;
}

