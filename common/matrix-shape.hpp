#ifndef matrix_shape_hpp
#define matrix_shape_hpp

#include <memory>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace smorodnikov
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix);
    Matrix(const CompositeShape &cs);
    ~Matrix() = default;

    Matrix& operator=(const Matrix &matrix);
    Matrix& operator=(Matrix &&matrix) noexcept = default;

    void addShape(const std::shared_ptr<Shape> &shape);

    size_t getRowSize() const noexcept;
    size_t getColumns() const noexcept;
    const std::shared_ptr<Shape>& getElement(const size_t row, const size_t column) const;

    void show() const;

  protected:
    bool isIntersect(const std::shared_ptr<Shape> &first, 
        const std::shared_ptr<Shape> &second) const noexcept;
        
  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> matrix_;
    size_t rows_;
    size_t columns_;
    size_t rowsAllocated_;
    size_t columnsAllocated_;

    void copyToMatrixWithOffset(std::unique_ptr<std::shared_ptr<Shape>[]> &matrixToCopyIn, 
        const size_t columnsWithOffset) const noexcept;
  };
}

#endif
