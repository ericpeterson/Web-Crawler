#ifndef _WORD_INDEX_H_
#define _WORD_INDEX_H_

typedef string Word;

/**
 *  Data structure that maps words to web page occurrences
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Store index that maps words to pages
 */
class WordIndex : Map<Word> {
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

#endif

