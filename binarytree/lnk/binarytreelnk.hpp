#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

#include "../binarytree.hpp"

namespace lasd {

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data>{ // Must extend BinaryTree<Data>

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk : virtual public BinaryTree<Data>::Node{

    private:

    protected:

    public:
      NodeLnk(const Data&);                                 // Constructor of a NodeLnk given a Data -Copy of the value-.
      NodeLnk(Data&&);                                      // Constructor of a NodeLnk given a Data -Move of the value-.
      NodeLnk(const NodeLnk&);                              // Copy constructor of a NodeLnk given a NodeLnk, needed to BTLnk constructors.
      NodeLnk(NodeLnk&&) noexcept;                          // Move constructor of a NodeLnk given a NodeLnk, needed to BTLnk constructors.
      ~NodeLnk();                                           // Destructor.
      Data x;
      NodeLnk* left;
      NodeLnk* right;
      Data& Element() noexcept override;                    // Gives a non const Data x of the node.
      const Data& Element() const noexcept override;        // Gives a const Data x of the node.
      bool HasLeftChild() const noexcept override;
      bool HasRightChild() const noexcept override;
      NodeLnk& LeftChild() const override;
      NodeLnk& RightChild() const override;
  };

  NodeLnk* root = nullptr;

  // Auxiliary BTLnk constructor function.
  NodeLnk* BreadthConstr(const LinearContainer<Data>&, const ulong);

public:

  /* Constructor/Destructor semantic: calling constructor/destructor on root, NodeLnk constructors/destructors will construct/destruct the BTLnk. */

  // Default constructor.
  BinaryTreeLnk() = default;

  // Specific constructors.
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  // Constructors semantic: construct a new root node, this will trigger a node constructor cascade...
  // Copy constructor.
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor.
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

  // Destructor.
  // Destructor semantic: destruct root, this will trigger all the node destructors cascade...
  ~BinaryTreeLnk();

  // Copy assignment.
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment.
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  // Specific member functions (inherited from BinaryTree).
  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  // Specific member functions (inherited from Container).
  void Clear() override; // Override Container member

};

}

#include "binarytreelnk.cpp"

#endif
