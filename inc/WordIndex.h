#ifndef _WORD_INDEX_H_
#define _WORD_INDEX_H_

#include <string>
#include <iostream>
#include "Map.h"
#include "Set.h"
#include "URL.h"
#include "Occurrence.h"
using namespace std;

typedef string Word;
typedef Set<Occurrence> OccurrenceSet;

/**
 *  Data structure that maps words to web page occurrences
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Store index that maps words to pages
 */
class WordIndex : Map<Word, OccurrenceSet> {
  public:

    /**
     *  Default constructor
     */
    WordIndex ();


    /**
     *  Destructor
     */
    ~WordIndex ();


    /**
     *  Copy constructor
     *
     *  @param wiCopy The WordIndex object to be copied
     */
    WordIndex (const WordIndex & wiCopy);


    /**
     *  Overloaded assignment operator
     *
     *  @param wiCopy The WordIndex object to be copied
     *
     *  @return A reference to this WordIndex object
     */
    WordIndex & operator = (const WordIndex & wiCopy);


    // Getter for `size`
    int GetSize ();


    /**
     *  Inserts a new occurrence of a Word into the index
     *
     *  @param IN `word` The new word occurrence
     *  @param IN `url` The web page on which `word` is found
     */
    void Insert (const Word & word, const URL & url);


    /**
     *  Unit test for the WordIndex class
     *
     *  @param `os` A reference to the output stream where the test result will
     *    be written
     *  @return true if all tests pass; false otherwise. 
     */
    static bool Test (ostream & os);


    /**
     *  Traverse the Set of occurrences recursively
     *
     *  @param `node` The current node in the Set
     *  @param OUT `stream` The stream where the word index will be written
     */
    void traverseOccurrences (BSTNode<Occurrence>* node, ostream & stream);


    /**
     *  Traverse this Word index of recursively and print elements to `stream`
     *
     *  @param `node` The current node in the Set
     *  @param OUT `stream` The stream where the word index will be written
     */
    void traverseWords (BSTNode< MapNode<string, OccurrenceSet> >* node, ostream & stream);


    /**
     *  Begins traversing this Word index
     *
     *  @param OUT `stream` The stream where the word index will be written
     */
    void traverse (ostream & stream);

  private:

    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *
     *  @param wiCopy The WordIndex object to be copied
     *
     *  @return A reference to this WordIndex
     */
    WordIndex & copy (const WordIndex & wiCopy);


    /**
     *  Deallocates heap memory used by this WordIndex
     */
    void free ();
};


/**
 *  Overloaded insertion operator
 *
 *  @param `stream` The stream associated with the insertion operator
 *  @param `index` The WordIndex object to write to `stream`
 */
ostream & operator << (ostream & stream, WordIndex & index);

#endif

