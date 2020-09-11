#include "shape.hpp"
#include <iostream>

Shape::Shape(const point_t &pos) :
  pos_(pos)
{}

void Shape::move(const point_t &toPos)
{
  pos_ = toPos;
}

void Shape::move(const double toX, const double toY)
{
  move({toX + pos_.x, toY + pos_.y});
}

void Shape::getInfo(std::ostream& out) const
{
  out << "(" << pos_.x << ", " << pos_.y << ")";
}

std::ostream& operator<<(std::ostream& out, const Shape &shape)
{
  shape.getInfo(out);
  return out;
}
