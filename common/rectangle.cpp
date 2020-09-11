#include "rectangle.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace smorodnikov;

Rectangle::Rectangle(const rectangle_t &rectangle):
    vertices_{ { rectangle.pos.x - rectangle.width / 2, rectangle.pos.y - rectangle.height / 2 },
        { rectangle.pos.x - rectangle.width / 2, rectangle.pos.y + rectangle.height / 2 }, 
        { rectangle.pos.x + rectangle.width / 2, rectangle.pos.y + rectangle.height / 2 },
        { rectangle.pos.x + rectangle.width / 2, rectangle.pos.y - rectangle.height / 2 } }
{
  if (rectangle.width <= 0 || rectangle.height <= 0)
  {
    throw std::invalid_argument("Error: Invalid rectangle parameters!\n");
  }
}

double Rectangle::getArea() const noexcept
{
  return (getSide(0, 2) * getSide(1, 0));
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  double minLeftX = std::min({ vertices_[0].x, vertices_[1].x,
      vertices_[2].x, vertices_[3].x });

  double maxRightX = std::max({ vertices_[0].x, vertices_[1].x,
      vertices_[2].x, vertices_[3].x });

  double minDownY = std::min({ vertices_[0].y, vertices_[1].y,
      vertices_[2].y, vertices_[3].y });

  double maxUpY = std::max({ vertices_[0].y, vertices_[1].y,
      vertices_[2].y, vertices_[3].y });

  return { { (minLeftX + maxRightX) / 2, (minDownY + maxUpY) / 2 },
      fabs(maxRightX - minLeftX), fabs(maxUpY - minDownY) };
}

point_t Rectangle::getCenter() const noexcept
{
  return {(vertices_[0].x + vertices_[2].x) / 2, (vertices_[0].y + vertices_[2].y) / 2};
}

double Rectangle::getSide(const size_t first, const size_t second) const noexcept
{
  return sqrt(pow((vertices_[second].x - vertices_[first].x), 2) 
             + pow((vertices_[second].y - vertices_[first].y), 2));
}

std::string Rectangle::getType() const noexcept
{
  return "Rectangle";
}

size_t Rectangle::getAmountOfVertices() const noexcept
{
  return sizeof(vertices_) / sizeof(*vertices_);
}

void Rectangle::move(const double toX, const double toY) noexcept
{
  const point_t center = getCenter();
  move(point_t{ center.x + toX, center.y + toY });
}

void Rectangle::move(const point_t &toPos) noexcept
{
  const point_t center = getCenter();
  const size_t amountOfVertices = getAmountOfVertices();
  for (size_t i = 0; i < amountOfVertices; i++)
  {
    vertices_[i].x += toPos.x - center.x;
    vertices_[i].y += toPos.y - center.y;
  }
}

void Rectangle::scale(const double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Error: Invalid scale coefficient value!\n");
  }
  const point_t center = getCenter();
  const size_t amountOfVertices = getAmountOfVertices();
  for (size_t i = 0; i < amountOfVertices; i++)
  {
    vertices_[i] = { (vertices_[i].x - center.x) * coef + center.x,
        (vertices_[i].y - center.y) * coef + center.y };
  }
}

void Rectangle::rotate(double angle) noexcept
{
  angle = (angle * M_PI) / 180;
  double sinAngle = sin(angle);
  double cosAngle = cos(angle);

  const size_t amountOfVertices = getAmountOfVertices();
  for (size_t i = 0; i < amountOfVertices; i++)
  {
    vertices_[i] = { cosAngle * vertices_[i].x - sinAngle * vertices_[i].y,
        sinAngle * vertices_[i].x + cosAngle * vertices_[i].y };
  }
}

void Rectangle::show() const
{
  std::cout << "\nRectangle:\nCoordinates of vertices_: ";

  const size_t amountOfVertices = getAmountOfVertices();
  for (size_t i = 0; i < amountOfVertices; i++)
  {
    std::cout << "(" << vertices_[i].x << ";" << vertices_[i].y << ") ";
  } 

  std::cout << "\nArea of rectangle: " << getArea();
  std::cout << "\nWidth of frame rectangle: " << getFrameRect().width;
  std::cout << "\nHeight of frame rectangle: " << getFrameRect().height;
  std::cout << "\nCenter point of frame rectangle: (" << getFrameRect().pos.x 
      << ";" << getFrameRect().pos.y << ")\n";
}

