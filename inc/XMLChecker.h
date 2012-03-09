#ifndef _XML_CHECKER_H_
#define _XML_CHECKER_H_

class XMLChecker {
  public:

    // Default constructor
    XMLChecker ();


    // Destructor
    ~XMLChecker ();


    /**
     *  Checks whether a value needs xml encoding
     *
     *  @param IN `value` The value to be checked
     *  @return true if the value needs xml encoding; false otherwise 
     */
    bool check (string & value);
};

#endif
