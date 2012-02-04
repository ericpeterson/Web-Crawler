#ifndef HTML_TOKENIZER_H
#define HTML_TOKENIZER_H

#include <string>
#include "URLInputStream.h"
#include "HTMLToken.h"

//!@defgroup htmltokenizer HTML Tokenizing Utils
//!Functions used to break apart an html string into tokens
//!@li Class HTMLTokenizer Used by students to break html strings into tokens.
//!@li Class HTMLToken The token that is returned when the student requests to get the next token from an HTMLTokenizer.

class HTMLTokenizerTester;

/**
 * The HTMLTokenizer class is used to parse the html language into tokens.
 */
//!@ingroup htmltokenizer
class HTMLTokenizer
{
public:
	friend class HTMLTokenizerTester;
	
	/**
	 * Initialize the HTMLTokenizer with an html string that you have already downloaded.
	 */
	HTMLTokenizer(const std::string& htmlCode);
	/**
	 * Initialize the HTMLTokenizer with an InputStream that the HTMLTokenizer will then
	 * retrieve all of the HTML code from.  When the constructor is finished, the
	 * InputStream that you pass in should be done and should be closed.
	 */
	HTMLTokenizer(URLInputStream* input);
	/**
	 * Destructor that cleans up any memory needing to be deleted by this tokenizer.
	 */
	virtual ~HTMLTokenizer();
	
	/**
	 * Get the next HTMLToken in the html string.
	 */
	HTMLToken GetNextToken();
	
	/**
	 * Return whether the tokenizer has another token to return.
	 */
	bool HasNextToken() const;
	
private:
	/**
	 * Convert a tag string into an HTMLToken object.
	 */
	HTMLToken TagToToken(const std::string& str) const;
	
	/**
	 * Get the next string token from the HTML string contined in this HTMLTokenizer.  If the
	 * current parsing position is at the end of the string, the empty string is returned.
	 */
	std::string GetNextTokenString();
	
	/**
	 * Returns whether the current parse position is at the beginning of a tag or not.
	 */
	bool AtTag() const;
	/**
	 * Returns whether the given position in the given string is at the beginning of a tag or not.
	 */
	bool AtTag(const std::string& str, int pos) const;
	/**
	 * Returns whether the current parse position is at the beginning of a comment or not.
	 */
	bool AtComment() const;
	/**
	 * Returns whether the given position in the given string is at the beginning of a comment or not.
	 */
	bool AtComment(const std::string& str, int pos) const;
	/**
	 * Returns whether the given character is a whitespace character or not.
	 */
	bool IsWhitespace(char toCheck) const;
	
	/**
	 * Return the first non-whitespace index in the given string after the given starting index.
	 */
	int AfterWhitespace(int startIndex, const std::string& str) const;
	
	/**
	 * Return the end position of the current tag being looked at.
	 */
	int FindEndOfTag() const;
	
	/**
	 * Return the end position of the current comment being looked at.
	 */
	int FindEndOfComment() const;
	
	/**
	 * Return the end position of the current block of text being looked at.
	 */
	int FindEndOfText() const;
	
	/**
	 * The HTML String to parse and return tokens from.
	 */
	std::string htmlString;
	
	/**
	 * The current position inside the htmlString that the parsing process is at.
	 */
	int parsePosition;
};


#endif

