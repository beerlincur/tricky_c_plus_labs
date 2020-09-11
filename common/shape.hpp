#ifndef shape_hpp
#define shape_hpp

#include <iostream>
#include <string>
#include "base-types.hpp"

namespace smorodnikov
{
  class Shape
  {
  public:
    
    virtual ~Shape() = default;
    
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual point_t getCenter() const noexcept = 0;
    virtual std::string getType() const noexcept = 0;

    virtual void move(const double toX, const double toY) noexcept = 0;
    virtual void move(const point_t &toPos) noexcept = 0;
    virtual void scale(const double coef) = 0;
    virtual void rotate(const double angle) noexcept = 0;
    virtual void show() const = 0;
  };
}

#endif
