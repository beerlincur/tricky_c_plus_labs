#include "composite-shape.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace smorodnikov;

CompositeShape::CompositeShape():
    pos_({0,0}),
    array_(nullptr),
    size_(0),
    sizeAllocated_(0)
{}

CompositeShape::CompositeShape(const CompositeShape &shape):
    pos_(shape.pos_),
    array_(std::make_unique<std::shared_ptr<Shape>[]>(shape.sizeAllocated_)),
    size_(shape.size_),
    sizeAllocated_(shape.sizeAllocated_)
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = shape.array_[i];
  }
}

const std::shared_ptr<Shape>& CompositeShape::operator[](const size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Error: Index out of range!\n");
  }
  return array_[index];
}

CompositeShape& CompositeShape::operator=(const CompositeShape &shape)
{
  if (&shape == this)
  {
    return *this;
  }

  array_ = std::make_unique<std::shared_ptr<Shape>[]>(shape.sizeAllocated_);
  for (size_t i = 0; i < shape.size_; i++)
  {
    array_[i] = shape.array_[i];
  }

  pos_ = shape.pos_;
  size_ = shape.size_;
  sizeAllocated_ = shape.sizeAllocated_;
  
  return *this;
}

void CompositeShape::addShape(const std::shared_ptr<Shape>& newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Error: Invalid composit-shape parametr!\n");
  }

  if (size_ == sizeAllocated_)
  {
    const size_t sizeToAllocate = 15;
    std::unique_ptr<std::shared_ptr<Shape>[]> newArray =
        std::make_unique<std::shared_ptr<Shape>[]>(sizeAllocated_ + sizeToAllocate);

    sizeAllocated_ += sizeToAllocate;

    for (size_t i = 0; i < size_; i++)
    {
      newArray[i] = array_[i];
    }
    array_.swap(newArray);
  }
  array_[size_] = newShape;
  size_++;

  pos_ = point_t{(getRightX() + getLeftX()) / 2, (getUpY() + getDownY()) / 2};
}

void CompositeShape::removeShape(const size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Error: Invalid index!\n");
  }
  
  for (size_t i = index + 1; i < size_; i++)
  {
    array_[i - 1] = array_[i];
  }

  size_--;
  array_[size_].reset();
  pos_ = point_t{(getRightX() + getLeftX()) / 2, (getUpY() + getDownY()) / 2};
  
}

double CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (size_t i = 0; i < size_; i++)
  {
    area += array_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    throw std::logic_error("Error: CompositeShape is empty!\n");
  }

  rectangle_t currentFrameRect = array_[0]->getFrameRect();
  double minX = currentFrameRect.pos.x - currentFrameRect.width / 2;
  double maxX = currentFrameRect.pos.x + currentFrameRect.width / 2;
  double minY = currentFrameRect.pos.y - currentFrameRect.height / 2;
  double maxY = currentFrameRect.pos.y + currentFrameRect.height / 2;

  for (size_t i = 0; i < size_; i++)
  {
    currentFrameRect = array_[i]->getFrameRect();

    minX = std::min(minX, currentFrameRect.pos.x 
                   - (currentFrameRect.width / 2));
    minY = std::min(minY, currentFrameRect.pos.y 
                   - (currentFrameRect.height / 2));
    maxX = std::max(maxX, currentFrameRect.pos.x 
                   + (currentFrameRect.width / 2));
    maxY = std::max(maxY, currentFrameRect.pos.y 
                   + (currentFrameRect.height / 2));
    
  }
  return { { (minX + maxX) / 2, (minY + maxY) / 2 }, 
      fabs(maxX - minX), fabs(maxY - minY) };
}

point_t CompositeShape::getCenter() const noexcept
{
  return pos_;
}

size_t CompositeShape::getSize() const noexcept
{
  return size_;
}

std::string CompositeShape::getType() const noexcept
{
  return "Composite shape";
}

void CompositeShape::move(const double toX, const double toY) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(toX, toY);
  }
  pos_.x += toX;
  pos_.y += toY;
}

void CompositeShape::move(const point_t &toPos) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(toPos.x - pos_.x, toPos.y - pos_.y);
  }
  pos_ = toPos;
}

void CompositeShape::scale(const double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Error: Invalid scale coefficient!\n");
  }
  
  if (coef != 1)
  {
    for (size_t i = 0; i < size_; i++)
    {
      point_t frameRectPos = array_[i]->getFrameRect().pos;
      array_[i]->move(point_t{pos_.x + coef * (frameRectPos.x - pos_.x),
          pos_.y + coef * (frameRectPos.y - pos_.y)});

      array_[i]->scale(coef);
    }
  }
  pos_ = point_t{(getRightX() + getLeftX()) / 2, (getUpY() + getDownY()) / 2};
}

void CompositeShape::rotate(double angle) noexcept
{
  angle = (angle * M_PI) / 180;

  double sinAngle = sin(angle);
  double cosAngle = cos(angle);

  for (size_t i = 0; i < size_; i++)
  {
    point_t shapeCenter = array_[i]->getFrameRect().pos;
    array_[i]->move({(pos_.x - shapeCenter.x) * cosAngle - (pos_.y - shapeCenter.y) * sinAngle + pos_.x,
        (pos_.x - shapeCenter.x) * sinAngle + (pos_.y - shapeCenter.y) * cosAngle + pos_.y});
    array_[i]->rotate(angle);

  }
}

void CompositeShape::show() const 
{
  std::cout << "Composite shape contains:\n";

  for (size_t i = 0; i < size_; i++)
  {
    std::cout << array_[i]->getType() << "\n";
  }

  std::cout << "\nArea of composite shape: " << getArea();
  std::cout << "\nWidth of frame rectangle: " << getFrameRect().width;
  std::cout << "\nHeight of frame rectangle: " << getFrameRect().height;
  std::cout << "\nCenter point of frame rectangle: (" << getFrameRect().pos.x 
      << ";" << getFrameRect().pos.y << ")\n";
}

double CompositeShape::getLeftX() const noexcept
{
  double minLeftX = 0;

  if (size_ == 0)
  {
    return minLeftX;
  }

  minLeftX = array_[0]->getFrameRect().pos.x - array_[0]->getFrameRect().width / 2;
  double arrayLeftX = 0;

  for (size_t i = 1; i < size_; i++)
  {
    arrayLeftX = array_[i]->getFrameRect().pos.x - array_[i]->getFrameRect().width / 2;
    minLeftX = std::min(arrayLeftX, minLeftX);
  }
  return minLeftX;
}

double CompositeShape::getRightX() const noexcept
{
  double maxRightX = 0;

  if (size_ == 0)
  {
    return maxRightX;
  }

  maxRightX = array_[0]->getFrameRect().pos.x + array_[0]->getFrameRect().width / 2;
  double arrayRightX = 0;

  for (size_t i = 1; i < size_; i++)
  {
    arrayRightX = array_[i]->getFrameRect().pos.x + array_[i]->getFrameRect().width / 2;
    maxRightX = std::max(arrayRightX, maxRightX);
  }
  return maxRightX;
}

double CompositeShape::getDownY() const noexcept
{
  double minDownY = 0;

  if (size_ == 0)
  {
    return minDownY;
  }

  minDownY = array_[0]->getFrameRect().pos.y - array_[0]->getFrameRect().height / 2;
  double arrayDownY = 0;
  for (size_t i = 1; i < size_; i++)
  {
    arrayDownY = array_[0]->getFrameRect().pos.y - array_[0]->getFrameRect().height / 2;
    minDownY = std::min(arrayDownY, minDownY);
  }
  return minDownY;
}

double CompositeShape::getUpY() const noexcept
{
  double maxUpY = 0;

  if (size_ == 0)
  {
    return maxUpY;
  }

  maxUpY = array_[0]->getFrameRect().pos.y + array_[0]->getFrameRect().height / 2;
  double arrayUpY = 0;

  for (size_t i = 1; i < size_; i++)
  {
    arrayUpY = array_[0]->getFrameRect().pos.y + array_[0]->getFrameRect().height / 2;
    maxUpY = std::max(arrayUpY, maxUpY);
  }
  return maxUpY ;
}




