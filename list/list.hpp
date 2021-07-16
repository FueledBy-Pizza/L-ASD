
#ifndef LIST_HPP
#define LIST_HPP

#include "../container/container.hpp"

namespace lasd {

template <typename Data>
class List : virtual public LinearContainer<Data>, virtual public MappableContainer<Data>, virtual public FoldableContainer<Data>{

private:

protected:

  using LinearContainer<Data>::size;

  struct Node{

    Data x;
    Node* next = nullptr;

    Node() = default;

    // Specific constructor, used by list constructor given a linear container and by Inserts.
    Node(const Data&);

    // Copy constructor, used by List copy constructor, in order to have a cascade behaviour.
    Node(const Node&);

    // Destructor.
    ~Node() = default;

  };

  Node* top = nullptr;
  Node* tail = nullptr;

public:

  // Default constructor.
  List() = default;

  // Specific constructor with a given linear container, uses Node specific constructor.
  List(const LinearContainer<Data>&);

  // Copy constructor, uses Node copy constructor to trigger a cascade list construction.
  List(const List&);

  // Move constructor.
  List(List&&) noexcept;

  // Destructor.
  ~List();                             // List destructor calls Clear().

  // Copy assignment.
  List& operator=(const List&);

  // Move assignment.
  List& operator=(List&&) noexcept;

  // Comparison operators.
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;

  // Specific member functions.
  void InsertAtFront(const Data&);
  void InsertAtFront(Data&&);
  void RemoveFromFront();
  Data FrontNRemove();
  void InsertAtBack(const Data&);
  void InsertAtBack(Data&&);

  // Specific member functions (inherited from Container).
  void Clear() override; // Destructs the list.

  // Specific member functions (inherited from LinearContainer).
  Data& Front() const override;
  Data& Back() const override;
  Data& operator[](const ulong) const override;

  // Specific member functions (inherited from MappableContainer).
  using typename MappableContainer<Data>::MapFunctor;
  void MapPreOrder(const MapFunctor, void*) override;                               // MapPreOrder calls Auxiliary MapPreOrder.
  void MapPostOrder(const MapFunctor, void*) override;                              // MapPostOrder calls Auxiliary MapPostOrder.

  // Specific member functions (inherited from FoldableContainer).
  using typename FoldableContainer<Data>::FoldFunctor;
  void FoldPreOrder(const FoldFunctor, const void*, void*) const override;          // FoldPreOrder calls Auxiliary FoldPreOrder.
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override;         // FoldPostOrder calls Auxiliary FoldPostOrder.

protected:

  // Auxiliary member functions (for MappableContainer).
  void MapPreOrder(const MapFunctor, void*, Node*);                                 // Recursive...
  void MapPostOrder(const MapFunctor, void*, Node*);                                // Recursive...

  // Auxiliary member functions (for FoldableContainer).
  void FoldPreOrder(const FoldFunctor, const void*, void*, Node*) const;            // Recursive...
  void FoldPostOrder(const FoldFunctor, const void*, void*, Node*) const;           // Recursive...

};

}

#include "list.cpp"

#endif
