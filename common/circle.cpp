#include "circle.hpp"
#include <cassert>
#include <cmath>

using namespace smorodnikov;

Circle::Circle(const point_t &pos, const double radius):
    pos_(pos),
    radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Error: Invalid circle parameter!\n");
  }
}

double Circle::getArea() const noexcept
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {pos_, 2 * radius_, 2 * radius_};
}

point_t Circle::getCenter() const noexcept
{
  return pos_;
}

std::string Circle::getType() const noexcept
{
  return "Circle";
}

void Circle::move(const double toX, const double toY) noexcept
{
  pos_.x += toX;
  pos_.y += toY;
}

void Circle::move(const point_t &toPos) noexcept
{
  pos_ = toPos;
}

void Circle::scale(const double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Error: Invalid scale coefficient value!\n");
  }
  radius_ *= coef;
}

void Circle::rotate(double /*angle*/) noexcept
{
  
}

void Circle::show() const
{
  std::cout << "\nCircle:\nArea of circle: " << getArea();
  std::cout << "\nWidth of frame rectangle: " << getFrameRect().width;
  std::cout << "\nHeight of frame rectangle: " << getFrameRect().height;
  std::cout << "\nCenter point of frame rectangle: (" << getFrameRect().pos.x 
      << ";" << getFrameRect().pos.y << ")\n";
}


