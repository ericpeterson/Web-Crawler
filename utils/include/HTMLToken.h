#ifndef HTML_TOKEN_H
#define HTML_TOKEN_H

#include <string>
#include <map>
using namespace std;

/**
 * A enumeration used to determine whether an HTMLToken is a TAG or TEXT.
 */
//!@ingroup htmltokenizer
enum HTMLTokenType
{
	/**
	 * Returned when the token is of the form <x ...>, where "x" could be anything.
	 */
	TAG_START,
	/**
	 * Returned when the token is of the form </x ...>, where "x" could be anything.
	 */
	TAG_END,
	/**
	 * Returned when the token is a comment tag of the form <!-- -->.
	 */
	COMMENT,
	/**
	 * Returned when the token is not a tag but is some text.
	 */
	TEXT,
	/**
	 * Returned when there are no more tokens to return.
	 */
	END
};

/**
 * Convert an HTMLTokenType to a String representation.  This is mostly useful for
 * debugging purposes.
 */
//!@ingroup htmltokenizer
string TypeToString(HTMLTokenType type);

class HTMLTokenizerTester;

/**
 * A Token of a HTML Document.  It could be either a tag or a word, depending on the
 * type variable.
 */
//!@ingroup htmltokenizer
class HTMLToken
{
public:
	friend class HTMLTokenizerTester;
	
	/**
	 * Standard Constructor that initializes member variables.
	 */
	HTMLToken(const string& tokenValue, HTMLTokenType tokenType);
	/**
	 * Copy Constructor that performs a deep copy of all member values.
	 */
	HTMLToken(const HTMLToken& toCopy);
	/**
	 * Standard Destructor that cleans up any memory used by this class.
	 */
	virtual ~HTMLToken();
	
	/**
	 * Return the value of the token, whether that be the first part of the HTML tag or
	 * it is the actual word value.
	 */
	string GetValue() const;
	
	/**
 	 * Get the type of this token, whether it be a TAG or a WORD.
 	 */
	HTMLTokenType GetType() const;
	
	/**
	 * Get whether the provided attribute was present in the originally parsed token or not.
	 */
	bool AttributeExists(const string& attribute);
	/**
	 * Get the associated value for the attribute of this token.  If the given attribute does not
	 * exist in the token, or the token is a WORD, then an empty string will be returned.
	 */
	string GetAttribute(const string& attribute);
	/**
	 * Either insert the provided attribute/value pair into the list of attributes for this token,
	 * or update the given attribute's value.  Note: If the HTMLTokenType is WORD, this function
	 * will not save the attribute/value pair to the list of attributes.
	 */
	void SetAttribute(const string& attribute, const string& value);
	
	
private:
	/**
	 * Return a lowercase copy of the provided string.
	 */
	string ToLower(const string& str);
	/**
	 * Return whether this token is a tag element (Start or End tag).
	 */
	bool IsTag() const;
	/**
	 * Either the word itself or the first part of the tag, such as "a" in <a>.
	 */
	string value;
	/**
	 * The type of this particular token, so either WORD or TAG.
	 */
	HTMLTokenType type;
	/**
	 * A collection of attribute/value pairs.  If the type of the token is WORD,
	 * this will always be empty.
	 */
	map<string, string> attributes;
};

#endif

