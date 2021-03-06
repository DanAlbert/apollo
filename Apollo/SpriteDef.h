/**
 * @file SpriteDef.h
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
 * An object representation of the data stored in a Sprite definition file.
 * 
 */
#ifndef SPRITEDEF_H
#define SPRITEDEF_H

#include "Apollo.h"

#include <tinyxml.h>

#include "IOError.h"

namespace Apollo
{
	class APOLLO_API SpriteDef
	{
	public:
		SpriteDef(const char* szPath) throw(IOError);
		~SpriteDef(void);

		inline const char*	GetFrame(int i) const;
		inline const int	GetNFrames(void) const;
		inline const int	GetFrameTime(void) const;

		bool LoadFromFile(const char* szPath) throw(IOError);
		void Release(void);

	protected:
		char**	m_Frames;
		int		m_nFrames;
		int		m_frameTime;
	};
}

#endif // SPRITEDEF_H
