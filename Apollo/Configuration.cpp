/**
 * @file Configuration.cpp
 * @author Dan Albert <dan@gingerhq.net>
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
 * An object representation of the data stored in the engine configuration
 * file.
 * 
 */
#include "Configuration.h"

namespace Apollo
{
	Configuration::Configuration(const char* szPath)
	{
		this->load(szPath);
	}

	Configuration::~Configuration(void)
	{
	}

	bool Configuration::Save(const char* szPath)
	{
		return false;
	}

	void Configuration::load(const char* szPath)
	{
		Ini ini(szPath);

		// [Graphics]
		m_XResolution = ini.GetUShort("Graphics", "x_resolution");
		m_YResolution = ini.GetUShort("Graphics", "y_resolution");
		m_BitDepth = ini.GetByte("Graphics", "bit_depth");
		m_VRefreshRate = ini.GetByte("Graphics", "vertical_refresh_rate");
		m_MultiSamplingLevel = ini.GetUInt("Graphics", "multisampling_level");
		m_VSync = ini.GetBool("Graphics", "vsync");
		m_Windowed = ini.GetBool("Graphics", "windowed");
	}
}
