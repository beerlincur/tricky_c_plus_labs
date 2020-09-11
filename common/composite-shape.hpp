#ifndef composite_shape_hpp
#define composite_shape_hpp

#include <memory>
#include "shape.hpp"

namespace smorodnikov
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &shape);
    CompositeShape(CompositeShape &&shape) = default;
    ~CompositeShape() = default;

    const std::shared_ptr<Shape>& operator[](const size_t index) const;
  
    CompositeShape& operator=(const CompositeShape &shape);
    CompositeShape& operator=(CompositeShape &&shape) noexcept = default;

    void addShape(const std::shared_ptr<Shape>& newShape);
    void removeShape(const size_t index);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    point_t getCenter() const noexcept override;
    size_t getSize() const noexcept;
    std::string getType() const noexcept override;
    
    void move(const double toX, const double toY) noexcept override;
    void move(const point_t &toPos) noexcept override;
    void scale(const double coef) override;
    void rotate(double angle) noexcept override;
    void show() const override;
  
  protected:
    double getLeftX() const noexcept;
    double getRightX() const noexcept;
    double getDownY() const noexcept;
    double getUpY() const noexcept;
    
  private:
    point_t pos_;
    std::unique_ptr<std::shared_ptr<Shape>[]> array_;
    size_t size_;
    size_t sizeAllocated_;
  };
}

#endif

