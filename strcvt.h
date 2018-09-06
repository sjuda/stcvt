#pragma once
#include "iostream"
#define FLOATLIMIT 340000000
#define INTLIMITMIN -2147483648LL
#define INTLIMITMAX 2147483647LL
template<typename T> inline T FromString(const::std::string& str);

class CastExeption : public std::runtime_error
{
public:
	CastExeption(std::string DefaultError) : runtime_error(DefaultError.c_str()) {}
};

class UnknowTypeExeption : public CastExeption
{
public:
	UnknowTypeExeption() : CastExeption("Error: Unknow Type") {}
};

class OverflowErrorExeption : public CastExeption
{
public:
	OverflowErrorExeption() : CastExeption("Error: String is big") {}
};

class BadCharsErrorExeption : public CastExeption
{
public:
	BadCharsErrorExeption() : CastExeption("Error: String Has Bad Chars") {}
};

class NULLStringErrorExeption : public CastExeption
{
public:
	NULLStringErrorExeption() : CastExeption("Error: String is null length") {}
};

inline bool IsValidCharInt(char sym, bool NotOtr)
{
	if ((sym >= '0' && sym <= '9') || NotOtr == false && sym == '-')
		return true;
	return false;
}

inline bool IsValidCharFloat(char sym, bool NotOtr, bool NotFl)
{
	if ((sym >= '0' && sym <= '9') || (NotOtr == false && sym == '-') || (NotFl == false && (sym == '.' || sym == ',')))
		return true;
	return false;
}

inline long long StringToDec(const::std::string& str, long long min, long long max)
{
	int i = 0;
	bool Type = (str[0] == '-');
	if (Type == true)
		i++;
	long long ret = (str[i++] - '0');
	for (; i < (int)str.length(); i++)
	{
		ret *= 10;
		ret += (str[i] - '0');
		if (Type == true && ret > (min*(-1)))
			throw OverflowErrorExeption();
		if (Type == false && ret > max)
			throw OverflowErrorExeption();
	}
	if (Type == true)
		ret *= -1;
	return ret;
}

TEMPLATE inline T FromString(const::std::string& str)
{
	if(str.length() == 0)
		throw NULLStringErrorExeption();
	bool HasFl = false;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (typeid(T) != typeid(float))
		{
			if (!IsValidCharInt(str[i], i != 0))
				throw BadCharsErrorExeption();
		}
		else
		{
			if (!IsValidCharFloat(str[i], i != 0, HasFl))
				throw BadCharsErrorExeption();
			if (str[i] == ',' || str[i] == '.')
				HasFl = true;
		}
	}
	if (typeid(T) == typeid(int))
		return (T)StringToDec(str.c_str(), INTLIMITMIN, INTLIMITMAX);
	else if (typeid(T) == typeid(float))
	{
		size_t hasfl = str.find(',');
		if(hasfl == string::npos)
			hasfl = str.find('.');
		if (hasfl == string::npos)
			return (T)StringToDec(str.c_str(), -FLOATLIMIT, FLOATLIMIT);
		string temp = str;
		temp.erase(hasfl, 1);
		T ret = (T)StringToDec(temp.c_str(), -FLOATLIMIT, FLOATLIMIT);
		ret *= (T)pow(10, -(((int)str.length() - (int)hasfl) - 1));
		return (T)ret;
	}
	else if (typeid(T) == typeid(bool))
	{
		if(str.length() != 1 || (str[0] != '0' && str[0] != '1'))
			throw BadCharsErrorExeption();
		return (T)(str[0] == '1');
	}
	throw UnknowTypeExeption();
}
