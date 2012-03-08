#include <string>
#include <iostream>
#include <cctype>
#include <cassert>
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
  bool gotDescription = false;
  bool inBody = false;
  int charCount = 0;
  const int descrLength = 100;

  while (tokenizer.HasNextToken()) {
    HTMLToken currentToken = tokenizer.GetNextToken();
 
    switch (currentToken.GetType()) {
      case TAG_START:
        currentTag = currentToken.GetValue();
        if (!inBody) {
          inBody = (currentTag == "body");
        }
        break;
      case TAG_END:
        currentTag.clear();
        if (currentToken.GetValue() == "body") {
          inBody = false;
        }
        ignoreCurrentTag = false;
        break;
      case COMMENT:
        // ignore comments
        break;
      case TEXT:
        for (int i = 0; i < numIgnoreTags; i++) {
          if (ignoreTags[i] == currentTag) {
            ignoreCurrentTag = true;
          }
        }

        if (true == ignoreCurrentTag) {
          break;
        }

        if ("a" == currentTag) {
          links.push(currentToken.GetAttribute("href"));
        }

        // Get the description
        if ("title" == currentTag && !gotDescription) {
          description = currentToken.GetValue();
          gotDescription = !description.empty();
          firstHeader = false;
        } else if (
          (currentTag.length() > 1) && 
          ('h' == currentTag.at(0)) && 
          (isdigit(currentTag.at(1))) &&
          (true == firstHeader)
          ) {

          description = currentToken.GetValue();
          gotDescription = !description.empty();
          firstHeader = false;
        } else if (inBody && !gotDescription && (charCount < descrLength)) {
          const char* text = currentToken.GetValue().c_str();
          while ((*text != '\0') && (charCount < descrLength)) {
            // only count if not a white space character
            if (!isspace(*text)) { 
              description.append(1, *text);
              charCount++;
            }

            text++;
          }
          assert(charCount <= descrLength);
          gotDescription = (charCount == descrLength);
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

  URLInputStream stream("file:///home/eric/school/Web-Crawler/test/test.html");
  HTMLParser parser(stream);
  parser.parse();
  TEST(parser.description == "Whatisthemeaningoflife?Well,Iwouldsaythatthemeaningoflifebeginsatbirth.Sometimesthedoctorsgetconfuse");
  //TEST(parser.description == "Hello there");
  //TEST(parser.description == "This is it!");

  return success;
}

