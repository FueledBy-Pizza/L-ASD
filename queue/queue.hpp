
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../container/container.hpp"

namespace lasd {

template <typename Data>
class Queue : virtual public Container{

private:

protected:

public:

  // Constructor.
  Queue() = default;

  // Destructor.
  virtual ~Queue() = default;

  // Copy assignment.
  Queue& operator=(const Queue&);

  // Move assignment.
  Queue& operator=(Queue&&);

  // Comparison operators.
  bool operator==(const Queue&) const noexcept;
  bool operator!=(const Queue&) const noexcept;

  // Specific member functions.
  virtual void Enqueue(const Data&) = 0;
  virtual void Enqueue(Data&&) = 0;
  virtual Data& Head() const = 0;
  virtual void Dequeue() = 0;
  virtual Data HeadNDequeue() = 0;

};

}

#endif
