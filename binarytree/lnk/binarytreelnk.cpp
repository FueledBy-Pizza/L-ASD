
namespace lasd {

  // NodeLnk.
  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& d){
    x = d;
    left = nullptr;
    right = nullptr;
  }

  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& d){
    std::swap(x, d);
    left = nullptr;
    right = nullptr;
  }

  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& n){
    x = n.Element();
    if(n.HasLeftChild()) left = new NodeLnk(n.LeftChild());
    else left = nullptr;
    if(n.HasRightChild()) right = new NodeLnk(n.RightChild());
    else right = nullptr;
  }

  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& n) noexcept{
    std::swap(x, n.Element());
    if(n.HasLeftChild()) left = new NodeLnk(std::move(n.LeftChild()));
    else left = nullptr;
    if(n.HasRightChild()) right = new NodeLnk(std::move(n.RightChild()));
    else right = nullptr;
  }

  // Semantics: destroys the whole tree, binary tree destructor/Clear() only calls delete on root.
  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::~NodeLnk(){
    delete left;
    delete right;
  }

  template <typename Data>
  Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept{
    return x;
  }

  template <typename Data>
  const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept{
    return x;
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept{
    return (left!=nullptr);
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
    return (right!=nullptr);
  }

  template <typename Data>
  typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
    if(HasLeftChild()) return *left;
    else throw std::out_of_range("Left child is null!");
  }

  template <typename Data>
  typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
    if(HasRightChild()) return *right;
    else throw std::out_of_range("Right child is null!");
  }

  // BTLnk.

  // Constructor with a given Linear Container.
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& c){
    size = c.Size();
    root = nullptr;
    if(size!=0){
      root = new NodeLnk(c[0]);
      root->left =  BreadthConstr(c, 1);
      root->right = BreadthConstr(c, 2);
    }
  }

  // Auxiliary function for LinearContainer constructor.
  template <typename Data>
  typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::BreadthConstr(const LinearContainer<Data>& c, const ulong i){
    if(i < c.Size()){
      NodeLnk* tmp = new NodeLnk(c[i]);
      tmp->left = BreadthConstr(c, (2*i)+1);
      tmp->right = BreadthConstr(c, (2*i)+2);
      return tmp;
    }
    return nullptr;
  }

  // Copy constructor.
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk& bt){
    size = bt.Size();
    if(size!=0) root = new NodeLnk(bt.Root());
  }

  // Copy assignment.
  template <typename Data>
  BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt){
    size = bt.Size();
    if(size!=0) root = new NodeLnk(bt.Root());
    return *this;
  }

  // Move constructor.
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& bt) noexcept{
    if(bt.Size()!=0) root = new NodeLnk(std::move(bt.Root()));
    std::swap(size, bt.size);
  }

  // Move assignment.
  template <typename Data>
  BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept{
    if(bt.Size()!=0) root = new NodeLnk(std::move(bt.Root()));
    std::swap(size, bt.size);
    return *this;
  }

  // Destructor, semantics: calls Clear().
  template <typename Data>
  BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    Clear();
  }

  template<typename Data>
  typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const{
    if(size!=0) return *root;
    else throw std::length_error("BinaryTreeLnk is empty!");
  }

  // Semantics: called by the destructor, Clear() calls delete on root, this will trigger NodeLnk destructor, that will delete the whole binary tree.
  template <typename Data>
  void BinaryTreeLnk<Data>::Clear(){
    delete root;
    size = 0;
    root = nullptr;
  }

}
