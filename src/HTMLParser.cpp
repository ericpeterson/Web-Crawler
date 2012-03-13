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
  , string & currentTag, bool* & bools, PageQueue & unprocessedPages) {

  bool inBody = bools[0];
  bool inHTML = bools[1];
  bool inTitle = bools[2];
  bool inHeader = bools[3];

  currentTag = currentToken.GetValue();
  StringUtil::ToLower(currentTag);
  if (!inBody) {
    bools[0] = (currentTag == "body");
  }
  if (!inHTML) {
    bools[1] = (currentTag == "html");
  }
  if (!inTitle) {
    bools[2] = (currentTag == "title");
  }
  if (!inHeader && !currentTag.empty() && ('h' == currentTag.at(0)) &&
    (isdigit(currentTag.at(1)))) {
    bools[3] = true;  
  }


  // links
  if (("a" == currentTag) && inHTML) {
    string href = currentToken.GetAttribute("href");

    // For some reason if href="" then HTMLToken returns " as the href
    if (("" != href) && ("\"" != href)) {
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
}


void HTMLParser::configureTagEnd (const HTMLToken & currentToken, string & currentTag
  , bool & inBody, bool & inHTML, bool & inTitle, bool & inHeader, bool & firstHeader) {

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

  string currentTokenStr = currentToken.GetValue();
  if ((currentTokenStr.length() > 1) && ('h' == currentTokenStr.at(0)) &&
    (isdigit(currentTokenStr.at(1)))) {
    inHeader = false;
    firstHeader = false;
  }
}


bool HTMLParser::shouldWeUseTitle (const bool inTitle, const bool inHTML) const {

 return inTitle && inHTML;
}


void HTMLParser::checkToIndexWords (const bool & ignore, const bool & inBody,
  const bool & inHTML, const bool & inTitle, HTMLToken & currentToken, string &
  currentURL, WordIndex & words) {

  if (ignore) {
    return;
  }

  // Index words
  if (inHTML && (inTitle || inBody)) {
    indexWords(currentToken, currentURL, words);
  }
}


void HTMLParser::checkTitle (const bool & ignore, const bool & inTitle,
    const bool & inHTML, const HTMLToken & currentToken, string & description,
    bool & gotDescription, bool & firstHeader) {

  if (ignore) {
    return;
  }

  if (shouldWeUseTitle(inTitle, inHTML)) {
    description += currentToken.GetValue();
    gotDescription = !description.empty();
    firstHeader = false;
  } 
}


void HTMLParser::parse (string & currentURL, URLInputStream & document,
  Description & description, WordIndex & words, PageQueue & unprocessedPages) {
  try {
    HTMLTokenizer tokenizer(&document);
    Tag currentTag;
    bool gotDescription = false, inBody = false, inHeader = false, ignore = false;
    bool inHTML = false, inTitle = false, firstHeader = true, building = false;
    bool boolArray[4] = {inBody, inHTML, inTitle, inHeader};
    bool* startBool = &boolArray[0];
    int charCount = 0;
    const int descrLength = 100;

    while (tokenizer.HasNextToken()) {
      HTMLToken currentToken = tokenizer.GetNextToken();
   
      switch (currentToken.GetType()) {
        case TAG_START:
          configureTagStart(currentToken, currentURL, currentTag, startBool, unprocessedPages);
          break;
        case TAG_END:
          configureTagEnd(currentToken, currentTag, boolArray[0], boolArray[1],
            boolArray[2], boolArray[3], firstHeader);
          break;
        case COMMENT:
          // ignore comments
          break;
        case TEXT:
          ignore = checkTag(currentTag);
          checkToIndexWords(ignore, boolArray[0], boolArray[1], boolArray[2],
            currentToken, currentURL, words);

          // Get the description
          checkTitle(ignore, boolArray[2], boolArray[1], currentToken, description,
            gotDescription, firstHeader);
          if (boolArray[3] && (true == firstHeader) && !ignore) {
            if (building) {description = ""; building = false;}
            description += currentToken.GetValue();
            gotDescription = !description.empty();
          } else if (boolArray[0] && !gotDescription && (charCount < descrLength) &&
            boolArray[1] && !ignore) { building = true;
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

  const int WORD_COUNT = 47;
  TEST(words.GetSize() == WORD_COUNT);

  //cout << words << endl;
  //cout << unprocessedPages << endl;

  document.Close();

  return success;
}

