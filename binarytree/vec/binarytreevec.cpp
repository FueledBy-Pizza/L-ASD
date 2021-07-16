
namespace lasd {

  // NodeVec.

  // Constructor.
  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& d, ulong i, Vector<NodeVec*>* v){
    x = d;
    index = i;
    noderif = v;
  }

  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::~NodeVec(){
    if(HasLeftChild()) delete (*noderif)[(2*index)+1];    // Il dereferenziamento va fatto in questo modo, perché devo prima dereferenziare la variabile vettore.
    if(HasRightChild()) delete (*noderif)[(2*index)+2];
  }

  template <typename Data>
  Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept{
    return x;
  }

  template <typename Data>
  const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept{
    return x;
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
    if((2*index)+1 > (noderif->Size())-1) return false;
    return true;
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    if((2*index)+2 > (noderif->Size())-1) return false;
    return true;
  }

  template <typename Data>
  typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const{
    if(HasLeftChild()) return *((*noderif)[(2*index)+1]);
    else throw std::out_of_range("Left child doesn't exists, exceeded vector size!");
  }

  template <typename Data>
  typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const{
    if(HasRightChild()) return *((*noderif)[(2*index)+2]);
    else throw std::out_of_range("Right child doesn't exists, exceeded vector size!");
  }

  // BTVec.

  // Costructor with a given Linear Container.
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& c){
    size = c.Size();
    vec.Resize(size);
    for(ulong i = 0; i < size; i++){
      vec[i] = new NodeVec(c[i], i, &vec);
    }
  }

  // Copy costructor.
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bt){
    size = bt.Size();
    vec.Resize(size);
    for (ulong i = 0; i < size; i++){
      vec[i] = new NodeVec(bt.vec[i]->Element(), i, &vec);
    }
  }

  // Copy assignment.
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt){
    size = bt.Size();
    vec.Resize(size);
    for (ulong i = 0; i < size; i++){
      vec[i] = new NodeVec(bt.vec[i]->Element(), i, &vec);
    }
    return *this;
  }

  // Move constructor.
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& bt) noexcept{
    std::swap(size, bt.size);
    vec.Resize(size);
    for (ulong i = 0; i < size; i++){
      std::swap(vec[i], (bt.vec)[i]);
      // il noderif va cambiato...
      vec[i]->noderif = &vec;
    }
  }

  // Move assignment.
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& bt) noexcept{
    std::swap(size, bt.size);
    vec.Resize(size);
    for (ulong i = 0; i < size; i++){
      std::swap(vec[i], (bt.vec)[i]);
      // il noderif va cambiato...
      vec[i]->noderif = &vec;
    }
    return *this;
  }

  template <typename Data>
  typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
    if(!(vec.Empty())) return *vec[0];
    else throw std::length_error("Tree is empty! Root()exc.");
  }

  // Same BTLnk semantic: delete root, this will trigger the delete (in postorder) of each BT NodeVec.
  template <typename Data>
  void BinaryTreeVec<Data>::Clear(){
    if(size>0){
      delete vec[0];
      size = 0;         // size dell'albero...
    }
    vec.Clear();        // Metterà a 0 la size del vettore...
  }

  // template <typename Data>
  // void BinaryTreeVec<Data>::MapBreadth(const MapFunctor fun, void* par){
  //   for(ulong i = 0; i < size; i++){
  //     fun(vec[i]->Element(), par);
  //   }
  // }

}
