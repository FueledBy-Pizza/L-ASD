
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

#include "../queue.hpp"
#include "../../list/list.hpp"

namespace lasd {

template <typename Data>
class QueueLst : virtual public Queue<Data>, protected List<Data>{

// All the member functions recalls to List functions.

private:

protected:

  using List<Data>::size;
  using List<Data>::top;
  using List<Data>::tail;

public:

  // Default constructor.
  QueueLst() : List<Data>(){};

  // Specific constructor.
  QueueLst(const LinearContainer<Data>& c) : List<Data>(c){};

  // Copy constructor.
  QueueLst(const QueueLst& ql) : List<Data>(ql){};

  // Move constructor.
  QueueLst(QueueLst&& ql) noexcept : List<Data>(std::move(ql)){};

  // Destructor.
  ~QueueLst();                          // Destructor, like List destructor, calls Clear().

  // Copy assignment.
  QueueLst& operator=(const QueueLst&);

  // Move assignment.
  QueueLst& operator=(QueueLst&&) noexcept;

  void Enqueue(const Data&) override;
  void Enqueue(Data&&) override;
  Data& Head() const override;
  void Dequeue() override;
  Data HeadNDequeue() override;

  // Comparison operators.
  bool operator==(const QueueLst&) const noexcept;
  bool operator!=(const QueueLst&) const noexcept;

  // Specific member functions (inherited from Container)
  void Clear() override;

};

}

#include "queuelst.cpp"

#endif
