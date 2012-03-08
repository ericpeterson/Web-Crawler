#include <string>
#include <iostream>
#include <cctype>
#include <cassert>
#include "URLInputStream.h"
#include "StringUtil.h"
#include "WordIndex.h"
#include "Queue.h"
#include "Page.h"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include "HTMLParser.h"
#include "StopWords.h"
#include "UnitTest.h"
using namespace std;

typedef Queue<Page> LinksList;
typedef string Description;
typedef string Tag;
typedef int Size;

HTMLParser::HTMLParser () : 
    description(""), currentURL(""), baseURL(""), words(WordIndex()), 
    stopWords(StopWords("")), links(LinksList()), document(NULL) {}


HTMLParser::HTMLParser (
    URLInputStream & input
  , string & base
  , string & current
  , StopWords & stop
) : description(""), currentURL(current), baseURL(base), words(WordIndex())
  , stopWords(stop), links(LinksList()), document(&input) {}


HTMLParser::~HTMLParser () {
  free();
}


HTMLParser::HTMLParser (const HTMLParser & hpCopy) : stopWords(StopWords("")) {
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
  bool inHTML = false;
  bool inTitle = false;
  int charCount = 0;
  const int descrLength = 100;

  while (tokenizer.HasNextToken()) {
    HTMLToken currentToken = tokenizer.GetNextToken();
 
    switch (currentToken.GetType()) {
      case TAG_START:
        currentTag = currentToken.GetValue();
        StringUtil::ToLower(currentTag);
        if (!inBody) {
          inBody = (currentTag == "body");
        }
        if (!inHTML) {
          inHTML = (currentTag == "html");
        }
        if (!inTitle) {
          inTitle = (currentTag == "html");
        }
        break;
      case TAG_END:
        currentTag.clear();
        if (currentToken.GetValue() == "body") {
          inBody = false;
        }
        if (currentToken.GetValue() == "html") {
          inHTML = false;
        }
        if (currentToken.GetValue() == "title") {
          inTitle = false;
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

        if ("a" == currentTag && inHTML) {
          string href = currentToken.GetAttribute("href");
          bool isAbsolute = URL::checkIfValid(href);
          if (isAbsolute) {
            links.push(Page(href));
          } else {
            links.push(Page(baseURL, href, ""));
          }
        }

        // Index words
        if (inHTML && (inTitle || inBody)) {
          const char* text = currentToken.GetValue().c_str();
          string currentWord;
          while (*text != '\0') {
            bool isWordChar = isWordCharacter(*text); 
            if (!isWordChar && (currentWord != "")) {
              StringUtil::ToLower(currentWord);
              bool filterWord = stopWords.Contains(currentWord); 
              if (!isdigit(currentWord.at(0)) && !filterWord) {
                words.Insert(currentWord, currentURL);
              }
              currentWord = "";
            } else if (isWordChar) {
              currentWord.append(1, *text);  
            }

            text++;
          }
        }

        // Get the description
        if ("title" == currentTag && !gotDescription && inHTML) {
          description = currentToken.GetValue();
          gotDescription = !description.empty();
          firstHeader = false;
        } else if (
          (currentTag.length() > 1) && 
          ('h' == currentTag.at(0)) && 
          (isdigit(currentTag.at(1))) &&
          (true == firstHeader) &&
          inHTML
          ) {

          description = currentToken.GetValue();
          gotDescription = !description.empty();
          firstHeader = false;
        } else if (inBody && !gotDescription && (charCount < descrLength) && inHTML) {
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


bool HTMLParser::isWordCharacter (char character) {
  return (isalnum(character) || '_' == character || '-' == character);
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
    baseURL = hpCopy.baseURL;
    currentURL = hpCopy.currentURL;
    words = hpCopy.words;
    stopWords = hpCopy.stopWords;
    links = hpCopy.links;
    document = hpCopy.document;
  }

  return *this;
}


void HTMLParser::free () {}


bool HTMLParser::Test (ostream & os) {
  bool success = true;
  string base = "file:///home/eric/school/Web-Crawler/test/";

  StopWords stopWords("test/stopWords.txt");
  URLInputStream stream("file:///home/eric/school/Web-Crawler/test/test.html");
  HTMLParser parser(stream, base, base, stopWords);
  parser.parse();
  TEST(parser.description == "Whatisthemeaningoflife?Well,Iwouldsaythatthemeaningoflifebeginsatbirth.Sometimesthedoctorsgetconfuse");
  //TEST(parser.description == "Hello there");
  //TEST(parser.description == "This is it!");

  URLInputStream stream2("file:///home/eric/school/Web-Crawler/test/test2.html");
  HTMLParser parser2(stream2, base, base, stopWords);
  parser2.parse();
  cout << parser2.description << endl;
  TEST(parser2.description == "");

  stream.Close();
  stream2.Close();

  return success;
}

