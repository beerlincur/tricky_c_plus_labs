#ifndef rectangle_hpp
#define rectangle_hpp

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  
  Rectangle(const point_t &pos, const double height, const double width);
  friend std::ostream& operator<<(std::ostream& out, const Rectangle &rectangle);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  

private:
  
  double height_;
  double width_;
  void getInfo(std::ostream& out) const override;
};

std::ostream& operator<<(std::ostream& out, const Rectangle &rectangle);

#endif /* rectangle_hpp */
