#include "Sprite.h"

#include "SceneManager.h"

namespace Apollo
{
	Sprite::Sprite(const char* path, RenderSystem* renderSystem) :
		m_Textures(NULL),
		m_ResourcePath(NULL)
	{
		if (!Load(path, renderSystem))
		{
			Release();
		}
	}

	Sprite::Sprite(const Sprite& s)
	{
		m_nFrames = s.m_nFrames;

		m_Textures = new Texture*[m_nFrames];
		memcpy(m_Textures, s.m_Textures, m_nFrames * sizeof(Texture*));

		m_animTime = s.m_animTime;
		m_maxWidth = s.m_maxWidth;
		m_maxHeight = s.m_maxHeight;
		m_cFrame = s.m_cFrame;
		m_animCount = s.m_animCount;
		
		m_ResourcePath = new char[strlen(s.m_ResourcePath) + 1];
		if (!m_ResourcePath)
		{
			Log("[Sprite] Error allocating memory for resource path (%s). Object may not be able to reload.", s.m_ResourcePath);
		}

		memset(m_ResourcePath, 0, sizeof(char) * (strlen(s.m_ResourcePath) + 1));
		memcpy(m_ResourcePath, s.m_ResourcePath, sizeof(char) * strlen(s.m_ResourcePath));
	}

	Sprite::~Sprite(void)
	{
		Release();
	}


	Sprite& Sprite::operator =(const Sprite& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		Release();

		m_nFrames = rhs.m_nFrames;

		m_Textures = new Texture*[m_nFrames];
		memcpy(m_Textures, rhs.m_Textures, m_nFrames * sizeof(Texture*));

		m_animTime = rhs.m_animTime;
		m_cFrame = rhs.m_cFrame;
		m_animCount = rhs.m_animCount;
		m_maxWidth = rhs.m_maxWidth;
		m_maxHeight = rhs.m_maxHeight;

		m_ResourcePath = new char[strlen(rhs.m_ResourcePath) + 1];
		if (!m_ResourcePath)
		{
			Log("[Sprite] Error allocating memory for resource path (%s). Object may not be able to reload.", rhs.m_ResourcePath);
		}

		memset(m_ResourcePath, 0, sizeof(char) * (strlen(rhs.m_ResourcePath) + 1));
		memcpy(m_ResourcePath, rhs.m_ResourcePath, sizeof(char) * strlen(rhs.m_ResourcePath));

		return *this;
	}

	bool Sprite::Load(const char* path, RenderSystem* renderSystem)
	{
		Release();	// Free any existing resources

		SpriteDef def(path);
		m_nFrames = def.GetNFrames();
		m_animTime = def.GetFrameTime();
		m_cFrame = 0;
		m_animCount = 0;
		m_maxWidth = 0;
		m_maxHeight = 0;

		m_Textures = new Texture*[m_nFrames];
		memset(m_Textures, 0, m_nFrames * sizeof(Texture*));

		for (int i = 0; i < m_nFrames; ++i)
		{
			unsigned int width;
			unsigned int height;

			m_Textures[i] = renderSystem->LoadTexture(def.GetFrame(i));

			width = m_Textures[i]->GetWidth();
			height = m_Textures[i]->GetHeight();

			m_maxWidth = (width > m_maxWidth) ? width : m_maxWidth;		// Set the objects width and height to the
			m_maxHeight = (height > m_maxHeight) ? height: m_maxHeight;	// width and height of the largest sprite
		}

		m_ResourcePath = (char*)malloc(sizeof(char) * (strlen(path) + 1));
		if (!m_ResourcePath)
		{
			Log("[Sprite] Error allocating memory for resource path (%s). Object may not be able to reload.",
				path);
		}

		memset(m_ResourcePath, 0, sizeof(char) * (strlen(path) + 1));
		memcpy(m_ResourcePath, path, sizeof(char) * strlen(path));

		return true;
	}

	void Sprite::Release(void)
	{
		if (m_Textures)
		{
			for (int i = 0; i < m_nFrames; ++i)
			{
				if (m_Textures[i])
				{
					m_Textures[i]->Release();
				}
			}
			
			delete [] m_Textures;
			m_Textures = NULL;
		}

		if (m_ResourcePath)
		{
			delete [] m_ResourcePath;
			m_ResourcePath = NULL;
		}
	}

	void Sprite::Draw(float x, float y, long deltaTime)
	{
		Draw(x, y, 0.0f, deltaTime);
	}

	void Sprite::Draw(float x, float y, float rotation, long deltaTime)
	{
		updateAnimation(deltaTime);
		m_Textures[m_cFrame]->Draw(x, y, rotation);
	}

	void Sprite::updateAnimation(long deltaTime)
	{
		m_animCount += deltaTime;

		if (m_animCount > m_animTime)
		{
			++m_cFrame;
			
			if (m_cFrame >= m_nFrames)
			{
				m_cFrame = 0;
			}

			m_animCount = 0;
		}
	}
}
