#include "n0/n0.h"


namespace n0
{
	ScreenElement::ScreenElement()
		: m_anchor(Anchor::BOTTOMLEFT)
		, m_backgroundColour(0xffffffff, Colour::ColourFormat_RGBA)
		, m_isVisible(true)
		, m_pParent(NULL)
	{

	}

	ScreenElement::ScreenElement(const ScreenElement & other)
		: m_anchor(other.m_anchor)
		, m_backgroundColour(other.m_backgroundColour)
		, m_isVisible(other.m_isVisible)
		, m_name(other.m_name)
		, m_pParent(other.m_pParent)
	{
		m_children.insert(m_children.end(),other.m_children.begin(),other.m_children.end());
	}
	
	ScreenElement::~ScreenElement()
	{
		if (m_pParent)
			RemoveFromParent();
		RemoveAllChildren();
	}
	
	void ScreenElement::Tick(const u64 delta)
	{
		if (!m_isEnabled)
			return;

		// tick children
		for (std::vector<ScreenElement*>::const_iterator it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (*it)
			{
				(*it)->Tick(delta);
			}
		}
	}

	void ScreenElement::Draw()
	{
		if (m_isVisible == false)
			return;

		m_screenBottomLeft = LocalToGlobal(m_position);

		DrawRect(m_screenBottomLeft.x, m_screenBottomLeft.y, m_dimensions.x, m_dimensions.y, m_backgroundColour);
#ifdef _DEBUG
		Colour c(~m_backgroundColour.GetAsInt(Colour::ColourFormat_RGBA), Colour::ColourFormat_RGBA);
		DrawLine(m_screenBottomLeft.x, m_screenBottomLeft.y, m_screenBottomLeft.x + m_dimensions.x, m_screenBottomLeft.y, c); // top
		DrawLine(m_screenBottomLeft.x, m_screenBottomLeft.y, m_screenBottomLeft.x + m_dimensions.x, m_screenBottomLeft.y + m_dimensions.y, c); // diagonally down
		DrawLine(m_screenBottomLeft.x, m_screenBottomLeft.y, m_screenBottomLeft.x, m_screenBottomLeft.y + m_dimensions.y, c); // left
		DrawLine(m_screenBottomLeft.x, m_screenBottomLeft.y + m_dimensions.y, m_screenBottomLeft.x + m_dimensions.x, m_screenBottomLeft.y, c); // diagonally up
		DrawLine(m_screenBottomLeft.x + m_dimensions.x, m_screenBottomLeft.y, m_screenBottomLeft.x + m_dimensions.x, m_screenBottomLeft.y + m_dimensions.y, c); // right
		DrawLine(m_screenBottomLeft.x, m_screenBottomLeft.y + m_dimensions.y, m_screenBottomLeft.x + m_dimensions.x, m_screenBottomLeft.y + m_dimensions.y, c); // bottom
#endif

		// draw children
		for (std::vector<ScreenElement*>::const_iterator it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (*it)
				(*it)->Draw();
		}
	}

	bool ScreenElement::AddChild(ScreenElement * child)
	{
		if (child == NULL)
			return false;

		m_children.push_back(child);
		child->m_pParent = this;
		
		return true;
	}

	ScreenElement * ScreenElement::GetChildByName(const std::string & name)
	{
		if (m_name.compare(name) == 0)
		{
			return this;
		}

		for (std::vector<ScreenElement*>::const_iterator it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (*it)
			{
				ScreenElement * child = (*it)->GetChildByName(name);
				if (child)
				{
					return child;
				}
			}
		}

		return NULL;
	}

	ScreenElement * ScreenElement::RemoveChild(ScreenElement* child)
	{
		for (std::vector<ScreenElement*>::const_iterator it = m_children.begin(); it != m_children.end(); ++it)
		{
			if ((*it) == child)
			{
				(*it)->m_pParent = NULL;
				ScreenElement * retval = (*it);
				m_children.erase(it);
				return retval;
			}
		}
		return NULL;
	}

	bool ScreenElement::RemoveFromParent()
	{
		if (m_pParent)
		{
			ScreenElement * child = m_pParent->RemoveChild(this);
			m_pParent = NULL;
			return child != NULL;
		}
		return true;
	}

	void ScreenElement::RemoveAllChildren()
	{
		for (std::vector<ScreenElement*>::const_iterator it = m_children.begin(); it != m_children.end();)
		{
			delete (*it);
			it = m_children.begin();
		}
		m_children.clear();
	}

	vec2i ScreenElement::LocalToGlobal(const vec2i & coord) const
	{
		if (m_pParent == NULL)
		{
			recti rect;
			return -GetAnchoredPosition(rect, m_anchor) + m_position;
		}

		return (m_pParent->GetScreenBottomLeft() + m_pParent->GetAnchoredPosition(*this, m_anchor) + m_position);
	}


	vec2i ScreenElement::GetAnchoredPosition(const recti & child, const u8 anchor) const
	{
		vec2i retval;

		// NOTE: Anchor::LEFT and Anchor::BOTTOM are default, so nothing to do here with them.
		if (anchor & Anchor::HCENTER)
		{
			retval.x = (m_dimensions.x / 2 ) - (child.GetWidth() / 2);
		}
		if (anchor & Anchor::RIGHT)
		{
			retval.x = m_dimensions.x - child.GetWidth();
		}
		if (anchor & Anchor::TOP)
		{
			retval.y = m_dimensions.y - child.GetHeight();
		}
		if (anchor & Anchor::VCENTER)
		{
			retval.y = (m_dimensions.y / 2) - (child.GetHeight() / 2);
		}

		return retval;
	}

	bool ScreenElement::Contains(const vec2i & coord) const
	{
		return Contains(coord.x, coord.y);
	}

	bool ScreenElement::Contains(const s32 x, const s32 y) const
	{
		//TODO: go through parent chain ensuring all parents are visible
		return false;
	}
}
