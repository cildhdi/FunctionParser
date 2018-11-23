#include <Segment.h>

namespace cl
{

SegmentPoint::SegmentPoint(double value, bool contain)
    : _value(value), _contain(contain)
{
}

double SegmentPoint::value() const
{
    return _value;
}

void SegmentPoint::set_value(double v)
{
    _value = v;
}

bool SegmentPoint::contain() const
{
    return _contain;
}

void SegmentPoint::set_contain(bool c)
{
    _contain = c;
}

bool SegmentPoint::operator<(const SegmentPoint &rhs) const
{
    return _value < rhs._value;
}

bool SegmentPoint::operator>(const SegmentPoint &rhs) const
{
    return _value > rhs._value;
}

//segment
	Segment::Segment()
	{
	}

	Segment::Segment(const SegmentPoint &lp, const SegmentPoint &rp)
	{
		set_point(lp, rp);
	}

	void Segment::set_point(const SegmentPoint &lp, const SegmentPoint &rp)
	{
		if (lp < rp)
		{
			_left = lp;
			_right = rp;
		}
		else
		{
			_left = rp;
			_right = lp;
		}
	}

	void Segment::set_left_point(const SegmentPoint &lp)
	{
		set_point(lp, _right);
	}

	void Segment::set_right_point(const SegmentPoint &rp)
	{
		set_point(_left, rp);
	}

	bool Segment::contain(double value) const
	{
		if (_left.value() < value && _right.value() > value)
			return true;
		if (_left.contain() && value == _left.value())
			return true;
		if (_right.contain() && value == _right.value())
			return true;
		return false;
	}

	std::string Segment::str() const
	{
		std::string res;
		res += (_left.contain() ? '[' : '(');
		res += std::to_string(_left.value());
		res += ',';
		res += std::to_string(_right.value());
		res += (_right.contain() ? ']' : ')');
		return res;
	}

	bool Segment::operator<(const Segment &rhs) const
	{
		return _left < rhs._left;
	}

	bool Segment::operator>(const Segment &rhs) const
	{
		return _left > rhs._left;
	}


} // namespace cl