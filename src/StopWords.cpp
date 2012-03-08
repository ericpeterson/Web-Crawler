#include <string>
#include <iostream>
#include <fstream>
#include <cctype>

#include "StopWords.h"
#include "Set.h"
#include "StringUtil.h"
using namespace std;

typedef string Word;

StopWords::StopWords (const char* file) : Set<Word>::Set() {
  ifstream stream(file);
  string currentWord;

  if (!stream.is_open()) {
    // There's a problem
  }

  while (stream.good()) {
    getline(stream, currentWord);
    StringUtil::ToLower(currentWord);
    StringUtil::Trim(currentWord);
    if (!currentWord.empty()) {
      Insert(currentWord);
    }
  }

  stream.close();
}


StopWords::~StopWords () {
  free();
}


StopWords::StopWords (const StopWords & swCopy) {
  copy(swCopy);
}


StopWords & StopWords::operator = (const StopWords & swCopy) {
  free();
  return copy(swCopy);
}


bool StopWords::Contains (string & word) const {
  StringUtil::ToLower(word);
  return Set<Word>::Contains(word);
}

bool StopWords::Test (ostream & os) {
  bool success = true;
  const int NUM_WORDS = 15;
  const int NOT_INCLUDED = 10;
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

  TEST(myWords.GetSize() == NUM_WORDS); 
  TEST(otherWords.GetSize() == NUM_WORDS);
  TEST(&myWords != &otherWords);

  for (int i = 0; i < NUM_WORDS; i++) {
    string currentWord(words[i]);
    TEST(myWords.Contains(currentWord) == true);
    TEST(otherWords.Contains(currentWord) == true);
  }

  for (int i = 0; i < NOT_INCLUDED; i++) {
    string currentWord(notIncluded[i]);
    TEST(myWords.Contains(currentWord) == false);
    TEST(otherWords.Contains(currentWord) == false);
  } 

  return success;
}


StopWords & StopWords::copy (const StopWords & swCopy) {
  Set<Word>::copy(swCopy);
  return *this;
}


void StopWords::free () {
  Set<Word>::free();
}

