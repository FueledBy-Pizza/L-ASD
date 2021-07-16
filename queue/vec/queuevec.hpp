
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

#include "../queue.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class QueueVec : virtual public Queue<Data>, protected Vector<Data>{

private:

protected:
  /* Principle to expand the structure: inserting the (QueueVec.size-1)th element.
     Effect caused: obtain double QueueVec.size; elements numbered from 0.*/
  /* Principle to reduce the structure: removing the [(QueueVec.size/4)+1]th element.
     Effect caused: obtain half QueueVec.size; elements numbered from 0.*/

  using Vector<Data>::Elements;
  using Vector<Data>::size;             // QueueVec.size will be a power of two, starting from 4.
  ulong head = 0;                       // Head "points" to the first concrete element existing in the queue, if queue is not empty (i.e. head==tail).
  ulong tail = 0;                       // Tail "points" to the position to insert the next element in the queue.

public:

  // All the costructors initialize QueueVec Elements starting from index 0.

  // Default constructor.
  QueueVec() : Vector<Data>(4) {};

  // Specific constructor.
  QueueVec(const LinearContainer<Data>&); // A queue obtained from a LinearContainer

  // Copy constructor.
  QueueVec(const QueueVec<Data>&);

  // Move constructor.
  QueueVec(QueueVec<Data>&&);

  // Destructor.
  ~QueueVec() = default;

  // Copy assignment.
  QueueVec<Data>& operator=(const QueueVec<Data>&);

  // Move assignment.
  QueueVec<Data>& operator=(QueueVec<Data>&&);

  // Comparison operators.
  bool operator==(const QueueVec<Data>&) const noexcept;
  bool operator!=(const QueueVec<Data>&) const noexcept;

  // Specific member functions (inherited from Queue).
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)
  Data& Head() const override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)

  // Specific member functions (inherited from Container).
  bool Empty() const noexcept override; // Override Container member
  ulong Size() const noexcept override; // Size() is not size !!! Override Container member
  void Clear() override; // La semantica della QueueVec.Clear() è di riportare la coda al suo stato iniziale (size=head=tail=0), non di avere lo stesso comportamento del distruttore (semantica che è invece di Vector e di List).

protected:

  // Auxiliary member functions.
  void IncrementQueueIndex(ulong&) const noexcept;    // Proper increment of an index scanning a queue, thus based on circularity and on concrete size ( Size() ) of the queue.
  void Expand();
  void Reduce();

};

}

#include "queuevec.cpp"

#endif
