#ifndef circle_hpp
#define circle_hpp

#include "shape.hpp"

namespace smorodnikov
{
  class Circle: public Shape
  {
  public:
    Circle (const point_t &pos, const double radius);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    point_t getCenter() const noexcept override;
    std::string getType() const noexcept override;

    void move(const double toX, const double toY) noexcept override;
    void move(const point_t &toPos) noexcept override;
    void scale(const double coef) override;
    void rotate(double angle) noexcept override;
    void show() const override;
    
  private:
    point_t pos_;
    double radius_;
  };
}

#endif
