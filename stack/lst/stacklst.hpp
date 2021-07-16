
#ifndef STACKLST_HPP
#define STACKLST_HPP

#include "../stack.hpp"
#include "../../list/list.hpp"

namespace lasd {

template <typename Data>
class StackLst : virtual public Stack<Data>, protected List<Data>{

// All the member functions recalls to List functions.

private:

protected:

  using List<Data>::size;
  using List<Data>::top;
  using List<Data>::tail;

public:

  // Default constructor.
  StackLst() : List<Data>(){};

  // Specific constructor.
  StackLst(const LinearContainer<Data>& c) : List<Data>(c){};

  // Copy constructor.
  StackLst(const StackLst& sl) : List<Data>(sl){};

  // Move constructor.
  StackLst(StackLst&& sl) noexcept : List<Data>(std::move(sl)){};

  // Destructor.
  ~StackLst();

  // Copy assignment.
  StackLst& operator=(const StackLst&);

  // Move assignment.
  StackLst& operator=(StackLst&&) noexcept;

  // Comparison operators.
  bool operator==(const StackLst&) const noexcept;
  bool operator!=(const StackLst&) const noexcept;

  // Specific member functions (inherited from Stack)
  void Push(const Data&) override;
  void Push(Data&&) override;
  Data& Top() const override;
  void Pop() override;
  Data TopNPop() override;

  // Specific member functions (inherited from Container)
  void Clear() override;

};

}

#include "stacklst.cpp"

#endif
