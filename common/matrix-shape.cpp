#include "matrix-shape.hpp"
#include <iostream>
#include <cmath>

using namespace smorodnikov;

Matrix::Matrix():
    matrix_(nullptr),
    rows_(0),
    columns_(0),
    rowsAllocated_(0),
    columnsAllocated_(0)
{}

Matrix::Matrix(const Matrix &matrix):
    matrix_(std::make_unique<std::shared_ptr<Shape>[]>(matrix.rowsAllocated_ * matrix.columnsAllocated_)),
    rows_(matrix.rows_),
    columns_(matrix.columns_),
    rowsAllocated_(matrix.rowsAllocated_),
    columnsAllocated_(matrix.columnsAllocated_)
{
  std::copy(matrix.matrix_.get(), matrix.matrix_.get() 
           + (matrix.rows_ * matrix.columnsAllocated_), matrix_.get());
}

Matrix::Matrix(Matrix &&matrix):
    matrix_(nullptr),
    rows_(matrix.rows_),
    columns_(matrix.columns_),
    rowsAllocated_(matrix.rowsAllocated_),
    columnsAllocated_(matrix.columnsAllocated_)
{
  *this = std::move(matrix);
}


Matrix::Matrix(const CompositeShape &cs):
    matrix_(nullptr),
    rows_(0),
    columns_(0),
    rowsAllocated_(0),
    columnsAllocated_(0)
{
  size_t csSize = cs.getSize();
  for (size_t i = 0; i < csSize; i++)
  {
    addShape(cs[i]);
  }
}

Matrix& Matrix::operator=(const Matrix &matrix)
{
  if (&matrix == this)
  {
    return *this;
  }

  matrix_ = std::make_unique<std::shared_ptr<Shape>[]>(matrix.rowsAllocated_ * matrix.columnsAllocated_);

  std::copy(matrix.matrix_.get(), matrix.matrix_.get() 
           + (matrix.rows_ * matrix.columnsAllocated_), matrix_.get());
  rows_ = matrix.rows_;
  columns_ = matrix.columns_;
  rowsAllocated_ = matrix.rowsAllocated_;
  columnsAllocated_ = matrix.columnsAllocated_;
  
  return *this;
}

void Matrix::addShape(const std::shared_ptr<Shape> &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Error: Invalid matrix parametr!\n");
  }

  const size_t rowsToAllocate = 5;
  const size_t columnsToAllocate = 15;
  
  if (rows_ == 0)
  {
    matrix_ = std::make_unique<std::shared_ptr<Shape>[]>((rowsAllocated_ 
        + rowsToAllocate) * (columnsAllocated_ + columnsToAllocate));
    rows_++;
    columns_++;
    rowsAllocated_ += rowsToAllocate;
    columnsAllocated_ += columnsToAllocate;
    matrix_[0] = shape;
  }
  else
  {
    bool isIntersectFlag = false;

    size_t i = 0;
    while (i < rows_)
    {
      size_t j = 0;
      while ((j < columnsAllocated_) && (!isIntersectFlag) && (matrix_[columnsAllocated_ * i + j] != nullptr))
      {
        if (isIntersect(matrix_[columnsAllocated_ * i + j], shape))
        {
          isIntersectFlag = true;
        }
        j++;
      }

      if (isIntersectFlag)
      {
        isIntersectFlag = false;
      }
      else
      {
        if (j == columns_)
        {
          if ((columns_ + 1) == columnsAllocated_)
          {
            std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix
                = std::make_unique<std::shared_ptr<Shape>[]>(rowsAllocated_ * (columnsAllocated_ + columnsToAllocate));
            copyToMatrixWithOffset(newMatrix, columnsAllocated_ + columnsToAllocate);
            matrix_.swap(newMatrix);
            columnsAllocated_ += columnsToAllocate;
          }
          columns_++;
        }

        matrix_[columnsAllocated_ * i + j] = shape;
        break;
      }
      i++;
    }

    if (i == rows_)
    {
      if ((rows_ + 1) == rowsAllocated_)
      {
        std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix
            = std::make_unique<std::shared_ptr<Shape>[]>((rowsAllocated_ + rowsToAllocate) * (columnsAllocated_));
        std::copy(matrix_.get(), matrix_.get() + (rows_ * columnsAllocated_), newMatrix.get());
        matrix_.swap(newMatrix);
        rowsAllocated_ += rowsToAllocate;
      }
      matrix_[rows_ * columnsAllocated_] = shape;
      rows_++;
    }
  }
}

size_t Matrix::getRowSize() const noexcept
{
  return rows_;
}

size_t Matrix::getColumns() const noexcept
{
  return columns_;
}

const std::shared_ptr<Shape>& Matrix::getElement(const size_t row, const size_t column) const
{
  if ((row > rows_) || (column > columns_))
  {
    throw std::out_of_range("Error: Index out of range!\n");
  }

  return matrix_[row * columnsAllocated_ + column];
}

void Matrix::show() const
{
  std::cout << "Matrix:\n";

  if (getRowSize() == 0)
  {
    std::cout << "Matrix is empty\n";
  }
  else
  {
    for (size_t i = 0; (i < rows_) && (matrix_[i * columnsAllocated_] != nullptr); i++)
    {
      for (size_t j = 0; (j < columnsAllocated_) && (matrix_[i * columnsAllocated_ + j] != nullptr); j++)
      {
        std::cout << "Row: " << i << " Column: " << j << ' ';
        matrix_[i * columnsAllocated_ + j]->show();
        std::cout << '\n';
      }
    }
  }
}

bool Matrix::isIntersect(const std::shared_ptr<Shape> &first,
    const std::shared_ptr<Shape> &second) const noexcept
{
  return ((abs(first->getFrameRect().pos.x - second->getFrameRect().pos.x)
      < ((first->getFrameRect().height / 2) + (second->getFrameRect().height / 2)))
      && ((abs(first->getFrameRect().pos.y - second->getFrameRect().pos.y)
      < ((first->getFrameRect().width / 2) + (second->getFrameRect().width / 2)))));
}

void Matrix::copyToMatrixWithOffset(std::unique_ptr<std::shared_ptr<Shape>[]> &matrixToCopyIn, 
    const size_t columnsWithOffset) const noexcept
{
  for (size_t i = 0; i < rows_ && matrix_[i * columnsAllocated_] != nullptr; i++)
  {
    for (size_t j = 0; j < columnsAllocated_ && matrix_[i * columnsAllocated_ + j] != nullptr; j++)
    {
      matrixToCopyIn[i * columnsWithOffset + j] = matrix_[i * columnsAllocated_ + j];
    }
  }
}



