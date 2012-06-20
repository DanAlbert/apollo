/**
 * @file Ini.cpp
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/19/2012
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2012 Dan Albert
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * @section DESCRIPTION
 * 
 * Basic INI (key-value) file parser.
 * 
 */
#include "Ini.h"

namespace Apollo
{
	Ini::Ini(std::string szPath) throw(IOError)
	{
		if (!this->open(szPath))
		{
			throw IOError(ERR_APOLLO_CONFIGURATION_LOAD);
		}
	}

	Ini::~Ini(void)
	{
		m_IniData.clear();
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

	bool Ini::open(std::string szPath)
	{
		m_fStream.open(szPath.c_str(), std::ifstream::in);
		if (m_fStream.fail())
		{
			return false;
		}

		std::string section;
		std::string key;
		std::string value;

		while (m_fStream.good())
		{
			char* line = (char*)malloc(sizeof(char) * 120);
			m_fStream.getline(line, 120);
			std::string str = line;
			Chomp(str);
			TrimSpaces(str);

			if (!strcmp(str.substr(0, 1).c_str(), "["))
			{
				size_t cmind = str.find(";");
				if (cmind == std::string::npos)
				{
					section = str.substr(1, str.length() - 2);
					Chomp(section);
					TrimSpaces(section);
				}
				else
				{
				}
			}
			else if (!strcmp(str.substr(0, 1).c_str(), ";"))
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
					size_t cmind = str.find(";");
					if (cmind == std::string::npos)
					{
						// Line contains no comment.
						// Read the whole line.
						key = str.substr(0, eqind);
						value = str.substr(eqind + 1);
						Chomp(key);
						TrimSpaces(key);
						Chomp(value);
						TrimSpaces(value);
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
						TrimSpaces(key);
						Chomp(value);
						TrimSpaces(value);
						m_IniData[section][key] = value;
						key.clear();
						value.clear();
					}
				}
			}
		}

		return true;
	}
}
