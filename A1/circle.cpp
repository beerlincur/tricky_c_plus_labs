#include "circle.hpp"
#include <cmath>
#include <cassert>

Circle::Circle(const point_t &pos, const double radius) :
  Shape(pos),
  radius_(radius)
{
  assert(radius_ > 0);
}

double Circle::getArea() const
{
  return M_PI * this->radius_ * this->radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::getInfo(std::ostream& out) const
{
  out << "Circle center = ";
  Shape::getInfo(out);
  out << " radius = " << radius_;
}

std::ostream& operator<<(std::ostream& out, const Circle &circle)
{
  circle.getInfo(out);
  return out;
}


