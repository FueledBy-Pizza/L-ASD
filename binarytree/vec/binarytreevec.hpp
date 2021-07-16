
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data>{

private:

protected:

  using BinaryTree<Data>::size;

  struct NodeVec : public BinaryTree<Data>::Node{

    private:

    protected:

    public:
      NodeVec(const Data&, ulong, Vector<NodeVec*>*);
      ~NodeVec();
      Data x;
      ulong index;
      Vector<NodeVec*>* noderif = nullptr;
      Data& Element() noexcept override;
      const Data& Element() const noexcept override;
      bool HasLeftChild() const noexcept override;
      bool HasRightChild() const noexcept override;
      NodeVec& LeftChild() const override;
      NodeVec& RightChild() const override;

  };

  Vector<NodeVec*> vec;

public:

  // Default constructor.
  BinaryTreeVec() = default;

  // Specific constructors.
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  // Copy constructor.
  BinaryTreeVec(const BinaryTreeVec<Data>&);

  // Move constructor.
  BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept;

  // Destructor.
  ~BinaryTreeVec() = default;

  // Copy assignment.
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment.
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  // Specific member functions (inherited from BinaryTree).
  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  // Specific member functions (inherited from Container).
  void Clear() override; // Override Container member

  // void MapBreadth(const MapFunctor, void*) override;

};

}

#include "binarytreevec.cpp"

#endif
