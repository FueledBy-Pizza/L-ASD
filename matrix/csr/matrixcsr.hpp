#ifndef MATRIXCSR_HPP
#define MATRIXCSR_HPP
#include "../matrix.hpp"
#include "../../list/list.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class MatrixCSR : virtual public Matrix<Data>, protected List<std::pair<Data, ulong>>{ // Must extend Matrix<Data>

private:

protected:

  using Matrix<Data>::size;
  using Matrix<Data>::row;
  using Matrix<Data>::col;
  using List<std::pair<Data, ulong>>::top;
  using List<std::pair<Data, ulong>>::tail;
  using typename List<std::pair<Data, ulong>>::Node;
  Vector<Node**> vec;

public:

  // Default constructor.
  MatrixCSR();

  // Specific constructors.
  MatrixCSR(const ulong, const ulong); // A matrix of some specified dimension

  // Destructor.
  ~MatrixCSR() = default;

  // Copy constructor.
  MatrixCSR(const MatrixCSR&);

  // Move constructor.
  MatrixCSR(MatrixCSR&&) noexcept;

  // Copy assignment.
  MatrixCSR& operator=(const MatrixCSR<Data>&);

  // Move assignment.
  MatrixCSR& operator=(MatrixCSR<Data>&&) noexcept;

  // Comparison operators.
  bool operator==(const MatrixCSR<Data>&) const noexcept;
  bool operator!=(const MatrixCSR<Data>&) const noexcept;

  // Specific member functions (inherited from Matrix).
  void RowResize(const ulong) override; // Override Matrix member
  void ColumnResize(const ulong) override; // Override Matrix member

  bool ExistsCell(const ulong, const ulong) const noexcept; // Override Matrix member (should not throw exceptions)

  Data& operator()(const ulong, const ulong) override; // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  const Data& operator()(const ulong, const ulong) const override; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  // Specific member functions (inherited from Container).
  void Clear() override; // Override Container member

  // Specific member functions (inherited from MappableContainer).
  using typename MappableContainer<Data>::MapFunctor;
  void MapPreOrder(const MapFunctor, void*) override; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void*) override; // Override MappableContainer member

  // Specific member functions (inherited from FoldableContainer).
  using typename FoldableContainer<Data>::FoldFunctor;
  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

};

}

#include "matrixcsr.cpp"

#endif
