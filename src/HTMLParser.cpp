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
#include "Occurrence.h"
#include "UnitTest.h"
using namespace std;

typedef Queue<Page> LinksList;
typedef string Description;
typedef string Tag;
typedef int Size;
typedef Set<Occurrence> OccurrenceSet;


HTMLParser::HTMLParser (string & base, string & stopFile) : 
  baseURL(base), stopWords(stopFile.c_str()) {}


HTMLParser::HTMLParser (string & base, const char* stopFile) : 
  baseURL(base), stopWords(stopFile) {}


HTMLParser::~HTMLParser () {
  free();
}


HTMLParser::HTMLParser (const HTMLParser & hpCopy) : 
  baseURL(hpCopy.baseURL), stopWords(hpCopy.stopWords) {}


HTMLParser & HTMLParser::operator = (const HTMLParser & hpCopy) {
  free();

  if (this != &hpCopy) {
    baseURL = hpCopy.baseURL;
    stopWords = hpCopy.stopWords;
  }

  return *this;
}


void HTMLParser::parse (string & currentURL, URLInputStream & document,
  Description & description, WordIndex & words, PageQueue & unprocessedPages) {

  HTMLTokenizer tokenizer(&document);
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
          inTitle = (currentTag == "title");
        }

        // links
        if ("a" == currentTag && inHTML) {
          string href = currentToken.GetAttribute("href");
          bool isAcceptable = true;
          //bool isAcceptable = URLFilter::filter(href);
          if (isAcceptable) {
            bool isAbsolute = URL::checkIfValid(href);
            if (isAbsolute) {
              unprocessedPages.enqueue(Page(href));
            } else {
              unprocessedPages.enqueue(Page(baseURL, href, ""));
            }
          }
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


void HTMLParser::free () {}


bool HTMLParser::Test (ostream & os) {
  bool success = true;

  string base = "file:///home/eric/school/Web-Crawler/test/start.html";
  string stopFile = "test/stopWords.txt";
  HTMLParser parser(base, stopFile);

  string currentURL = "file:///home/eric/school/Web-Crawler/test/test.html";
  URLInputStream document(currentURL);
  string description;
  WordIndex words;
  PageQueue unprocessedPages;
  parser.parse(currentURL, document, description, words, unprocessedPages);

  TEST(description == "Hello there");

  const int WORD_COUNT = 45; 
  TEST(words.GetSize() == WORD_COUNT);

  cout << words << endl;
  cout << unprocessedPages << endl;

  document.Close();

  return success;
}

