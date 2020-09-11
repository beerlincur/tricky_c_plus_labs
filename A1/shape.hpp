#ifndef shape_hpp
#define shape_hpp

#include "base-types.hpp"
#include <iostream>

class Shape
{
public:
  
  Shape(const point_t &pos);
  virtual ~Shape() = default;
  
  friend std::ostream& operator<<(std::ostream& out, const Shape &shape);
  
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &toPos);
  virtual void move(const double toX, const double toY);
  
protected:
  
  point_t pos_;
  virtual void getInfo(std::ostream& out) const;
  
  
};

std::ostream& operator<<(std::ostream& out, const Shape &shape);

#endif /* shape_hpp */
