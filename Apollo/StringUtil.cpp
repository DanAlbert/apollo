#include "StringUtil.h"

void Chomp(std::string& str)
{
	if (str.empty())
		return;
	while (str.substr(str.length() - 1, 1) == "\n")
	{
		str = str.substr(0, str.length() - 1);
	}
}

void RemoveLeadingAndTrailingSpaces(std::string& str)
{
	if (str.empty())
		return;
	while (str.substr(0, 1) == " ")
	{
		str = str.substr(1);
	}
	while (str.substr(str.length() - 1, 1) == " ")
	{
		str = str.substr(0, str.length() - 1);
	}
}

void RemoveLeadingSpaces(std::string& str)
{
	if (str.empty())
		return;
	while (str.substr(0, 1) == " ")
	{
		str = str.substr(1);
	}
}

void RemoveTrailingSpaces(std::string& str)
{
	if (str.empty())
		return;
	while (str.substr(str.length() - 1, 1) == " ")
	{
		str = str.substr(0, str.length() - 1);
	}
}