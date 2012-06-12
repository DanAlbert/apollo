/**
 * @file Ini.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
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
#ifndef INI_H
#define INI_H

#include <fstream>
#include <hash_map>
#include <string>
#include <sstream>

#include "Debug.h"
#include "StringUtil.h"

#include "IOError.h"

namespace Apollo
{
	typedef stdext::hash_map<std::string, stdext::hash_map<std::string, std::string> > IniDictionary;

	class Ini
	{
	public:
		Ini(std::string szPath) throw(IOError);
		virtual ~Ini(void);

		virtual const char*	GetString(const char* szSection, const char* szKey);
		virtual bool GetBool(const char* szSection, const char* szKey);
		virtual char GetChar(const char* szSection, const char* szKey);
		virtual unsigned char GetByte(const char* szSection, const char* szKey);
		virtual int GetInt(const char* szSection, const char* szKey);
		virtual unsigned int GetUInt(const char* szSection, const char* szKey);
		virtual short GetShort(const char* szSection, const char* szKey);
		virtual unsigned short GetUShort(const char* szSection, const char* szKey);
		virtual long GetLong(const char* szSection, const char* szKey);
		virtual unsigned long GetULong(const char* szSection, const char* szKey);

	protected:
		std::fstream	m_fStream;
		IniDictionary	m_IniData;

		virtual bool open(std::string szPath);
	};
}

#endif // INI_H
