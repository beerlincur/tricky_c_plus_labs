#ifndef rectangle_hpp
#define rectangle_hpp

#include "shape.hpp"

namespace smorodnikov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle (const rectangle_t& rectangle);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    point_t getCenter() const noexcept override;
    double getSide(const size_t first, const size_t second) const noexcept;
    std::string getType() const noexcept override;
    size_t getAmountOfVertices() const noexcept;

    void move(const double toX, const double toY) noexcept override;
    void move(const point_t &toPos) noexcept override;
    void scale(const double coef) override;
    void rotate(double angle) noexcept override;
    void show() const override;

  private:
    point_t vertices_[4];
  };
}

#endif
