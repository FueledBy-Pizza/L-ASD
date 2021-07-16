
#ifndef MATRIXVEC_HPP
#define MATRIXVEC_HPP
#include "../matrix.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class MatrixVec : virtual public Matrix<Data>, virtual protected Vector<Data>{ // Must extend Matrix<Data>

private:

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;
  using Matrix<Data>::row;
  using Matrix<Data>::col;

public:

  // Most of the member functions recalls Vector member functions.

  // Default constructor.
  MatrixVec() = default;

  // Specific constructors.
  MatrixVec(const ulong r, const ulong c) : Vector<Data>::Vector(r*c){
    row = r;
    col = c;
  }; // A matrix of some specified dimension.

  // Copy constructor.
  MatrixVec(const MatrixVec<Data>& m) : Vector<Data>::Vector(m){
    row = m.row;
    col = m.col;
  };

  // Move constructor.
  MatrixVec(MatrixVec<Data>&& m) : Vector<Data>::Vector(std::move(m)){
    std::swap(row, m.row);
    std::swap(col, m.col);
  };

  // Destructor.
  virtual ~MatrixVec();

  // Copy assignment.
  MatrixVec& operator=(const MatrixVec<Data>&);

  // Move assignment.
  MatrixVec& operator=(MatrixVec<Data>&&);

  // Comparison operators.
  bool operator==(const MatrixVec<Data>&) const noexcept;
  bool operator!=(const MatrixVec<Data>&) const noexcept;

  // Specific member functions (inherited from Matrix).
  // Per RowResize() riusiamo il metodo di Vector, non possiamo fare lo stesso con ColumnResize(), perchè i dati vanno copiati in modo diverso...
  void RowResize(const ulong) override; // Override Matrix member
  void ColumnResize(const ulong) override; // Override Matrix member
  bool ExistsCell(const ulong, const ulong) const noexcept override; // Override Matrix member (should not throw exceptions)

  Data& operator()(const ulong, const ulong) override; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  const Data& operator()(const ulong, const ulong) const override; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  // Specific member functions (inherited from Container).
  void Clear() override; // Override Container member

  // Specific member functions (inherited from MappableContainer).
  using Vector<Data>::MapPreOrder; // Override MappableContainer member
  using Vector<Data>::MapPostOrder;

  // Specific member functions (inherited from FoldableContainer).
  using Vector<Data>::FoldPreOrder; // Override FoldableContainer member
  using Vector<Data>::FoldPostOrder;

};

}

#include "matrixvec.cpp"

#endif
