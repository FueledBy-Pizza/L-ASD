
namespace lasd {

   // A stack obtained from a LinearContainer.
  template <typename Data>
  StackVec<Data>::StackVec(const LinearContainer<Data>& c){
    int x = c.Size();
    while(x%4!=0) x++;                    // We want to mantain the solid property of the structure that will have just a power-of-two size, greater or equal to 4.
    size = x;
    Elements = new Data[size];
    for(ulong i = 0; i < c.Size(); i++){
      Elements[i] = c[i];
    }
    if(c.Size()>size-2) Expand();         // We anyway got to expand the stack if the conditions allow it...
    sentinel = c.Size();
  };

  // Destructor.
  template <typename Data>
  StackVec<Data>::~StackVec(){
    Clear();
  }

  // Copy assignment.
  template <typename Data>
  StackVec<Data>& StackVec<Data>::operator=(const StackVec& sv){
    sentinel = sv.sentinel;
    Vector<Data>::operator=(sv);
    return *this;
  }

  // Move  assignment.
  template <typename Data>
  StackVec<Data>& StackVec<Data>::operator=(StackVec&& sv){
    std::swap(sentinel, sv.sentinel);
    Vector<Data>::operator=(std::move(sv));
    return *this;
  }

  // Comparison operators.
  template <typename Data>
  bool StackVec<Data>::operator==(const StackVec& sv) const noexcept{
    return Vector<Data>::operator==(sv);
  }

  template <typename Data>
  bool StackVec<Data>::operator!=(const StackVec& sv) const noexcept{
    return Vector<Data>::operator!=(sv);
  }

  // Specific member functions (inherited from Stack).
  template <typename Data>
  void StackVec<Data>::Push(const Data& d){
    if(sentinel!=size-2) Elements[sentinel] = d;
    else{
      Expand();
      Elements[sentinel] = d;
    }
    sentinel++;
  }

  template <typename Data>
  void StackVec<Data>::Push(Data&& d){
    if(sentinel!=size-2) Elements[sentinel] = d;
    else{
      Expand();
      Elements[sentinel] = d;
    }
    sentinel++;
  }

  template <typename Data>
  Data& StackVec<Data>::Top() const{
    if(sentinel!=0) return Elements[sentinel-1];
    else throw std::length_error("The stack is empty!");
  }

  template <typename Data>
  void StackVec<Data>::Pop(){
    if(sentinel!=0){
      sentinel--;
      if(size!=4 && sentinel==(size/4)) Reduce();
    }
    else throw std::length_error("The stack is empty!");
  }

  template <typename Data>
  Data StackVec<Data>::TopNPop(){
    if(sentinel!=0){
      sentinel--;
      if(size!=4 && sentinel==(size/4)) Reduce();
      return Elements[sentinel];
    }
    else throw std::length_error("The stack is empty!");
  }

  template <typename Data>
  inline bool StackVec<Data>::Empty() const noexcept{
    return (sentinel==0);
  }

  template <typename Data>
  inline ulong StackVec<Data>::Size() const noexcept{
    return sentinel;
  }

  template <typename Data>
  void StackVec<Data>::Clear(){
    Vector<Data>::Clear();
    sentinel = 0;
  }

  template <typename Data>
  void StackVec<Data>::Expand(){
    Vector<Data>::Resize(size*2);
  }

  template <typename Data>
  void StackVec<Data>::Reduce(){
    Vector<Data>::Resize(size/2);
  }

}
