/**
 * @file Configuration.h
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
 * An object representation of the data stored in the engine configuration
 * file.
 * 
 */
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "Ini.h"

#include "IOError.h"

namespace Apollo
{
	// Reimplement struct with Save() and Load()
	class APOLLO_API Configuration
	{
	public:
		Configuration(const char* szPath) throw(IOError);
		~Configuration(void);

		virtual bool Save(const char* szPath) throw(IOError);

		inline unsigned int	GetXResolution(void)		const	{	return m_XResolution;			}
		inline unsigned int	GetYResolution(void)		const	{	return m_YResolution;			}
		inline unsigned int	GetBitDepth(void)			const	{	return m_BitDepth;				}
		inline unsigned int	GetVRefreshRate(void)		const	{	return m_VRefreshRate;			}
		inline unsigned int	GetMultiSamplingLevel(void)	const	{	return m_MultiSamplingLevel;	}
		inline bool			GetVSync(void)				const	{	return m_VSync;					}
		inline bool			GetWindowed(void)			const	{	return m_Windowed;				}

	protected:
		// [Graphics]
		unsigned int	m_XResolution;
		unsigned int	m_YResolution;
		unsigned int	m_BitDepth;
		unsigned int	m_VRefreshRate;
		unsigned int	m_MultiSamplingLevel;
		bool			m_VSync;
		bool			m_Windowed;

		virtual void load(const char* szPath);
	};
}

#endif // CONFIGURATION_H
