
#ifndef STACK_HPP
#define STACK_HPP

#include "../container/container.hpp"

namespace lasd {

template <typename Data>
class Stack : virtual public Container{

private:

protected:

public:

  // Constructor.
  Stack() = default;

  // Destructor.
  virtual ~Stack() = default;

  // Copy assignment.
  Stack& operator=(const Stack&);

  // Move assignment.
  Stack& operator=(Stack&&) noexcept;

  // Comparison operators.
  bool operator==(const Stack&) const noexcept;
  bool operator!=(const Stack&) const noexcept;

  // Specific member functions.
  virtual void Push(const Data&) = 0;
  virtual void Push(Data&&) = 0;
  virtual Data& Top() const = 0;
  virtual void Pop() = 0;
  virtual Data TopNPop() = 0;

};

}

#endif
