#include "HTMLTokenizer.h"

#include <cctype>

HTMLTokenizer::HTMLTokenizer(const std::string& htmlCode)
{
	htmlString = htmlCode;
	parsePosition = 0;
}
HTMLTokenizer::HTMLTokenizer(URLInputStream* input)
{
	htmlString = "";
	while(input->IsOpen() && !input->IsDone())
	{
		htmlString += input->Read();
	}
	parsePosition = 0;
}
HTMLTokenizer::~HTMLTokenizer()
{
}

HTMLToken HTMLTokenizer::GetNextToken()
{
	std::string tokenStr = GetNextTokenString();
	if(tokenStr == "")
	{
		return HTMLToken("", END);
	}
	else if(AtTag(tokenStr, 0))
	{
		return TagToToken(tokenStr);
	}
	else if(AtComment(tokenStr, 0))
	{
		return HTMLToken(tokenStr, COMMENT);
	}
	else
	{
		return HTMLToken(tokenStr, TEXT);
	}
}

bool HTMLTokenizer::HasNextToken() const
{
	return parsePosition < (int)htmlString.length();
}

HTMLToken HTMLTokenizer::TagToToken(const std::string& str) const
{
	// Find tag name
	int startPos = 1;
	HTMLTokenType type = TAG_START;
	
	if(str.length() >= 2 && str[startPos] == '/')
	{
		type = TAG_END;
		startPos++;
	}
	
	int runPos = startPos;
	while(runPos < (int)str.length() && IsWhitespace(str[runPos]) == false && str[runPos] != '>')
	{
		runPos++;
	}
	std::string tagName = str.substr(startPos, runPos - startPos);
	startPos = runPos;
	
	HTMLToken result(tagName, type);
	std::string key = "";
	char strTerm = ' ';
	
	// Find tag attributes
	while(startPos < (int)str.length() && str[startPos] != '>')
	{
		startPos = AfterWhitespace(startPos, str);
		
		// Find attribute name (key)
		runPos = startPos;
		while(runPos < (int)str.length() && IsWhitespace(str[runPos]) == false && str[runPos] != '=' && str[runPos] != '>')
		{
			runPos++;
		}
		key = str.substr(startPos, runPos - startPos);
		startPos = runPos;
		
		// Find equals sign
		startPos = AfterWhitespace(startPos, str);
		if(str[startPos] != '=')
		{
			// Return to beginning of while loop.
			continue;
		}
		else
		{
			// Move past equal sign
			startPos++;
		}
		
		// Find attribute value (value)
		startPos = AfterWhitespace(startPos, str);
		if(str[startPos] == '\"' || str[startPos] == '\'')
		{
			strTerm = str[startPos];
			startPos++;
		}
		else
		{
			strTerm = ' ';
		}
		
		runPos = startPos + 1;
		while(runPos < (int)str.length() && str[runPos] != '>' && str[runPos] != strTerm && !(strTerm == ' ' && IsWhitespace(str[runPos])))
		{
			runPos++;
		}
		
		// Add attribute
		result.SetAttribute(key, str.substr(startPos, runPos - startPos));
		
		if((strTerm == '\"' || strTerm == '\'') && runPos < (int)str.length())
		{
			runPos++;
		}
		startPos = runPos;
	}
	
	return result;
}
	
std::string HTMLTokenizer::GetNextTokenString()
{
	int end;
	
	if(HasNextToken() == false)
	{
		end = parsePosition;
	}
	else
	{
		if(AtTag())
		{
			end = FindEndOfTag();
		}
		else if(AtComment())
		{
			end = FindEndOfComment();
		}
		else
		{
			end = FindEndOfText();
		}
		
		// This moves the end position to the first character of the next token.
		end++;
	}
	
	std::string result = htmlString.substr(parsePosition, end - parsePosition);
	parsePosition = end;
	
	return result;
}

bool HTMLTokenizer::AtTag() const
{
	return AtTag(htmlString, parsePosition);
}

bool HTMLTokenizer::AtTag(const std::string& str, int pos) const
{
	if(pos >= (int)str.length() - 2)
	{
		return false;
	}
	else
	{
		return str[pos] == '<' && 
					(isalpha(str[pos + 1]) != 0 || // A tag can either have a character after the bracket or
					(str[pos + 1] == '/' && isalpha(str[pos + 2]) != 0)); // a slash followed by a character
	}
}

bool HTMLTokenizer::AtComment() const
{
	return AtComment(htmlString, parsePosition);
}

bool HTMLTokenizer::AtComment(const std::string& str, int pos) const
{
	if(pos >= (int)str.length() - 4)
	{
		return false;
	}
	else
	{
		return str.compare(pos, 4, "<!--") == 0;
	}
}

bool HTMLTokenizer::IsWhitespace(char toCheck) const
{
	return isspace(toCheck) != 0;
}

int HTMLTokenizer::AfterWhitespace(int startIndex, const std::string& str) const
{
	while(startIndex < (int)str.length() && IsWhitespace(str[startIndex]))
	{
		startIndex++;
	}
	return startIndex;
}


int HTMLTokenizer::FindEndOfTag() const
{
	int endTagPos = parsePosition + 1;
	
	while(endTagPos <= (int)htmlString.length() - 1 &&
			htmlString[endTagPos] != '>')
	{
		endTagPos++;
	}
	
	if(endTagPos >= (int)htmlString.length())
	{
		endTagPos--;
	}
	
	return endTagPos;
}

int HTMLTokenizer::FindEndOfComment() const
{
	// Move to the first character position after the opening bracket sequence.
	int endCommentPos = parsePosition + 4;
	
	while(endCommentPos <= (int)htmlString.length() - 3 && htmlString.compare(endCommentPos, 3, "-->") != 0)
	{
		endCommentPos++;
	}
	
	if(endCommentPos > (int)htmlString.length() - 3)
	{
		// If the end of the comment was the end of the html string, then just set the end of the comment position
		// to be the end of the string.
		endCommentPos = htmlString.length() - 1;
	}
	else
	{
		// If there actually is an end of a comment bracket, the jump forward two places so that we are now pointing
		// at the ending bracket, rather than the first dash.
		endCommentPos += 2;
	}
	
	return endCommentPos;
}

int HTMLTokenizer::FindEndOfText() const
{
	int endTextPos = parsePosition + 1;
	
	while(endTextPos < (int)htmlString.length() &&
			htmlString[endTextPos] != '<')
	{
		endTextPos++;
	}
	
	// This is because the while loop is terminated when we find the end of the string or
	// the tag opening character, so to get the last text character, we have to step back once.
	endTextPos--;
	
	return endTextPos;
}

