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