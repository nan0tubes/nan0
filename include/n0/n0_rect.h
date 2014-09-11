//
//  n0_rect.h
//  n0
//
//  Created by Norman van der Ploeg on 2014-09-10.
//  Copyright (c) 2014 Norman van der Ploeg. All rights reserved.
//

#ifndef n0_n0_rect_h
#define n0_n0_rect_h


#endif


namespace n0
{
    
    // RECT
    template<class T>
    class rect
    {
    protected:
        vec2<T> m_position;
        vec2<T> m_dimensions;
        
    public:
        rect<T>() { }
        rect<T>(const vec2<T> position, const vec2<T> dimensions) : m_position(position), m_dimensions(dimensions) { }
        rect<T>(const rect<T> & other) : m_position(other.m_position), m_dimensions(other.m_dimensions) { }
        
        rect<T> & operator=(const rect<T> & rhs) { m_position = rhs.m_position; m_dimensions= rhs.m_dimensions; return *this; }
        
        // position
        T * GetX() { return &m_position.x; }
        T * GetY() { return &m_position.y; }
        vec2<T> GetPosition() const { return m_position; }
        virtual void SetPosition(const vec2<T> & position) { m_position = position; }
        virtual void SetPosition(const T x, const T y) { m_position.x = x; m_position.y = y; }
        
        // size
        T * GetW() { return &m_dimensions.x; }
        T * GetH() { return &m_dimensions.y; }
        T GetWidth() const { return m_dimensions.x; }
        void SetWidth(const T & width) { m_dimensions.x = width; }
        T GetHeight() const { return m_dimensions.y; }
        void SetHeight(const T & height) { m_dimensions.y = height; }
        vec2<T> GetSize() const { return m_dimensions; }
        void SetSize(const vec2<T> & dimensions) { m_dimensions = dimensions; }
        void SetSize(const T x, const T y) { m_dimensions.x = x; m_dimensions.y = y; }
        
        // utility
        vec2<T> GetCenter() const { return m_dimensions / 2; }
        T GetArea() const { return m_dimensions.x * m_dimensions.y; }
        T GetPerimeter() const { return (m_dimensions.x << 1) + (m_dimensions.y << 1); }
        
        bool Contains(const vec2<T> & pt) const { return Contains(pt.x, pt.y); }
        bool Contains(const T x, const T y) const { return !(x < m_position.x || x > m_position.x + m_dimensions.x || y < m_position.y() || y > m_position.y + m_dimensions.y); }
    };
    
    template<class T>
    static bool operator==(const rect<T> & lhs, const rect<T> & rhs) { return lhs.m_position == rhs.m_position && lhs.m_dimensions == rhs.m_dimensions; }
    template<class T>
    static bool operator!=(const rect<T> & lhs, const rect<T> & rhs) { return !operator==(lhs, rhs); }
    
    typedef rect<s32> recti;
    typedef rect<u32> rectu;
    typedef rect<f32> rectf;
}