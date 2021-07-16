
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

#include "../stack.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class StackVec : virtual public Stack<Data>, protected Vector<Data>{

// Most of the member functions recalls to Vector functions.

private:

protected:

  using Vector<Data>::Elements;
  using Vector<Data>::size;
  ulong sentinel = 0;

public:

  // Default constructor.
  StackVec() : Vector<Data>(4) {};

  // Specific constructor.
  StackVec(const LinearContainer<Data>&);

  // Copy constructor.
  StackVec(const StackVec& sv) : Vector<Data>(sv){
    sentinel = sv.sentinel;
  };

  // Move constructor.
  StackVec(StackVec&& sv) noexcept : Vector<Data>(std::move(sv)){
    std::swap(sentinel, sv.sentinel);
  };

  // Destructor.
  ~StackVec();

  // Copy assignment.
  StackVec& operator=(const StackVec&);

  // Move assignment.
  StackVec& operator=(StackVec&&);

  // Comparison operators.
  bool operator==(const StackVec&) const noexcept;
  bool operator!=(const StackVec&) const noexcept;

  // Specific member functions (inherited from Stack).
  void Push(const Data&) override;
  void Push(Data&&) override;
  Data& Top() const override;
  void Pop() override;
  Data TopNPop() override;

  // Specific member functions (inherited from Container).
  bool Empty() const noexcept override;
  ulong Size() const noexcept override;
  void Clear() override;

protected:

  // Auxiliary member functions.
  void Expand();
  void Reduce();

};

}

#include "stackvec.cpp"

#endif
