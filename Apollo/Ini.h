#ifndef __INI_H__
#define __INI_H__

#include <fstream>
#include <hash_map>
#include <string>
#include <sstream>

#include "Debug.h"
#include "StringUtil.h"

namespace Apollo
{
	typedef stdext::hash_map<std::string, stdext::hash_map<std::string, std::string> > IniDictionary;

	class Ini
	{
	public:
		Ini(std::string szPath);
		virtual ~Ini(void);

		virtual bool Open(std::string szPath);

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
	};
}

#endif // __INI_H__