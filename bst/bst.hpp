
#ifndef BST_HPP
#define BST_HPP
#include "../binarytree/lnk/binarytreelnk.hpp"

namespace lasd {

template <typename Data>
class BST : public BinaryTreeLnk<Data>{
private:

protected:

  using BinaryTreeLnk<Data>::root;
  using BinaryTreeLnk<Data>::size;
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  // Default constructor.
  BST() = default;

  // Specific constructors.
  /* Semantica: scegliere tra l'ordinare il linear container e poi riversarlo in un BTLink tramite ricerca binaria, oppure inserire ogni volta ordinatamente un elemento dal linear container,
   scegliamo la seconda, perchè mediamente costruirà comunque un albero bilanciato -sempre a costo nlgn-, quindi è conveniente seguire la seconda scelta, perchè più semplice. */
  BST(LinearContainer<Data>&); // A bst obtained from a LinearContainer

  // Copy constructor.
  BST(const BST& bst) : BinaryTreeLnk<Data>(bst) {};
  // Copy assignment.
  BST& operator=(const BST&);

  // Move constructor.
  BST(BST&& bst) noexcept : BinaryTreeLnk<Data>(std::move(bst)) {};
  // Move assignment.
  BST& operator=(BST&&) noexcept;

  // Destructor.
  ~BST() = default;

  // Comparison operators.
  bool operator==(const BST<Data>&) const noexcept;
  bool operator!=(const BST<Data>&) const noexcept;

  // Specific member functions.
  void Insert(const Data&) noexcept; // Copy of the value.
  void Insert(Data&&) noexcept; // Move of the value.
  void Remove(const Data&) noexcept;

  // Nelle funzioni Min/Max e Predecessor/Successor, vogliamo che l'utente non andrà modificare comunque questo dato che riceve di ritorno, altrimenti potrà ovviamente violare la condizione di bst.
  // n.b. Il riferimento come ritorno lo usiamo per efficienza.

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  // Successor/Predecessor throws exception if bst is empty, or if max/min of the tree is less/greater or equal than the element you want to search the successor/predecessor of.
  const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when empty)
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when empty)
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when empty)

  const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when empty)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when empty)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when empty)

  // Specific member functions (inherited from TestableContainer).
  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

protected:

  /* Auxiliary member functions: */

  // Used by *NRemove functions.
  Data DataNDelete(NodeLnk*);

  NodeLnk* Detach(NodeLnk*&);                                             // Detach is the function that really evaluate the deleting cases (has left, has right, has neither, has both...).
  NodeLnk* DetachMin(NodeLnk*&);                                          // Detaches the min node, than returns it.

  // "Skips" the node received, then returns the node "skipped".
  NodeLnk* SkipOnLeft(NodeLnk*&);
  NodeLnk* SkipOnRight(NodeLnk*&);

  // Auxiliary function used by all the others functions that could modify the structure.
  NodeLnk* const& FindPointerTo(NodeLnk* const &, const Data&) const;     // Const return type.
  NodeLnk*& FindPointerTo(NodeLnk*&, const Data&);                        // Non-const return type.

  // Auxiliary to Min.
  NodeLnk* const& FindPointerToMin(NodeLnk* const &) const;               // Const return type.
  NodeLnk*& FindPointerToMin(NodeLnk*&);                                  // Non-const return type.

  // Auxiliary to Max.
  NodeLnk* const& FindPointerToMax(NodeLnk* const &) const;               // Const return type.
  NodeLnk*& FindPointerToMax(NodeLnk*&);                                  // Non-const return type.

  // Auxiliary to Predecessor.
  NodeLnk* const & FindPointerToPredecessor(NodeLnk* const &, NodeLnk* const &, const Data&) const;

  // Auxiliary to Successor.
  NodeLnk* const & FindPointerToSuccessor(NodeLnk* const &, NodeLnk* const &, const Data&) const;

  // Auxiliary functions to sort the LinearContainer before construct a BST.
  // NodeLnk* SortedCostr(LinearContainer<Data>&, long, long);
  // void QuickSort(LinearContainer<Data>&, ulong, ulong);
  // ulong Partiziona(LinearContainer<Data>&, ulong, ulong);
  // void Swap(LinearContainer<Data>&, ulong, ulong);

};

}

#include "bst.cpp"

#endif
