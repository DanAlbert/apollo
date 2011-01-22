#include "Configuration.h"

namespace Apollo
{
	Configuration::Configuration(void)
	{
	}

	Configuration::Configuration(const char* szPath)
	{
		Load(szPath);
	}

	Configuration::~Configuration(void)
	{
	}

	bool Configuration::Save(const char* szPath)
	{
		return false;
	}

	bool Configuration::Load(const char* szPath)
	{
		Ini ini(szPath);

		// [Graphics]
		m_XResolution = ini.GetUShort("Graphics", "x_resolution");
		m_YResolution = ini.GetUShort("Graphics", "y_resolution");
		m_BitDepth = ini.GetByte("Graphics", "bit_depth");
		m_VRefreshRate = ini.GetByte("Graphics", "vertical_refresh_rate");
		m_MultiSamplingLevel = ini.GetUInt("Graphics", "multisampling_level");
		m_VSync = ini.GetBool("Graphics", "vsync");
		m_Windowed = ini.GetBool("Graphics", "windowed");

		return true;
	}
}