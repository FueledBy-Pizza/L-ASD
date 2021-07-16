
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include "../container/container.hpp"
#include "../iterator/iterator.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../stack/lst/stacklst.hpp"

namespace lasd {

template <typename Data>
class BinaryTree : virtual public InOrderMappableContainer<Data>, virtual public BreadthMappableContainer<Data>, virtual public InOrderFoldableContainer<Data>, virtual public BreadthFoldableContainer<Data>{ // Must extend InOrder/BreadthMappableContainer<Data> and InOrder/BreadthFoldableContainer<Data>

private:

protected:

  using BreadthMappableContainer<Data>::size;

public:

  // Unlike the List Node, here Node is public, accessible from the user.
  struct Node {

    private:

    protected:
      // Comparison operators.
      bool operator==(const Node&) const noexcept; // Comparison of abstract types is possible, but should not be visible.
      bool operator!=(const Node&) const noexcept; // Comparison of abstract types is possible, but should not be visible.

    public:

      friend class BinaryTree<Data>;    // potrebbe servire se implementassimo gli operator == e !=, ad esempio se in essi ci servisse la size...

      // Destructor.
      virtual ~Node() = default;

      // Constructor.
      Node() = default;

      // Copy constructor.
      // Node(const Node&);

      // Copy assignment.
      Node& operator=(const Node&) = delete;

      // Move assignment.
      Node& operator=(Node&&) noexcept = delete;

      // Specific member functions.
      virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)
      virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

      bool IsLeaf() noexcept; // posso anche già implementarla qui usando hasleft/right implementate nel BT concreto
      virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
      virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

      // Thanks to these member functions, we can concretely define many member functions of the class BinaryTree, already at this abstraction level.
      virtual Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
      virtual Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  // Destructor.
  virtual ~BinaryTree() = default;

  // Copy assignment.
  virtual BinaryTree& operator=(const BinaryTree&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment.
  virtual BinaryTree& operator=(BinaryTree&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators.
  bool operator==(const BinaryTree&) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree&) const noexcept; // Comparison of abstract binary tree is possible.

  // Specific member functions.
  virtual Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  // Specific member functions (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFunctor;
  void MapPreOrder(const MapFunctor, void*) override; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void*) override; // Override MappableContainer member

  // Specific member functions (inherited from FoldableContainer)
  using typename FoldableContainer<Data>::FoldFunctor;
  void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  // Specific member functions (inherited from InOrderMappableContainer)
  void MapInOrder(const MapFunctor, void*) override; // Override InOrderMappableContainer member

  // Specific member functions (inherited from InOrderFoldableContainer)
  void FoldInOrder(const FoldFunctor, const void*, void*) const override; // Override InOrderFoldableContainer member

  // valutare di quali funzioni posso fare l'override nelle implementazioni più concrete(solo per un vantaggio di efficienza)
  // ad esempio per le breadth potrebbe avere un senso nei vettori...
  // Specific member functions (inherited from BreadthMappableContainer)
  void MapBreadth(const MapFunctor, void*) override; // Override BreadthMappableContainer member

  // Specific member functions (inherited from BreadthFoldableContainer)
  void FoldBreadth(const FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member

protected:

  // Auxiliary member functions (for MappableContainer).
  // Recursive...
  void MapPreOrder(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree
  void MapPostOrder(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

  // Auxiliary member functions (for FoldableContainer)
  // Recursive...
  void FoldPreOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree
  void FoldPostOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

  // Auxiliary member functions (for InOrderMappableContainer)
  // Recursive...
  void MapInOrder(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

  // Auxiliary member functions (for InOrderFoldableContainer)
  // Recursive...
  void FoldInOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

  // Auxiliary member functions (for BreadthMappableContainer)
  // Recursive...
  void MapBreadth(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

  // Auxiliary member functions (for BreadthFoldableContainer)
  // Recursive...
  void FoldBreadth(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

};

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>{

private:

protected:

  typename BinaryTree<Data>::Node* pn = nullptr;
  StackLst<typename BinaryTree<Data>::Node*> sl{};

public:

  // It obviously just exists a specific iterator constructor, not a default one.
  // Specific constructors.
  BTPreOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  // Copy constructor.
  BTPreOrderIterator(const BTPreOrderIterator&);

  // Copy assignment.
  BTPreOrderIterator& operator=(const BTPreOrderIterator&);

  // Move constructor.
  BTPreOrderIterator(BTPreOrderIterator&&) noexcept;

  // Move assignment.
  BTPreOrderIterator& operator=(BTPreOrderIterator&&) noexcept;

  // Destructor.
  ~BTPreOrderIterator() = default;

  // Comparison operators.
  bool operator==(const BTPreOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPreOrderIterator<Data>&) const noexcept;

  // Specific member functions (inherited from Iterator).
  Data& operator*() const override; // (throw std::out_of_range when terminated)
  bool Terminated() const noexcept override; // (should not throw exceptions)

  // Specific member functions (inherited from ForwardIterator).
  BTPreOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

};

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>{

private:

protected:

  typename BinaryTree<Data>::Node* pn = nullptr;
  StackLst<typename BinaryTree<Data>::Node*> sl{};

  // Auxiliary functions.
  typename BinaryTree<Data>::Node* LeftMostLeaf(typename BinaryTree<Data>::Node*) noexcept;

public:

  // Specific constructors.
  BTPostOrderIterator(const BinaryTree<Data>&);   // A differenza degli iteratori Pre e Breadth, qui già inizializzo lo stack.

  // Copy constructor.
  BTPostOrderIterator(const BTPostOrderIterator&);

  // Copy assignment.
  BTPostOrderIterator& operator=(const BTPostOrderIterator&);

  // Move constructor.
  BTPostOrderIterator(BTPostOrderIterator&&) noexcept;

  // Move assignment.
  BTPostOrderIterator& operator=(BTPostOrderIterator&&) noexcept;

  // Destructor.
  ~BTPostOrderIterator() = default;

  // Comparison operators.
  bool operator==(const BTPostOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPostOrderIterator<Data>&) const noexcept;

  // Specific member functions (inherited from Iterator).
  Data& operator*() const override; // (throw std::out_of_range when terminated)
  bool Terminated() const noexcept override; // (should not throw exceptions)

  // Specific member functions (inherited from ForwardIterator).
  BTPostOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

};

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>{

private:

protected:

  typename BinaryTree<Data>::Node* pn = nullptr;
  StackLst<typename BinaryTree<Data>::Node*> sl{};

  // Auxiliary functions.
  typename BinaryTree<Data>::Node* LeftMostNode(typename BinaryTree<Data>::Node*) noexcept;

public:

  // Specific constructors.
  // Specific constructors.
  BTInOrderIterator(const BinaryTree<Data>&);   // A differenza degli iteratori Pre e Breadth, qui già inizializzo lo stack.

  // Copy constructor.
  BTInOrderIterator(const BTInOrderIterator&);

  // Copy assignment.
  BTInOrderIterator& operator=(const BTInOrderIterator&);

  // Move constructor.
  BTInOrderIterator(BTInOrderIterator&&) noexcept;

  // Move assignment.
  BTInOrderIterator& operator=(BTInOrderIterator&&) noexcept;

  // Destructor.
  ~BTInOrderIterator() = default;

  // Comparison operators.
  bool operator==(const BTInOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTInOrderIterator<Data>&) const noexcept;

  // Specific member functions (inherited from Iterator).
  Data& operator*() const override; // (throw std::out_of_range when terminated)
  bool Terminated() const noexcept override; // (should not throw exceptions)

  // Specific member functions (inherited from ForwardIterator).
  BTInOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

};

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>{

private:

protected:

  typename BinaryTree<Data>::Node* pn = nullptr;
  QueueLst<typename BinaryTree<Data>::Node*> ql{};

public:

  // Specific constructors.
  BTBreadthIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  // Copy constructor.
  BTBreadthIterator(const BTBreadthIterator<Data>&);

  // Copy assignment.
  BTBreadthIterator& operator=(const BTBreadthIterator<Data>&);

  // Move constructor.
  BTBreadthIterator(BTBreadthIterator<Data>&&) noexcept;

  // Move assignment.
  BTBreadthIterator& operator=(BTBreadthIterator<Data>&&) noexcept;

  // Destructor.
  ~BTBreadthIterator() = default;

  // Comparison operators.
  bool operator==(const BTBreadthIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthIterator<Data>&) const noexcept;

  // Specific member functions (inherited from Iterator).
  Data& operator*() const override; // (throw std::out_of_range when terminated)
  bool Terminated() const noexcept override; // (should not throw exceptions)

  // Specific member functions (inherited from ForwardIterator).
  BTBreadthIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

};

}

#include "binarytree.cpp"

#endif
