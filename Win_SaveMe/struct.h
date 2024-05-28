#pragma once

struct Vec2
{
	float x;
	float y;

public:
	Vec2& operator = (POINT _pt)
	{
		// x = (float)_pt.x;
		// y = (float)_pt.y;

		Vec2 myVec2;
		myVec2.x = (float)_pt.x;
		myVec2.y = (float)_pt.y;
		return myVec2;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator / (float _iOther)
	{
		assert(!(0.f == _iOther));
		return Vec2(x / _iOther, y / _iOther);
	}
	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}


public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
};