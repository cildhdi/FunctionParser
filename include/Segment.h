#pragma once

#include <string>

namespace cl
{

class SegmentPoint
{
  private:
    double _value;
    bool _contain;

  public:
    SegmentPoint(double value = 0, bool contain = false);
    double value() const;
    void set_value(double v);
    bool contain() const;
    void set_contain(bool c);
    bool operator<(const SegmentPoint &rhs) const;
    bool operator>(const SegmentPoint &rhs) const;
};

class Segment
{
  private:
    SegmentPoint _left;
    SegmentPoint _right;

  public:
    Segment();
    Segment(const SegmentPoint &lp, const SegmentPoint &rp);
    void set_point(const SegmentPoint &lp, const SegmentPoint &rp);
    void set_left_point(const SegmentPoint &lp);
    void set_right_point(const SegmentPoint &rp);
    bool contain(double value) const;
    std::string str() const;
    bool operator<(const Segment &rhs) const;
    bool operator>(const Segment &rhs) const;
};

} // namespace cl
