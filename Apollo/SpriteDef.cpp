/**
 * @file SpriteDef.cpp
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
 * An object representation of the data stored in a Sprite definition file.
 * 
 */
#include "SpriteDef.h"

namespace Apollo
{
	SpriteDef::SpriteDef(const char* szPath) :
		m_Frames(NULL),
		m_nFrames(0),
		m_frameTime(0)
	{
		if (!LoadFromFile(szPath))
		{
			Release();
			return;
		}
	}

	SpriteDef::~SpriteDef(void)
	{
		Release();
	}

	inline const char* SpriteDef::GetFrame(int i) const
	{
		return m_Frames[i];
	}

	inline const int SpriteDef::GetNFrames(void) const
	{
		return m_nFrames;
	}

	inline const int SpriteDef::GetFrameTime(void) const
	{
		return m_frameTime;
	}

	// TODO: Overload this method. The other method should accept a
	// TiXmlElement* to <Sprite>
	bool SpriteDef::LoadFromFile(const char* szPath)
	{
		Release();

		TiXmlDocument doc(szPath);
		if (!doc.LoadFile(TIXML_ENCODING_UTF8))
			return false;

		TiXmlHandle hDoc(&doc);
		TiXmlElement* elem;
		TiXmlHandle hRoot(0);

		// root
		elem = hDoc.FirstChildElement().Element(); // /Sprite
		hRoot = TiXmlHandle(elem);
		elem->QueryIntAttribute("nFrames", &m_nFrames);
		elem->QueryIntAttribute("frame-time", &m_frameTime);

		m_Frames = new char*[m_nFrames];
		memset(m_Frames, 0, m_nFrames * sizeof(char*));

		elem = hRoot.FirstChild("Frame").Element(); // /Sprite/Frame
		for (int i = 0; i < m_nFrames; ++i)
		{
			if (elem)
			{
				const char* text = elem->GetText();
				m_Frames[i] = new char[strlen(text) + 1];
				
				strcpy(m_Frames[i], text);

				elem = elem->NextSiblingElement();
			}
		}

		return true;
	}

	void SpriteDef::Release(void)
	{
		if (m_Frames)
		{
			for (int i = 0; i < m_nFrames; ++i)
			{
				if (m_Frames[i])
				{
					delete [] m_Frames[i];
					m_Frames[i] = NULL;
				}
			}

			delete [] m_Frames;
			m_Frames = NULL;
		}
	}
}
