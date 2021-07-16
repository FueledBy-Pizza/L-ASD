
namespace lasd {

  // Node.

  // Specific constructor, used by list constructor given a linear container, and by Inserts.
  template <typename Data>
  List<Data>::Node::Node(const Data& d){
    this->x = d;
    this->next = nullptr;
  }

  // Copy constructor, used by List copy constructor, in order to have a cascade behaviour.
  template <typename Data>
  List<Data>::Node::Node(const Node& n){
    x = n.x;
    next = nullptr;
    if(n.next!=nullptr){
      next = new Node(*(n.next));
    }
  }


  // List.

  // Specific constructor with a given linear container, uses Node specific constructor.
  template <typename Data>
  List<Data>::List(const LinearContainer<Data>& c){
    size = c.Size();
    Node* l = new Node(c[0]);
    Node* tmp = l;
    for(ulong i=1; i<size; i++){
      Node* temp = new Node(c[i]);
      tmp->next = temp;
      tmp = tmp->next;
    }
    top = l;
    tail = tmp; //tail = temp
  }

  // Copy constructor, uses Node copy constructor.
  template <typename Data>
  List<Data>::List(const List& l){
    size = l.Size();
    top = nullptr;
    tail = nullptr;
    Node* tmp = nullptr;
    if(l.top!=nullptr){
      tmp = new Node(*(l.top));       // This will trigger a cascade nodes construction...
      top = tmp;
      while(tmp->next!=nullptr){      // Cycling through the list to find the tail.
        tmp = tmp->next;
      }
      tail = tmp;
    }
  }

  // Move constructor.
  template <typename Data>
  List<Data>::List(List&& l) noexcept{
    std::swap(size, l.size);
    std::swap(tail, l.tail);
    std::swap(top, l.top);
  }

  // Destructor.
  template <typename Data>
  List<Data>::~List(){
    Clear();
  }

  // Copy assignment.
  template <typename Data>
  List<Data>& List<Data>::operator=(const List<Data>& l){
    size = l.Size();
    top = nullptr;
    tail = nullptr;
    Node* tmp = nullptr;
    if(l.top!=nullptr){
      tmp = new Node(*(l.top));
      top = tmp;
      while(tmp->next!=nullptr){
        tmp = tmp->next;
      }
      tail = tmp;
    }
    return *this;
  }

  // Move assignment.
  template <typename Data>
  List<Data>& List<Data>::operator=(List<Data>&& l) noexcept{
    std::swap(size, l.size);
    std::swap(tail, l.tail);
    std::swap(top, l.top);
    return *this;
  }

  // Comparison operators.
  template <typename Data>
  bool List<Data>::operator==(const List& l) const noexcept{
    if(size!=l.size) return false;
    if(top==nullptr) return true;       // Qui già posso ritornare true, ho appena saputo che le due size sono uguali, quindi le due size saranno entrambe zero.
    Node* tmp1 = top;                   // Altrimenti mi posiziono sulle due liste ...
    Node* tmp2 = l.top;
    ulong i = 0;
    while (i < size){                   // ... e verifico l'uguaglianza dei dati.
      if(tmp1->x != tmp2->x) return false;
      tmp1 = tmp1->next;
      tmp2 = tmp2->next;
      ++i;
    }
    return true;
  }

  template <typename Data>
  bool List<Data>::operator!=(const List& l) const noexcept{
    return !(*(this)==l);
  }

  // Specific member functions.
  template <typename Data>
  void List<Data>::InsertAtFront(const Data& d){
    size++;
    Node* l = new Node(d);
    if(size==1){
      top = l;
      tail = top;
    }
    else{
      l->next = top;
      top = l;
    }
  }

  template <typename Data>
  void List<Data>::InsertAtFront(Data&& d){
    size++;
    Node* l = new Node(d);
    if(size==1){
      top = l;
      tail = top;
    }
    else{
      l->next = top;
      top = l;
    }
  }

  template <typename Data>
  void List<Data>::RemoveFromFront(){
    if(size!=0){
      Node* tmp = top;
      top = top->next;
      delete tmp;
      size--;
    }
    else throw std::length_error("List is empty!");
  }

  template <typename Data>
  Data List<Data>::FrontNRemove(){
    if(size!=0){
      Data x = Front();
      Node* tmp = top;
      top = top->next;
      delete tmp;
      size--;        // Necessario metterlo qui, e non prima della chiamata a Front()...
      return x;
    }
    else throw std::length_error("List is empty!");
  }

  template <typename Data>
  void List<Data>::InsertAtBack(const Data& d){
    size++;
    Node* l = new Node(d);
    if(size==1){
      top = l;
      tail = l;
    }
    else{
      tail->next = l;
      tail = tail->next;
    }
  }

  template <typename Data>
  void List<Data>::InsertAtBack(Data&& d){
    size++;
    Node* l = new Node(d);
    if(size==1){
      tail = l;
      top = tail;
    }
    else{
      tail->next = l;
      this->tail = l;
    }
  }

  // Specific member functions (inherited from Container).
  template <typename Data>
  void List<Data>::Clear(){
    size = 0;
    Node* tmp = top;
    while(tmp!=nullptr){
      tmp = tmp->next;
      delete top;
      top = tmp;
    }
    top = nullptr;
    tail = nullptr;
  }

  // Specific member functions (inherited from LinearContainer).
  template <typename Data>
  Data& List<Data>::Front() const{
    if(size != 0) return top->x;
    else throw std::length_error("List is empty!");
  }

  template <typename Data>
  Data& List<Data>::Back() const{
    if(size!=0) return tail->x;
    else throw std::length_error("List is empty!");
  }

  template <typename Data>
  Data& lasd::List<Data>::operator[](const ulong i) const{
    ulong j = 0;
    if(i <= size){
      Node* tmp = top;
      for(j = 0; j < i; j++){
        tmp = tmp->next;
      }
      return tmp->x;
    }
    else{
      throw std::out_of_range("Cannot access to the element n. " + std::to_string(i) + " in a " + std::to_string(size) + "-sized list!");
    }
  }

  // Specific member functions (inherited from MappableContainer and Foldable Container).
  template <typename Data>
  void List<Data>::MapPreOrder(const MapFunctor fun, void* par){  // Calls Auxiliary MapPreOrder.
    MapPreOrder(fun, par, top);
  }

  // Auxiliary MapPreOrder.
  // Recursive...
  template <typename Data>
  void List<Data>::MapPreOrder(const MapFunctor fun, void* par, Node* t){
    Node* tmp = t;
    if(tmp!=nullptr){
      fun(tmp->x, par);
      MapPreOrder(fun, par, tmp->next);
    }
  }

  template <typename Data>
  void List<Data>::MapPostOrder(const MapFunctor fun, void* par){   // Calls Auxiliary MapPostOrder.
    MapPostOrder(fun, par, top);
  }

  // Auxiliary MapPostOrder.
  // Recursive...
  template <typename Data>
  void List<Data>::MapPostOrder(const MapFunctor fun, void* par, Node* t){
    Node* tmp = t;
    if(tmp!=nullptr){
      MapPostOrder(fun, par, tmp->next);
      fun(tmp->x, par);
    }
  }

  template <typename Data>
  void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{  // Calls Auxiliary FoldPreOrder.
    FoldPreOrder(fun, par, acc, top);
  }

  // Auxiliary FoldPreOrder.
  // Recursive...
  template <typename Data>
  void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node* t) const{
    Node* tmp = t;
    if(tmp!=nullptr){
      fun(tmp->x, par, acc);
      FoldPreOrder(fun, par, acc, tmp->next);
    }
  }

  template <typename Data>
  void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{  // Calls Auxiliary FoldPostOrder.
    FoldPostOrder(fun, par, acc, top);
  }

  // Auxiliary FoldPostOrder.
  // Recursive...
  template <typename Data>
  void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node* t) const{
    Node* tmp = t;
    if(tmp!=nullptr){
      FoldPostOrder(fun, par, acc, tmp->next);
      fun(tmp->x, par, acc);
    }
  }

}
