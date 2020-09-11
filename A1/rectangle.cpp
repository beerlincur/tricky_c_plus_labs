#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const point_t &pos, const double height, const double width) :
  Shape(pos),
  height_(height),
  width_(width)
{
  assert(height_ > 0 && width_ > 0);
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, height_, width_};
}

void Rectangle::getInfo(std::ostream &out) const
{
  out << "Rectangle center = ";
  Shape::getInfo(out);
  out << " height = " << height_ << " width = " << width_;
}

std::ostream& operator<<(std::ostream& out, const Rectangle &rectangle)
{
  rectangle.getInfo(out);
  return out;
}


