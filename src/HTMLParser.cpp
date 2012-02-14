#include <string>
#include "URLInputStream.h"
#include "WordIndex"
#include "LinksList"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include <iostream>
#include <cctype>

typedef string Tag;
typedef int Size;

HTMLParser::HTMLParser () : 
    description(""), words(new WordIndex())
  , links(new LinksList()), document(NULL) {}


HTMLParser::HTMLParser (const URLInputStream & input) :
    description(""), words(new WordIndex)
  , links(new LinksList()), document(&input) {}


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
  HTMLToken currentToken;
  Tag currentTag;
  const Size numIgnoreTags = 1; 
  Tag ignoreTags[numIgnoreTags] = {"script"};
  bool ignoreCurrentTag = false;
  bool firstHeader = true;

  while (tokenizer.HasNextToken()) {
    currentToken = tokenizer.GetNextToken();
 
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
          links.insert(currentToken.GetAttribute("href"));
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
        } else if (description.empty() && (0 == currentTag.GetValue().compare("body"))) {
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


Description HTMLParser::getDescription () const {
  return description;
}


WordIndex HTMLParser::getWords () const {
  return words;
}


LinksList HTMLParser::getLinks () const {
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


void HTMLParser::free () {
  delete words;
  delete links;
}

