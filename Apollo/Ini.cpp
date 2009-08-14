#include "Ini.h"

namespace Apollo
{
	Ini::Ini(std::string szPath)
	{
		if (!Open(szPath))
		{
			return;
		}
	}

	Ini::~Ini(void)
	{
		m_IniData.clear();
	}

	bool Ini::Open(std::string szPath)
	{
		m_fStream.open(szPath.c_str(), std::ifstream::in);

		std::string section;
		std::string key;
		std::string value;

		while (m_fStream.good())
		{
			char* line = (char*)malloc(sizeof(char) * 120);
			m_fStream.getline(line, 120);
			std::string str = line;
			Chomp(str);
			RemoveLeadingAndTrailingSpaces(str);

			if (!strcmp(str.substr(0, 1).c_str(), "["))
			{
				size_t cmind = str.find("#");
				if (cmind == std::string::npos)
				{
					section = str.substr(1, str.length() - 2);
					Chomp(section);
					RemoveLeadingAndTrailingSpaces(section);
				}
				else
				{
				}
			}
			else if (!strcmp(str.substr(0, 1).c_str(), "#"))
			{
				// Line is a comment.
				// Skip it.
			}
			else
			{
				if (section.empty())
				{
					Log("[IniFile] Error parsing Ini file, no section defined.");
				}
				else
				{
					size_t eqind = str.find("=");
					size_t cmind = str.find("#");
					if (cmind == std::string::npos)
					{
						// Line contains no comment.
						// Read the whole line.
						key = str.substr(0, eqind);
						value = str.substr(eqind + 1);
						Chomp(key);
						RemoveLeadingAndTrailingSpaces(key);
						Chomp(value);
						RemoveLeadingAndTrailingSpaces(value);
						m_IniData[section][key] = value;
						key.clear();
						value.clear();
					}
					else
					{
						// Line contains a comment.
						// Read until the comment.
						key = str.substr(0, eqind);
						value = str.substr(eqind + 1, cmind - eqind - 1);
						Chomp(key);
						RemoveLeadingAndTrailingSpaces(key);
						Chomp(value);
						RemoveLeadingAndTrailingSpaces(value);
						m_IniData[section][key] = value;
						key.clear();
						value.clear();
					}
				}
			}
		}

		return true;
	}

	const char*	Ini::GetString(const char* szSection, const char* szKey)
	{
		return m_IniData[szSection][szKey].c_str();
	}
	
	bool Ini::GetBool(const char* szSection, const char* szKey)
	{
		bool ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> ret;
		return ret;
	}
	
	char Ini::GetChar(const char* szSection, const char* szKey)
	{
		char ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> ret;
		return ret;
	}
	
	unsigned char Ini::GetByte(const char* szSection, const char* szKey)
	{
		int temp;
		unsigned char ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> temp;
		ret = (unsigned char)temp;
		return ret;
	}
	
	int Ini::GetInt(const char* szSection, const char* szKey)
	{
		int ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> ret;
		return ret;
	}
	
	unsigned int Ini::GetUInt(const char* szSection, const char* szKey)
	{
		unsigned int ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> ret;
		return ret;
	}

	short Ini::GetShort(const char* szSection, const char* szKey)
	{
		short ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> ret;
		return ret;
	}

	unsigned short Ini::GetUShort(const char* szSection, const char* szKey)
	{
		unsigned short ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> ret;
		return ret;
	}

	long Ini::GetLong(const char* szSection, const char* szKey)
	{
		long ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> ret;
		return ret;
	}

	unsigned long Ini::GetULong(const char* szSection, const char* szKey)
	{
		unsigned long ret;
		std::istringstream i(m_IniData[szSection][szKey]);
		i >> ret;
		return ret;
	}
}