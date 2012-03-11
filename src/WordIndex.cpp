#include <string>
#include <iostream>
#include <cassert>
#include <sstream>

#include "Map.h"
#include "Set.h"
#include "Occurrence.h"
#include "WordIndex.h"
#include "URL.h"
#include "BST.h"

#include "StringUtil.h"
#include "CS240Exception.h"

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


int WordIndex::GetSize () {
  return BST< MapNode<Word, OccurrenceSet> >::GetSize();
}


void WordIndex::free () {
  Map<Word, OccurrenceSet>::free();
}


void WordIndex::Insert (const Word & word, const URL & url) {
  bool containsWord = Map<Word, OccurrenceSet>::Contains(word);

  if (true == containsWord) {
    // The word is already in this index -- increment occurrence
    OccurrenceSet dummySet;
    MapNode<Word, OccurrenceSet> mapNode(word, dummySet);
    BSTNode< MapNode<Word, OccurrenceSet> >* node = 
      BST< MapNode<Word, OccurrenceSet> >::Find(mapNode);

    Occurrence wrapper(url);
    BSTNode<Occurrence> * oNode = node->GetValue().GetValue().Find(wrapper);

    if (NULL != oNode) {
      // word occurred on a known web page
      oNode->GetValue().increment();
    } else {
      // word has an occurrence on a new web page
      bool wasInserted = node->GetValue().GetValue().Insert(wrapper);
      assert(wasInserted == true);
    }
  } else {
    // We need to add the word to this index
    OccurrenceSet set;
    Occurrence occurrence(url);
    bool wasAdded = set.Insert(occurrence);
    assert(wasAdded == true);

    Map<Word, OccurrenceSet>::Insert(word, set);
  }
}


void WordIndex::traverseOccurrences (BSTNode<Occurrence>* node, ostream & stream) {
  if (NULL == node) {
    return;
  }

  if (NULL != node->GetLeft()) {
    traverseOccurrences(node->GetLeft(), stream);
  }

  if (NULL != node->GetRight()) {
    traverseOccurrences(node->GetRight(), stream);
  }

  stream << ("      <occurrence>\n");
  stream << ("        <url>\n          ");
  try {
    stream << StringUtil::EncodeToXmlCopy(node->GetValue().getURL().getFullURL());
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }
  stream << ("\n        </url>\n");
  stream << ("        <count>");

  // convert count (int) to a string
  try {
    stringstream ss;
    ss << node->GetValue().getCount();
    string countStr(ss.str());
    stream << StringUtil::EncodeToXmlCopy(countStr);
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }
  stream << ("</count>\n");
  stream << ("      </occurrence>\n");
}


void WordIndex::traverseWords (
    BSTNode< MapNode<string, OccurrenceSet> >* node
  , ostream & stream
) {
  if (NULL == node) {
    return;
  }

  if (NULL != node->GetLeft()) {
    traverseWords(node->GetLeft(), stream);
  }
  
  if (NULL != node->GetRight()) {
    traverseWords(node->GetRight(), stream);
  }

  stream << ("    <word>\n");
  stream << ("      <value>");
  stream.flush();
  try {
    stream << StringUtil::EncodeToXmlCopy(node->GetValue().GetKey());
  } catch (CS240Exception & exception) {
    cout << exception.GetMessage() << endl;
  }
  stream << ("</value>\n");
  traverseOccurrences(node->GetValue().GetValue().GetRoot(), stream);
  stream << ("    </word>\n");
}


void WordIndex::traverse (ostream & stream) {
  traverseWords(GetRoot(), stream);
}


ostream & operator << (ostream & stream, WordIndex & index) {
  index.traverse(stream);
  return stream;
}


bool WordIndex::Test (ostream & os) {
  bool success = true;
  const int PAGES = 3;
  const int WORDS = 30;
  URL urls[PAGES] = {
      URL("http://www.google.com/index.html")
    , URL("file:///home/file.txt")
    , URL("http://www.msn.com/sports.html")
  };
  Word words[WORDS] = {
      "and", "the", "a", "wood", "couch", "potato", "Henry", "the", "a", "and"
    , "a", "house", "dog", "wood", "couch", "frisbee", "green", "then", "why", "how"
    , "a", "a", "yes", "no", "maybe", "Henry", "the", "frisbee", "green", "couch"
  };

  WordIndex wordIndex;

  for (int i = 0; i < PAGES; i++) {
    for (int j = 0; j < WORDS; j++) {
      wordIndex.Insert(words[j], urls[i]);
    }
  }

  OccurrenceSet set = wordIndex.GetValue("a");

  BSTNode<Occurrence>* node = set.Find(Occurrence(urls[1]));
  TEST (NULL != node);

  Occurrence current = node->GetValue();
  TEST(current.getURL().getFullURL() == urls[1].getFullURL());
  TEST(current.getCount() == 5);

  return success;
}
