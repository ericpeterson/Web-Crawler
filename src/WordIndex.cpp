#include <string>
#include <iostream>
#include "Map.h"
#include "Set.h"
#include "Occurrence.h"
#include "WordIndex.h"
using namespace std;

typedef string Word;
typedef Set<Occurrence> OccurrenceSet;

WordIndex::WordIndex () : Map<Word, OccurrenceSet>::Map() {}


WordIndex::~WordIndex () {
  free();
}


WordIndex::WordIndex (const WordIndex & wiCopy) {
  copy(wiCopy);
}


WordIndex & WordIndex::operator = (const WordIndex & wiCopy) {
  free();
  return copy(wiCopy);
}


WordIndex & WordIndex::copy (const WordIndex & wiCopy) {
  Map<Word, OccurrenceSet>::copy(wiCopy);
  return *this;
}


void WordIndex::free () {
  Map<Word, OccurrenceSet>::free();
}


bool WordIndex::Test (ostream & os) {
  bool success = true;

  WordIndex myIndex;

  return success;
}
