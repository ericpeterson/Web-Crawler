#include "HTMLToken.h"

#include <cctype>

string TypeToString(HTMLTokenType type)
{
	string result = "";
	
	switch(type)
	{
		case TAG_START:
			result = "TAG_START";
			break;
			
		case TAG_END:
			result = "TAG_END";
			break;
			
		case TEXT:
			result = "TEXT";
			break;
			
		case END:
			result = "END";
			break;
			
		default:
			result = "ERROR!  Contact TA's about TypeToString() in HTMLToken.cpp.";
			break;
	}
	
	return result;
}

HTMLToken::HTMLToken(const string& tokenValue, HTMLTokenType tokenType)
{
	value = tokenValue;
	type = tokenType;
}
HTMLToken::HTMLToken(const HTMLToken& toCopy)
{
	value = toCopy.value;
	type = toCopy.type;
	attributes = toCopy.attributes;
}
HTMLToken::~HTMLToken()
{
}

string HTMLToken::GetValue() const
{
	return value;
}

HTMLTokenType HTMLToken::GetType() const
{
	return type;
}

bool HTMLToken::AttributeExists(const string& attribute)
{
	return attributes.find(ToLower(attribute)) != attributes.end();
}
string HTMLToken::GetAttribute(const string& attribute)
{
	string lowerAtt = ToLower(attribute);
	if( IsTag() == false || attributes.find(lowerAtt) == attributes.end())
	{
		return string("");
	}
	else
	{
		return attributes[lowerAtt];
	}
}
void HTMLToken::SetAttribute(const string& attribute, const string& value)
{
	if(IsTag())
	{
		attributes[ToLower(attribute)] = value;
	}
}

string HTMLToken::ToLower(const string& str)
{
	string result = str;
	for(int i = 0; i < (int)result.length(); i++)
	{
		result[i] = tolower(result[i]);
	}
	return result;
}

bool HTMLToken::IsTag() const
{
	return type == TAG_START || type == TAG_END;
}


