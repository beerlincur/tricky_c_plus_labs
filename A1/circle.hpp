#ifndef circle_hpp
#define circle_hpp

#include "shape.hpp"

class Circle: public Shape
{
public:
  
  Circle(const point_t &pos, const double radius);
  friend std::ostream& operator<<(std::ostream& out, const Circle &circle);
  
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  
private:
  
  double radius_;
  void getInfo(std::ostream& out) const override;
  
};

std::ostream& operator<<(std::ostream& out, const Circle &circle);

#endif /* circle_hpp */
