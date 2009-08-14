#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Ini.h"

namespace Apollo
{
	// Reimplement struct with Save() and Load()
	class Configuration
	{
	public:
		Configuration(void);
		Configuration(const char* szPath);
		~Configuration(void);

		virtual bool Save(const char* szPath);
		virtual bool Load(const char* szPath);

		inline unsigned int	GetXResolution(void)	const	{	return m_XResolution;	}
		inline unsigned int	GetYResolution(void)	const	{	return m_YResolution;	}
		inline unsigned int	GetBitDepth(void)		const	{	return m_BitDepth;		}
		inline unsigned int	GetVRefreshRate(void)	const	{	return m_VRefreshRate;	}
		inline bool			GetVSync(void)			const	{	return m_VSync;			}
		inline bool			GetWindowed(void)		const	{	return m_Windowed;		}

	protected:
		// [Graphics]
		unsigned int	m_XResolution;
		unsigned int	m_YResolution;
		unsigned int	m_BitDepth;
		unsigned int	m_VRefreshRate;
		bool			m_VSync;
		bool			m_Windowed;
	};
}

#endif // __CONFIGURATION_H__