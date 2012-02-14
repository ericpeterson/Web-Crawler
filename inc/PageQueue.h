#ifndef _PAGE_QUEUE_H_
#define _PAGE_QUEUE_H_

#include "Page.h"

typedef int Size;

/**
 *  Stores the pages yet to be processed
 *
 *  (TA use) Class Responsibilities:
 *  
 *    * Keep track of yet-to-be indexed pages
 */
class PageQueue : Queue<Page> {
  public:

    /**
     *  Default constructor
     */
    PageQueue ();


    /**
     *  Destructor
     */
    ~PageQueue ();


    /**
     *  Copy constructor
     *
     *  @param pqCopy The PageQueue object to be copied
     */
    PageQueue (const PageQueue & pqCopy);


    /**
     *  Overloaded assignment operatora
     *
     *  @param pqCopy The PageQueue object to be copied
     *
     *  @return A reference to this PageQueue object
     */
    PageQueue & operator = (const PageQueue & pqCopy);


    /**
     *  Checks if this PageQueue has any elements
     *
     *  @return true if the size of this PageQueue is zero; false otherwise.
     */
    bool isEmpty ();


    /**
     *  Gets the next Page from the queue and removes it from the queue
     *
     *  @return The next page in the queue
     */
    Page dequeue ();


    /**
     *  Adds a new page to the Queue
     *
     *  @param newPage The new page to be added to the queue
     */
    void enqueue (Page newPage);

    private:

      // The number of elements in this PageQueue. Useful for determining if
      // the queue is empty.
      Size size;

      /**
       *  Performs the leg-word for the copy constructor and the overloaded
       *  assignment operator
       *  
       *  @param pqCopy The PageQueue object to be copied
       *
       *  @return A reference to this PageQueue object
       */
      PageQueue & copy (const PageQueue & pqCopy);


      /**
       *  Deallocates any memory used by this PageQueue
       */
      void free ();
};

#endif
