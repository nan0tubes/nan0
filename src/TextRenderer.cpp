#include "fwInternal.h"

TextRenderer::TextRenderer(irr::IrrlichtDevice * pDevice)
{
	m_pDevice = pDevice;
	irr::gui::IGUIFont * font = m_pDevice->getGUIEnvironment()->getBuiltInFont();
	m_Batches[kFont_Default] = std::pair<irr::gui::IGUIFont*, std::queue<SText> >(font, std::queue<SText>());
	m_HasBegin = false;
}

TextRenderer::~TextRenderer( )
{
	CleanUp();
}

void TextRenderer::Begin( )
{
	ASSERT(!m_HasBegin);

	m_HasBegin = true;
}

void TextRenderer::End( )
{
	ASSERT(m_HasBegin);

	FlushAll();
	m_HasBegin = false;
}

u32 TextRenderer::AddFont(const char * filename)
{
	const u32 key = Hash(filename);
	//TODO: verify file exists and such
	irr::gui::IGUIFont * font = m_pDevice->getGUIEnvironment()->getFont(filename);
	m_Batches[key] = std::pair<irr::gui::IGUIFont*, std::queue<SText> >(font, std::queue<SText>());
	return key;
}

void TextRenderer::AddText(const u32 font, const wchar_t * text, const irr::core::vector2di & pos, const irr::video::SColor colour)
{
	FW_ASSERT(m_HasBegin, "TextRenderer::AddText, have you started the batch?");

	std::map<u32, std::pair< irr::gui::IGUIFont*, std::queue<SText> > >::iterator iter = m_Batches.find(font);
	if (iter != m_Batches.end())
	{
		const irr::core::dimension2du size = (*iter).second.first->getDimension(text);
		irr::core::recti posRect(pos.X, pos.Y-size.Height, pos.X+size.Width, pos.Y);
		(*iter).second.second.push(SText(text, posRect, colour, false, false, NULL));
	}
}

void TextRenderer::AddCenteredText(const u32 font, const wchar_t * text, const irr::core::vector2di & center, const irr::video::SColor colour)
{
	FW_ASSERT(m_HasBegin, "TextRenderer::AddCenteredText, have you started the batch?");

	std::map<u32, std::pair< irr::gui::IGUIFont*, std::queue<SText> > >::iterator iter = m_Batches.find(font);
	if (iter != m_Batches.end())
	{
		const irr::core::dimension2du size((*iter).second.first->getDimension(text));
		const irr::core::position2di pos(center.X - (size.Width / 2), center.Y - (size.Height / 2));
		(*iter).second.second.push(SText(text, irr::core::recti(pos, size), colour, true, false, NULL));
	}
}

irr::core::dimension2du TextRenderer::GetTextDimension(const u32 font, const wchar_t * text)
{
	irr::core::dimension2du dims;

	std::map<u32, std::pair< irr::gui::IGUIFont*, std::queue<SText> > >::iterator iter = m_Batches.find(font);
	if (iter != m_Batches.end())
	{
		dims = ((*iter).second.first->getDimension(text));
	}

	return dims;
}

void TextRenderer::Flush(const u32 font)
{
	std::map<u32, std::pair< irr::gui::IGUIFont*, std::queue<SText> > >::iterator iter = m_Batches.find(font);
	if (iter != m_Batches.end())
	{
		while ((*iter).second.second.size())
		{
			const SText * textObj = &(*iter).second.second.front();
			if (m_HasBegin)
			{
				irr::gui::IGUISkin* pSkin = m_pDevice->getGUIEnvironment()->getSkin();
				irr::gui::IGUIFont* pFont = pSkin->getFont();
				if (pSkin->getFont() != (*iter).second.first)
					pSkin->setFont((*iter).second.first);

				(*iter).second.first->draw(textObj->textString, textObj->posRect, textObj->colour, textObj->hCenter, textObj->vCenter, NULL);
			}
			(*iter).second.second.pop();
		}
	}
}

void TextRenderer::FlushAll( )
{
	std::map<u32, std::pair< irr::gui::IGUIFont*, std::queue<SText> > >::iterator iter = m_Batches.begin();
	while (iter != m_Batches.end())
	{
		Flush((*iter).first);
		++iter;
	}
}

void TextRenderer::CleanUp( )
{
	ASSERT(!m_HasBegin);

	if (m_Batches.size())
	{
		FlushAll();
		m_Batches.clear();
	}
}
