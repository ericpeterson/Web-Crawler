#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cassert>

#include "StopWords.h"
#include "Array.h"

#include "StringUtil.h"
#include "CS240Exception.h"
#include "UnitTest.h"
using namespace std;

typedef string Word;

StopWords::StopWords (const char* file) : Array() {
  assert(NULL != file);

  ifstream stream(file);
  string currentWord;

  if (!stream.is_open()) {
    throw CS240Exception("Stop words file did not open correctly");
  }

  while (stream.good()) {
    getline(stream, currentWord);
    StringUtil::ToLower(currentWord);
    StringUtil::Trim(currentWord);
    if (!currentWord.empty()) {
      this->Push(currentWord);
    }
  }

  stream.close();
}


StopWords::~StopWords () {
  free();
}


StopWords::StopWords (const StopWords & swCopy) : Array(swCopy) {}


StopWords & StopWords::operator = (const StopWords & swCopy) {
  free();
  return copy(swCopy);
}


bool StopWords::Contains (string & word) const {
  StringUtil::ToLower(word);
  return Array::Contains(word);
}


bool StopWords::Contains (const char* word) const {
  return Array::Contains(word);
}


bool StopWords::Test (ostream & os) {
  bool success = true;
  const ArraySize NUM_WORDS = 15;
  const ArraySize NOT_INCLUDED = 10;
  const char* file = "test/stopWords.txt";
  const char* file2 = "test/stopWords2.txt";
  string words[NUM_WORDS] = {
      "a", "ab", "hi", "there", "what"
    , "z", "hypocephalis", "word", "and", "Natalie"
    , "the", "google", "maybe", "baby", "pregnant"
  };
  string notIncluded[NOT_INCLUDED] = {
      "weasel", "carriage", "Carnegie", "melon", "house"
    , "chees", "water", "flower", "mansion", "bobsledteam"
  };

  StopWords myWords(file);
  StopWords otherWords(file2);
  otherWords = myWords;

  TEST(myWords.GetLength() == NUM_WORDS); 
  TEST(otherWords.GetLength() == NUM_WORDS);
  TEST(&myWords != &otherWords);

  for (ArraySize i = 0; i < NUM_WORDS; i++) {
    string currentWord(words[i]);
    TEST(myWords.Contains(currentWord) == true);
    TEST(otherWords.Contains(currentWord) == true);
  }

  for (ArraySize i = 0; i < NOT_INCLUDED; i++) {
    string currentWord(notIncluded[i]);
    TEST(myWords.Contains(currentWord) == false);
    TEST(otherWords.Contains(currentWord) == false);
  } 

  return success;
}


StopWords & StopWords::copy (const StopWords & swCopy) {
  Array::copy(swCopy);
  return *this;
}


void StopWords::free () {
  Array::free();
}

