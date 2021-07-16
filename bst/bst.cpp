namespace lasd {

  /* PUBLIC PROCEDURES */

  // Specific constructor.
  template <typename Data>
  BST<Data>::BST(LinearContainer<Data>& c){
    for(ulong i = 0; i < c.Size(); i++) Insert(c[i]);
    size = c.Size();
  }

  // Copy assignment.
  template <typename Data>
  BST<Data>& BST<Data>::operator=(const BST<Data>& bst){
    BinaryTreeLnk<Data>::operator=(bst);
    return *this;
  }

  // Move assignment.
  template <typename Data>
  BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept{
    BinaryTreeLnk<Data>::operator=(std::move(bst));
    return *this;
  }

  // Comparison operators.
  template <typename Data>
  bool BST<Data>::operator==(const BST<Data>& bst) const noexcept{
    if(this->Empty() && bst.Empty()) return true;
    if(!(this->Empty()) && !(bst.Empty())){
      if(this->Size()!=bst.Size()) return false;
      BTInOrderIterator<Data> i(*this);
      BTInOrderIterator<Data> i2(bst);
      while(!(i.Terminated()) && (*i==*i2)){        // Mi basta solo un controllo di terminazione su uno dei due iteratori, già so che gli alberi hanno la stessa dimensione (i.e. gli iteratori hanno la stessa "dimensione")...
        ++i;
        ++i2;
      }
      if(i.Terminated()) return true;
      else return false;
    }
    return false;
  }

  template <typename Data>
  bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept{
    return !(*this==bst);
  }

  // Copy of the value.
  template <typename Data>
  void BST<Data>::Insert(const Data& d) noexcept{
    NodeLnk*& newnode = FindPointerTo(root, d);
    if(newnode == nullptr){
      newnode = new NodeLnk(d);
      size++;
    }
  }

  // Move of the value.
  template <typename Data>
  void BST<Data>::Insert(Data&& d) noexcept{
    NodeLnk*& newnode = FindPointerTo(root, d);
    if(newnode == nullptr){
      newnode = new NodeLnk(d);
      size++;
    }
  }

  template <typename Data>
  void BST<Data>::Remove(const Data& d) noexcept{
    NodeLnk*& n = FindPointerTo(root, d);
    if(n != nullptr){
      delete Detach(n);
      size--;
    }
  }

  template <typename Data>
  const Data& BST<Data>::Min() const{
    if(!(this->Empty())) return (FindPointerToMin(root))->x;
    else throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  Data BST<Data>::MinNRemove(){
    if(!(this->Empty())) return DataNDelete(FindPointerToMin(root));
    else throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  void BST<Data>::RemoveMin(){
    if(!(this->Empty())) Remove(FindPointerToMin(root)->x);
    else throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  const Data& BST<Data>::Max() const{
    if(!(this->Empty())) return (FindPointerToMax(root))->x;
    else throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  Data BST<Data>::MaxNRemove(){
    if(!(this->Empty())) return DataNDelete(FindPointerToMax(root));
    else throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  void BST<Data>::RemoveMax(){
    if(!(this->Empty())) Remove(FindPointerToMax(root)->x);
    else throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  const Data& BST<Data>::Predecessor(const Data& d) const{
    if(!(this->Empty())){
      NodeLnk* s = FindPointerToPredecessor(root, nullptr, d);
      if(s!=nullptr) return s->x;
      throw std::length_error("BST: Doesn't exist a predecessor, min of the tree is greater-equal than the element you searched predecessor of.");        // when d <= min(bst)
    }
    throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  Data BST<Data>::PredecessorNRemove(const Data& d){
    if(!(this->Empty())){
      NodeLnk* s = FindPointerToPredecessor(root, nullptr, d);
      if(s!=nullptr) return DataNDelete(s);
      throw std::length_error("BST: Doesn't exist a predecessor, min of the tree is greater-equal than the element you searched predecessor of.");        // when d <= min(bst)
    }
    throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  void BST<Data>::RemovePredecessor(const Data& d){
    if(!(this->Empty())){
      NodeLnk* s = FindPointerToPredecessor(root, nullptr, d);
      if(s!=nullptr) Remove(s->x);
      else throw std::length_error("BST: Doesn't exist a predecessor, min of the tree is greater-equal than the element you searched predecessor of.");   // when d <= min(bst)
    }
    else throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  const Data& BST<Data>::Successor(const Data& d) const{
    if(!(this->Empty())){
      NodeLnk* s = FindPointerToSuccessor(root, nullptr, d);
      if(s!=nullptr) return s->x;
      throw std::length_error("BST: Doesn't exist a successor, max of the tree is less-equal than the element you searched successor of.");          // when d >= max(bst)
    }
    throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  Data BST<Data>::SuccessorNRemove(const Data& d){
    if(!(this->Empty())){
      NodeLnk* s = FindPointerToSuccessor(root, nullptr, d);
      if(s!=nullptr) return DataNDelete(s);
      throw std::length_error("BST: Doesn't exist a successor, max of the tree is less-equal than the element you searched successor of.");          // when d >= max(bst)
    }
    throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  void BST<Data>::RemoveSuccessor(const Data& d){
    if(!(this->Empty())){
      NodeLnk* s = FindPointerToSuccessor(root, nullptr, d);
      if(s!=nullptr) Remove(s->x);
      else throw std::length_error("BST: Doesn't exist a successor, max of the tree is less-equal than the element you searched successor of.");     // when d >= max(bst)
    }
    else throw std::length_error("BST: The tree is empty!");
  }

  template <typename Data>
  bool BST<Data>::Exists(const Data& d) const noexcept{
    return (FindPointerTo(root, d) != nullptr);
  }


  /* PROTECTED FUNCTIONS */

  // Function used by all the other remove functions of the form  " *NRemove ".
  template <typename Data>
  Data BST<Data>::DataNDelete(NodeLnk* n){
    Data d {};
    if(n!=nullptr){
      d = n->x;
      Remove(d);
    }
    return d;
  }

  // Detach is the function that really evaluate the deleting cases (has left, has right, has neither, has both...).
  template <typename Data>
  typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& n){
    if(n!=nullptr){
      if(!(n->HasLeftChild()) || !(n->HasRightChild())){
        if(n->HasLeftChild()) return SkipOnLeft(n);
        else return SkipOnRight(n);
      }
      else{
        NodeLnk* tmp = DetachMin(n->right);
        std::swap(n->x, tmp->x);
        return tmp;
      }
    }
    return nullptr;
  }

  // Detaches the min node, than returns it.
  template <typename Data>
  typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& n){
    return SkipOnRight(FindPointerToMin(n));
  }

  // "Skips" the node received, then returns the node "skipped".
  template <typename Data>
  typename BST<Data>::NodeLnk* BST<Data>::SkipOnLeft(NodeLnk*& n){
    NodeLnk* tmp = nullptr;
    if(n!=nullptr){
      std::swap(tmp, n->left);
      std::swap(tmp, n);
    }
    return tmp;
  }

  // "Skips" the node received, then returns the node "skipped".
  template <typename Data>
  typename BST<Data>::NodeLnk* BST<Data>::SkipOnRight(NodeLnk*& n){
    NodeLnk* tmp = nullptr;
    if(n!=nullptr){
      std::swap(tmp, n->right);
      std::swap(tmp, n);
    }
    return tmp;
  }

  // Const return type.
  template <typename Data>
  typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerTo(NodeLnk* const & t, const Data& d) const{
    NodeLnk* const & tmp = t;
    if(tmp!=nullptr){
      if(tmp->x > d) return FindPointerTo(tmp->left, d);
      else{
        if(tmp->x < d) return FindPointerTo(tmp->right, d);
        return tmp;
      }
    }
    return tmp;
  }

  // Non-const return type.
  template <typename Data>
  typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& t, const Data& d){
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(t, d));   // Convert to BST<Data>* the value returned by FindPointerTo, then convert to NodeLnk*&.
  }

  // Const return type for Min.
  template <typename Data>
  typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToMin(NodeLnk* const & t) const{
    NodeLnk* const* ret = &t;       // Pointer to a const pointer to a NodeLnk!
    NodeLnk* tmp = t;
    if(tmp!=nullptr){
      while(tmp->HasLeftChild()){
        ret = &tmp->left;
        tmp = tmp->left;
      }
    }
    return *ret;
  }

  // Non-const return type for Min.
  template <typename Data>
  typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& t){
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(t));
  }

  // Const return type for Max.
  template <typename Data>
  typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToMax(NodeLnk* const & t) const{
    NodeLnk* const* ret = &t;       // Pointer to a const pointer to a NodeLnk!
    NodeLnk* tmp = t;
    if(tmp!=nullptr){
      while(tmp->HasRightChild()){
        ret = &tmp->right;
        tmp = tmp->right;
      }
    }
    return *ret;
  }

  // Non-const return type for Max.
  template <typename Data>
  typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& t){
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(t));
  }

  template <typename Data>
  typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToPredecessor(NodeLnk* const & n, NodeLnk* const & c, const Data& d) const{
    if(n!=nullptr){
      if(n->x == d){
        if(n->HasLeftChild()) return FindPointerToMax(n->left);
      }
      else{
        if(n->x > d) return FindPointerToPredecessor(n->left, c, d);
        else return FindPointerToPredecessor(n->right, n, d);
      }
    }
    return c;     // will be returned c==nullptr if d <= min(bst), this will trigger an exception thrown in functions: Predecessor, PredecessorNRemove, RemovePredecessor.
  }

  template <typename Data>
  typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToSuccessor(NodeLnk* const & n, NodeLnk* const & c, const Data& d) const{
    if(n!=nullptr){
      if(n->x == d){
        if(n->HasRightChild()) return FindPointerToMin(n->right);
      }
      else{
        if(n->x < d) return FindPointerToSuccessor(n->right, c, d);
        else return FindPointerToSuccessor(n->left, n, d);
      }
    }
    return c;     // will be returned c==nullptr if d >= max(bst), this will trigger an exception thrown in functions: Successor, SuccessorNRemove, RemoveSuccessor.
  }


/*
  template <typename Data>
  typename BST<Data>::NodeLnk* BST<Data>::SortedCostr(LinearContainer<Data>& c, long p, long r){
    if(p < r){
      long q = ((p+r)/2);
      NodeLnk* tmp = new NodeLnk(c[q]);
      tmp->left = SortedCostr(c, p, q);
      tmp->right = SortedCostr(c, q+1, r);
      return tmp;
    }
    else{
      return nullptr;
    }
  }

  template <typename Data>
  void BST<Data>::QuickSort(LinearContainer<Data>& c, ulong p, ulong r){
    ulong q = 0;
    if(p < r){
      q = Partiziona(c, p, r);
      QuickSort(c, p, q);
      QuickSort(c, q+1, r);
    }
  }

  template <typename Data>
  ulong BST<Data>::Partiziona(LinearContainer<Data>& c, ulong p, ulong r){
    ulong i = p - 1;
  	ulong j = r + 1;
  	ulong x = c[p];
  	do {
  		do {
  			i = i + 1;
  		} while(c[i] < x);
  		do {
  			j = j - 1;
  		} while(c[j] > x);
  		if (i < j) {
  			Swap(c, i, j);
  		}
  	} while(i < j);
  	return j;
  }

  template <typename Data>
  void BST<Data>::Swap(LinearContainer<Data>& c, ulong i, ulong j){
    Data tmp = c[i];
    c[i] = c[j];
    c[j] = tmp;
  }
*/

}
