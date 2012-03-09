#ifndef _XML_GENERATOR_H_
#define _XML_GENERATOR_H_

#include <string>
#include "URL.h"
#include "PageSet.h"
#include "WordIndex.h"
using namespace std;


/**
 *  Generates the XML output of the web crawler
 *
 *  (TA use) Class Responsibilities:
 *
 *    * Generate XML output file
 */
class XMLGenerator {
  public:

    /**
     *  Overloaded constructor
     *
     *  @param `outFile` The output XML file
     */
    XMLGenerator (string & outFile);


    /**
     *  Destructor
     */
    ~XMLGenerator ();


    /**
     *  Copy contructor
     *
     *  @param xgCopy The XMLGenerator object to be copied
     */
    XMLGenerator (const XMLGenerator & xgCopy);


    /**
     *  Overloaded assignment operator
     *
     *  @param xgCopy The XMLGenerator object to be copied
     *
     *  @return A reference to this XMLGenerator
     */
    XMLGenerator & operator = (const XMLGenerator & xgCopy);


    /**
     *  Generates XML output for an indexed web page
     *
     *  @param startURL The first URL indexed by the web crawler
     *
     *  @param pages A set of pages indexed by the web crawler
     *
     *  @param words The mapping of indexed words to the web pages on which
     *               they were found
     *
     *  @return The XML Document 
     */
    void generate (URL & startURL, PageSet & pages, WordIndex & words);

  private:

    string xmlFile;

    /**
     *  Performs the leg-work for the copy constructor and overloaded
     *  assignment operator.
     *
     *  @param xgCopy The XMLGenerator object to be copied
     *
     *  @return A reference to this XMLGenerator
     */
    XMLGenerator & copy (const XMLGenerator & xgCopy);


    /**
     *  Deallocates all heap memory created by this XMLGenerator
     */
    void free ();
};

#endif
