
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "../container/container.hpp"

namespace lasd {

template <typename Data>
class Matrix : virtual public MappableContainer<Data>, virtual public FoldableContainer<Data> { // Must extend MappableContainer<Data> and FoldableContainer<Data>

private:

protected:

  ulong row = 0;
  ulong col = 0;

public:

  // Destructor.
  virtual ~Matrix() = default;

  // Copy assignment.
  virtual Matrix<Data>& operator=(const Matrix<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment.
  virtual Matrix<Data>& operator=(Matrix<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators.
  bool operator==(const Matrix<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Matrix<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  // Specific member functions.
  inline const ulong& RowNumber() const; // (concrete function should not throw exceptions)
  inline const ulong& ColumnNumber() const; // (concrete function should not throw exceptions)

  virtual void RowResize(const ulong) = 0;
  virtual void ColumnResize(const ulong) = 0;

  virtual bool ExistsCell(const ulong, const ulong) const noexcept = 0; // (concrete function should not throw exceptions)

  virtual Data& operator()(const ulong, const ulong) = 0; // Mutable access to the element (concrete function should throw exceptions only when out of range)
  virtual const Data& operator()(const ulong, const ulong) const = 0; // Immutable access to the element (concrete function should throw exceptions when not present)

};

}

#include "matrix.cpp"

#endif
