namespace lasd {

  // Node.

  // Needed to compare 2 trees...
  template <typename Data>
  bool BinaryTree<Data>::Node::operator==(const Node& n) const noexcept{
    if(Element()==n.Element()){
      if(HasLeftChild() && n.HasLeftChild()){
        if(HasRightChild() && n.HasRightChild()){
          return (LeftChild()==n.LeftChild() && RightChild()==n.RightChild());
        }
        if(!(HasRightChild()) && !(n.HasRightChild())) return LeftChild()==n.LeftChild();
        else return false;
      }
      if(!(HasLeftChild()) && !(n.HasLeftChild())){
        if(HasRightChild() && n.HasRightChild()) return RightChild()==n.RightChild();
        else{
          if(!(HasRightChild()) && !(n.HasRightChild())) return true;
          else return false;
        }
      }
      else return false;
    }
    return false;
  }

  template <typename Data>
  bool BinaryTree<Data>::Node::operator!=(const Node& n) const noexcept{
    return !(*(this)==n);
  }

  template <typename Data>
  bool BinaryTree<Data>::Node::IsLeaf() noexcept{
    if ( !(HasLeftChild()) && !(HasRightChild()) ) return true;
    return false;
  }



  // BinaryTree.
  // We can implement BinaryTree Member Functions despite BinaryTree is an abstract class thanks to the functions RightChild, LeftChild ect...

  // Sematics: check if the two roots are equal, so the functionality is completely demanded to node1==node2.
  template <typename Data>
  bool BinaryTree<Data>::operator==(const BinaryTree& bt) const noexcept{
    if(this->Empty() && bt.Empty()) return true;
    else{
      if(!(this->Empty()) && !(bt.Empty())) return (Root()==bt.Root());
      else return false;
    }
  }

  template <typename Data>
  bool BinaryTree<Data>::operator!=(const BinaryTree& bt) const noexcept{
    return !(*this==bt);
  }

  template <typename Data>
  void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par){
    if(!(this->Empty())) MapPreOrder(fun, par, &Root());
  }

  // Auxiliary.
  template <typename Data>
  void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par, Node* n){
    fun(n->Element(), par);
    if(n->HasLeftChild()) MapPreOrder(fun, par, &(n->LeftChild()));
    if(n->HasRightChild()) MapPreOrder(fun, par, &(n->RightChild()));
  }

  template <typename Data>
  void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par){
    if(!(this->Empty())) MapPostOrder(fun, par, &Root());
  }

  // Auxiliary.
  template <typename Data>
  void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par, Node* n){
    if(n->HasLeftChild()) MapPostOrder(fun, par, &(n->LeftChild()));
    if(n->HasRightChild()) MapPostOrder(fun, par, &(n->RightChild()));
    fun(n->Element(), par);
  }

  template <typename Data>
  void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par){
    if(!(this->Empty())) MapInOrder(fun, par, &Root());
  }

  // Auxiliary.
  template <typename Data>
  void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par, Node* n){
    if(n->HasLeftChild()) MapInOrder(fun, par, &(n->LeftChild()));
    fun(n->Element(), par);
    if(n->HasRightChild()) MapInOrder(fun, par, &(n->RightChild()));
  }

  template <typename Data>
  void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par){
    if(!(this->Empty())) MapBreadth(fun, par, &Root());
  }

  // Auxiliary.
  template <typename Data>
  void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par, Node* n){
    lasd::QueueLst<Node*> ql{};
    ql.Enqueue(n);
    while(!(ql.Empty())){
      Data x = ql.Head()->Element();
      fun(x, par);
      if(ql.Head()->HasLeftChild()) ql.Enqueue(&(ql.Head()->LeftChild()));
      if(ql.Head()->HasRightChild()) ql.Enqueue(&(ql.Head()->RightChild()));
      ql.Dequeue();
    }
  }

  template <typename Data>
  void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
    if(!(this->Empty())) FoldPreOrder(fun, par, acc, &Root());
  }

  // Auxiliary.
  template <typename Data>
  void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node* n) const{
    fun(n->Element(), par, acc);
    if(n->HasLeftChild()) FoldPreOrder(fun, par, acc, &(n->LeftChild()));
    if(n->HasRightChild()) FoldPreOrder(fun, par, acc, &(n->RightChild()));
  }

  template <typename Data>
  void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    if(!(this->Empty())) FoldPostOrder(fun, par, acc, &Root());
  }

  // Auxiliary.
  template <typename Data>
  void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node* n) const{
    if(n->HasLeftChild()) FoldPostOrder(fun, par, acc, &(n->LeftChild()));
    if(n->HasRightChild()) FoldPostOrder(fun, par, acc, &(n->RightChild()));
    fun(n->Element(), par, acc);
  }

  template <typename Data>
  void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc) const{
    if(!(this->Empty())) FoldInOrder(fun, par, acc, &Root());
  }

  // Auxiliary.
  template <typename Data>
  void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc, Node* n) const{
    if(n->HasLeftChild()) FoldInOrder(fun, par, acc, &(n->LeftChild()));
    fun(n->Element(), par, acc);
    if(n->HasRightChild()) FoldInOrder(fun, par, acc, &(n->RightChild()));
  }

  template <typename Data>
  void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const{
    if(!(this->Empty())) FoldBreadth(fun, par, acc, &Root());
  }

  // Auxiliary.
  template <typename Data>
  void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc, Node* n) const{
    lasd::QueueLst<Node*> ql{};
    ql.Enqueue(n);
    while(!(ql.Empty())){
      Data x = ql.Head()->Element();
      fun(x, par, acc);
      if(ql.Head()->HasLeftChild()) ql.Enqueue(&(ql.Head()->LeftChild()));
      if(ql.Head()->HasRightChild()) ql.Enqueue(&(ql.Head()->RightChild()));
      ql.Dequeue();
    }
  }



  // BTPreOrderIterator.


  // Specific constructor.
  /*Avremo tre momenti in cui lo stack sarà vuoto: quando chiamiamo il costruttore, quando abbiamo visitato tutto il sottoalbero sx, quando abbiamo terminato.*/
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt){
    if(!(bt.Empty())) pn = &bt.Root();
  }

  // Copy constructor.
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& it){
    pn = it.pn;
    sl = it.sl;
  }

  // Copy assignment.
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& it){
    pn = it.pn;
    sl = it.sl;
    return *this;
  }

  // Move constructor.
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& it) noexcept{
    std::swap(pn, it.pn);
    std::swap(sl, it.sl);
  }

  // Move assignment.
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& it) noexcept{
    std::swap(pn, it.pn);
    std::swap(sl, it.sl);
    return *this;
  }

  // Comparison operators.
  template <typename Data>
  bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& it) const noexcept{
    if(Terminated() && it.Terminated()) return true;
    if(!(Terminated()) && !(it.Terminated())){
      if(*(*this)==*it && sl==it.sl) return true;
      else return false;
    }
    return false;
  }

  template <typename Data>
  bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& it) const noexcept{
    return (!(*this==it));
  }

  template <typename Data>
  Data& BTPreOrderIterator<Data>::operator*() const{
    if(!(Terminated())) return pn->Element();
    else throw std::out_of_range("You reached the end of the tree! *exc.");
  }

  template <typename Data>
  bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    return (pn==nullptr && sl.Empty());
  }

  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++(){
    if(!(Terminated())){
      if(pn->HasRightChild()) sl.Push(&(pn->RightChild()));       // E' NECESSARIO effettuare prima il controllo sulla destra...
      if(pn->HasLeftChild()) pn = &(pn->LeftChild());
      else{
        if(!(sl.Empty())) pn = sl.TopNPop();
        else pn = nullptr;
      }
      return *this;
    }
    throw std::out_of_range("You reached the end of the tree! ++exc.");
  }



  // BTBreadthIterator.

  // Specific costructor.
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt){
    if(!(bt.Empty())) pn = &bt.Root();
  }

  // Copy costructor.
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator& it){
    pn = it.pn;
    ql = it.ql;
  }

  // Copy assignment.
  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& it){
    pn = it.pn;
    ql = it.ql;
    return *this;
  }

  // Move constructor.
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& it) noexcept{
    std::swap(pn, it.pn);
    std::swap(ql, it.ql);
  }

  // Move assignment.
  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& it) noexcept{
    std::swap(pn, it.pn);
    std::swap(ql, it.ql);
    return *this;
  }

  template <typename Data>
  bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& it) const noexcept{
    if(Terminated() && it.Terminated()) return true;
    if(!(Terminated()) && !(it.Terminated())){
      if(*(*this)==*it && ql==it.ql) return true;
      else return false;
    }
    return false;
  }

  template <typename Data>
  bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& it) const noexcept{
    return (!(*(this)==it));
  }

  template <typename Data>
  Data& BTBreadthIterator<Data>::operator*() const{
    if(!(Terminated())) return pn->Element();
    else throw std::out_of_range("You reached the end of the tree! *exc.");
  }

  template <typename Data>
  bool BTBreadthIterator<Data>::Terminated() const noexcept{
    return (pn==nullptr && ql.Empty());
  }

  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++(){
    if(!(Terminated())){
      if(pn->HasLeftChild()) ql.Enqueue(&(pn->LeftChild()));
      if(pn->HasRightChild()) ql.Enqueue(&(pn->RightChild()));
      if(!(ql.Empty())) pn = ql.HeadNDequeue();
      else pn = nullptr;
      return *this;
    }
    throw std::out_of_range("You reached the end of the tree! ++exc.");
  }



  // BTInOrderIterator.

  // Specific costructor.
  /* A differenza dei costruttori di iteratori Pre e Breadth, qui, come per l'iteratore Post, già inizializziamo lo stack (con LeftMostNode()).
  Infatti, avremo, a differenza dell'iteratore PreOrder/PostOrder, due (e non tre/uno) momenti in cui lo stack sarà vuoto, quando abbiamo visitato il sottoalbero sx della radice, e quando abbiamo terminato*/
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt){
    if(!(bt.Empty())) pn = LeftMostNode(&(bt.Root()));
  }

  // Copy costructor.
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& it){
    pn = it.pn;
    sl = it.sl;
  }

  // Copy assignment.
  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& it){
    pn = it.pn;
    sl = it.sl;
    return *this;
  }

  // Move constructor.
  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& it) noexcept{
    std::swap(pn, it.pn);
    std::swap(sl, it.sl);
  }

  // Move assignment.
  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& it) noexcept{
    std::swap(pn, it.pn);
    std::swap(sl, it.sl);
    return *this;
  }

  template <typename Data>
  bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& it) const noexcept{
    if(Terminated() && it.Terminated()) return true;
    if(!(Terminated()) && !(it.Terminated())){
      if(*(*this)==*it && sl==it.sl) return true;
      else return false;
    }
    return false;
  }

  template <typename Data>
  bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& it) const noexcept{
    return (!(*(this)==it));
  }

  template <typename Data>
  Data& BTInOrderIterator<Data>::operator*() const{
    if(!(Terminated())) return pn->Element();
    else throw std::out_of_range("You reached the end of the tree! *exc.");
  }

  template <typename Data>
  bool BTInOrderIterator<Data>::Terminated() const noexcept{
    return (pn==nullptr && sl.Empty());
  }

  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++(){
    if(!(Terminated())){
      if(pn->HasRightChild()) pn = LeftMostNode(&(pn->RightChild()));
      else{
        if(!(sl.Empty())) pn = sl.TopNPop();
        else pn = nullptr;
      }
      return *this;
    }
    throw std::out_of_range("You reached the end of the tree! ++exc.");
  }

  // Auxiliary functions.
  template <typename Data>
  typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::LeftMostNode(typename BinaryTree<Data>::Node* n) noexcept{
    if(n->HasLeftChild()){
      sl.Push(n);
      return LeftMostNode(&(n->LeftChild()));
    }
    return n;
  }



  // BTPostOrderIterator.

  // Specific costructor.
  /* A differenza degli altri iteratori, qui già inizializzo lo stack (con LeftMostLeaf()).
  Infatti, a differenza dell'iteratore Inorder (2) e dell'iteratore PreOrder (3), qui ci sarà solo un momento in cui lo stack sarà vuoto: quando l'iteratore è terminato.*/
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt){
    if(!(bt.Empty())) pn = LeftMostLeaf(&(bt.Root()));
  }

  // Copy costructor.
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& it){
    pn = it.pn;
    sl = it.sl;
  }

  // Copy assignment.
  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& it){
    pn = it.pn;
    sl = it.sl;
    return *this;
  }

  // Move constructor.
  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& it) noexcept{
    std::swap(pn, it.pn);
    std::swap(sl, it.sl);
  }

  // Move assignment.
  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& it) noexcept{
    std::swap(pn, it.pn);
    std::swap(sl, it.sl);
    return *this;
  }

  template <typename Data>
  bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& it) const noexcept{
    if(Terminated() && it.Terminated()) return true;
    if(!(Terminated()) && !(it.Terminated())){
      if(*(*this)==*it && sl==it.sl) return true;
      else return false;
    }
    return false;
  }

  template <typename Data>
  bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& it) const noexcept{
    return (!(*(this)==it));
  }

  template <typename Data>
  Data& BTPostOrderIterator<Data>::operator*() const{
    if(!(Terminated())) return pn->Element();
    else throw std::out_of_range("You reached the end of the tree! *exc.");
  }

  template <typename Data>
  bool BTPostOrderIterator<Data>::Terminated() const noexcept{
    return (pn==nullptr && sl.Empty());
  }

  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){
    if(!(Terminated())){
      if(!(sl.Empty())){
        if(sl.Top()->HasLeftChild()){
          if((&(sl.Top()->LeftChild())==pn) && (sl.Top()->HasRightChild())) pn = LeftMostLeaf(&(sl.Top()->RightChild()));
          else pn = sl.TopNPop();
        }
        else{
          pn = sl.TopNPop();
          /* I controlli di chiedersi se il top dello stack ha destro, e se il destro sono proprio io, sono inutili.
          Il primo perchè se lo stack è diverso dal vuoto, il top ha per forza o un dx o un sx ...
          ... il secondo perchè vengo sempre dal figlio di destra se sono qui... */
        }
      }
      else{
        pn = nullptr;
      }
      return *this;
    }
    throw std::out_of_range("You reached the end of the tree! ++exc.");
  }

  // Auxiliary functions.
  template <typename Data>
  typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::LeftMostLeaf(typename BinaryTree<Data>::Node* n) noexcept{
    if(n->HasLeftChild()){
      sl.Push(n);
      return LeftMostLeaf(&(n->LeftChild()));
    }
    else{
      if(n->HasRightChild()){
        sl.Push(n);
        return LeftMostLeaf(&(n->RightChild()));
      }
      else return n;
    }
  }

}
