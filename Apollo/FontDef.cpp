#include "FontDef.h"

namespace Apollo
{
	FontDef::FontDef(const char* path)
	{
		this->loadFromFile(path);
	}

	FontDef::~FontDef(void)
	{
	}

	const CharacterDef FontDef::operator[] (int index) const
	{
		return this->characters[index];
	}

	const char* FontDef::GetResourcePath(void) const
	{
		return this->resourcePath.c_str();
	}

	bool FontDef::loadFromFile(const char* path)
	{
		TiXmlDocument doc(path);
		if (!doc.LoadFile(TIXML_ENCODING_UTF8))
			return false;

		TiXmlHandle hDoc(&doc);
		TiXmlElement* elem;
		TiXmlHandle hRoot(0);

		// root
		elem = hDoc.FirstChildElement().Element(); // /Font
		hRoot = TiXmlHandle(elem);
		
		this->resourcePath = elem->Attribute("file");

		for (elem = hRoot.FirstChild("Character").Element(); elem; elem = elem->NextSiblingElement())
		{
			char value;
			int x;
			int y;
			int width;
			int height;
			int xOffset;
			int yOffset;
			int xAdvance;

			value = (char)atoi(elem->GetText());
			elem->QueryIntAttribute("x", &x);
			elem->QueryIntAttribute("y", &y);
			elem->QueryIntAttribute("width", &width);
			elem->QueryIntAttribute("height", &height);
			elem->QueryIntAttribute("x-offset", &xOffset);
			elem->QueryIntAttribute("y-offset", &yOffset);
			elem->QueryIntAttribute("x-advance", &xAdvance);

			this->characters[value] = CharacterDef(
				value,
				x,
				y,
				width,
				height,
				xOffset,
				yOffset,
				xAdvance);
		}

		return true;
	}
}
