#ifndef __NAN0_SCREENELEMENT_H__
#define __NAN0_SCREENELEMENT_H__

namespace n0
{
	// SCREEN ELEMENT
	class ScreenElement : public recti
	{
	protected:
		vec2i m_screenBottomLeft;
		u8 m_anchor;
		Colour m_backgroundColour;
		bool m_isVisible;
		bool m_isEnabled;
		std::string m_name;
		ScreenElement * m_pParent;
		std::vector<ScreenElement*> m_children;

	public:
		ScreenElement();
		ScreenElement(const ScreenElement & other);
		virtual ~ScreenElement();

		virtual void Tick(const u64 delta);
		virtual void Draw();

		virtual std::string GetType() { return "ScreenElement"; }

		// screen elements
		bool AddChild(ScreenElement * child);
		ScreenElement * GetParent() const { return m_pParent; }
		ScreenElement * GetChildByName(const std::string & name);
		std::vector<ScreenElement*> * GetChildren() { return &m_children; }

		ScreenElement * RemoveChild(ScreenElement* child);
		bool RemoveFromParent();
		void RemoveAllChildren();

		// anchor
		u8 GetAnchor() const { return m_anchor; }
		void SetAnchor(const u8 anchor) { m_anchor = anchor; }
		bool IsAnchorSet(const u8 anchor) const { return (anchor & m_anchor) == anchor; }

		// visibility
		bool IsVisible() const { return m_isVisible; }
		void SetVisible(const bool visibility) { m_isVisible = visibility; }

		// enabled
		bool IsEnabled() const { return m_isEnabled; }
		void SetEnabled(bool isEnabled) { m_isEnabled = isEnabled; }

		// background colour
		Colour GetBackgroundColour() const { return m_backgroundColour; }
		void SetBackgroundColour(const Colour & colour) { m_backgroundColour = colour; }

		vec2i GetScreenBottomLeft() const { return m_screenBottomLeft; }

		bool Contains(const s32 x, const s32 y) const;
		bool Contains(const vec2i & coord) const;

		std::string GetName() { return m_name; }
		void SetName(std::string name) { m_name = name; }

	protected:
		vec2i LocalToGlobal(const vec2i & coord) const;
		vec2i GetAnchoredPosition(const recti & child, const u8 anchor) const;
	}; // class ScreenElement
} // namespace n0

#endif // __NAN0_SCREENELEMENT_H__