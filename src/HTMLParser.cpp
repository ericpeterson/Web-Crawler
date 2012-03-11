#include <string>
#include <iostream>
#include <cctype>
#include <cassert>

#include "WordIndex.h"
#include "Queue.h"
#include "Page.h"
#include "HTMLParser.h"
#include "StopWords.h"
#include "Occurrence.h"
#include "URLFilter.h"

#include "UnitTest.h"
#include "URLInputStream.h"
#include "StringUtil.h"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include "CS240Exception.h"

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


bool HTMLParser::checkTag (string & currentTag) {
  const Size numIgnoreTags = 1; 
  Tag ignoreTags[numIgnoreTags] = {"script"};
  bool ignoreCurrentTag = false;
  for (int i = 0; i < numIgnoreTags; i++) {
    if (ignoreTags[i] == currentTag) {
      ignoreCurrentTag = true;
      break;
    }
  }

  return ignoreCurrentTag;
}

void HTMLParser::insertWord (string & currentURL, string & currentWord,
  WordIndex & words) {

  StringUtil::ToLower(currentWord);
  bool filterWord = stopWords.Contains(currentWord); 
  if (isalpha(currentWord.at(0)) && !filterWord) {
    words.Insert(currentWord, currentURL);
  }
  currentWord = "";
}


void HTMLParser::indexWords (HTMLToken & currentToken, string & currentURL, WordIndex & words) {
  const char* text = currentToken.GetValue().c_str();
  string currentWord;
  while (*text != '\0') {
    bool isWordChar = isWordCharacter(*text); 
    if (!isWordChar && (currentWord != "")) {
      insertWord(currentURL, currentWord, words);
    } else if (isWordChar) {
      currentWord.append(1, *text);  
    }

    text++;
  }

  // add the last word of the TEXT, if we missed it
  if (currentWord != "") {
    insertWord(currentURL, currentWord, words);
  }
}


void HTMLParser::buildDescription (HTMLToken & currentToken, const int & descrLength
  , int & charCount, string & description, bool & gotDescription) {

  const char* text = currentToken.GetValue().c_str();
  while ((*text != '\0') && (charCount < descrLength)) {
    description.append(1, *text);

    // only count if not a white space character
    if (!isspace(*text)) { 
      charCount++;
    }

    text++;
  }
  assert(charCount <= descrLength);
  gotDescription = (charCount == descrLength);
}


void HTMLParser::configureTagStart (HTMLToken & currentToken, string & currentURL
  , string & currentTag, bool & inBody, bool & inHTML, bool & inTitle
  , PageQueue & unprocessedPages) {

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
  if (("a" == currentTag) && inHTML) {
    string href = currentToken.GetAttribute("href");

    /*
      URL constructor will auto-resolve href. The URL constructor is called
      under the hood by the 3-arg Page constructor.
    */
    Page hrefWrapper(currentURL, href, "");

    // filter the resolved href relative to the scope of start url
    URL startURL(this->baseURL);
    URLFilter filter(startURL);
    string resolvedHREF = hrefWrapper.getURL().getFullURL();
    bool shouldFilterHREF = filter.filter(resolvedHREF);
    if (!shouldFilterHREF) {
      unprocessedPages.enqueue(hrefWrapper);
    }
  }
}


void HTMLParser::configureTagEnd (const HTMLToken & currentToken, string & currentTag
  , bool & inBody, bool & inHTML, bool & inTitle, bool & ignoreCurrentTag) {

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
}


bool HTMLParser::shouldWeUseTitle (const string & currentTag, const bool gotDescription,
  const bool inHTML, const bool ignoreCurrentTag) const {

 return ("title" == currentTag) && (!gotDescription) && inHTML && !ignoreCurrentTag;
}


void HTMLParser::checkToIndexWords (const bool & inBody, const bool & inHTML, const bool & inTitle
  , HTMLToken & currentToken, string & currentURL, WordIndex & words) {

  // Index words
  if (inHTML && (inTitle || inBody)) {
    indexWords(currentToken, currentURL, words);
  }
}


void HTMLParser::parse (string & currentURL, URLInputStream & document,
  Description & description, WordIndex & words, PageQueue & unprocessedPages) {
  try {
    HTMLTokenizer tokenizer(&document);
    Tag currentTag;
    bool ignoreCurrentTag = false, gotDescription = false, inBody = false;
    bool inHTML = false, inTitle = false, firstHeader = true;
    int charCount = 0;
    const int descrLength = 100;

    while (tokenizer.HasNextToken()) {
      HTMLToken currentToken = tokenizer.GetNextToken();
   
      switch (currentToken.GetType()) {
        case TAG_START:
          configureTagStart(currentToken, currentURL, currentTag, inBody
            , inHTML, inTitle, unprocessedPages);
          break;
        case TAG_END:
          configureTagEnd(currentToken, currentTag, inBody, inHTML, inTitle
            , ignoreCurrentTag);
          break;
        case COMMENT:
          // ignore comments
          break;
        case TEXT:
          ignoreCurrentTag = checkTag(currentTag);

          checkToIndexWords(inBody, inHTML, inTitle, currentToken, currentURL, words);

          // Get the description
          if (shouldWeUseTitle(currentTag, gotDescription, inHTML, ignoreCurrentTag)) {
            description = currentToken.GetValue();
            gotDescription = !description.empty();
            firstHeader = false;
          } else if ((currentTag.length() > 1) && ('h' == currentTag.at(0)) &&
            (isdigit(currentTag.at(1))) && (true == firstHeader) && inHTML &&
            !ignoreCurrentTag) {
            description = currentToken.GetValue();
            gotDescription = !description.empty();
            firstHeader = false;
          } else if (inBody && !gotDescription && (charCount < descrLength) &&
            inHTML && !ignoreCurrentTag) {
            buildDescription(currentToken, descrLength, charCount, description, gotDescription);
          }
   
          break;
        case END:
          // and we're done!
          break;
        default:
          cout << "Unexpected HTML Token" << currentToken.GetType() << endl;
      }
    }
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }
}


bool HTMLParser::isWordCharacter (char character) {
  return (isalnum(character) || '_' == character || '-' == character);
}


void HTMLParser::free () {}


bool HTMLParser::Test (ostream & os) {
  bool success = true;

  string base = "file:///users/guest/p/peter2/cs240/webCrawler/test/start.html";
  string stopFile = "test/stopWords.txt";
  HTMLParser parser(base, stopFile);

  string currentURL = "file:///users/guest/p/peter2/cs240/webCrawler/test/test.html";
  URLInputStream document(currentURL);
  string description;
  WordIndex words;
  PageQueue unprocessedPages;
  parser.parse(currentURL, document, description, words, unprocessedPages);

  TEST(description == "Hello there");

  const int WORD_COUNT = 45; 
  TEST(words.GetSize() == WORD_COUNT);

  //cout << words << endl;
  //cout << unprocessedPages << endl;

  document.Close();

  return success;
}

