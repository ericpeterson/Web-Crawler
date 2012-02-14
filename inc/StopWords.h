#ifndef _STOP_WORDS_H_
#define _STOP_WORDS_H_

typedef string Word;

/**
 *  Loads and stores the stop words from a file into memory
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Load and store stop words
 */
class StopWords : BST<Word> {
  public:

    /**
     *  Default constructor
     */
    StopWords ();


    /**
     *  Destructor
     */
    ~StopWords ();


    /**
     *  Copy constructor
     *
     *  @param swCopy The StopWords object to be copied
     */
    StopWords (const StopWords & swCopy);


    /**
     *  Overloaded assignment operator
     *
     *  @param swCopy The StopWords object to be copied
     *
     *  @return A reference to this StopWords object
     */
    StopWords & operator = (const StopWords & swCopy);

  private:

    /**
     *  Performs the leg-work for the copy constructor and assignment operator
     *  @param swCopy The StopWords object to be copied
     *
     *  @return A reference to this StopWords
     */
    StopWords & copy (const StopWords & swCopy);


    /**
     *  Deallocates heap memory used by this StopWords
     */
    void free ();
};

#endif
