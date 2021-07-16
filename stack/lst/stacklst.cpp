
namespace lasd {

  // Destructor.
  template <typename Data>
  StackLst<Data>::~StackLst(){
    Clear();
  }

  // Copy assignment.
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& sl){
    List<Data>::operator=(sl);
    return *this;
  }

  // Move assignment.
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& sl) noexcept{
    List<Data>::operator=(std::move(sl));
    return *this;
  }

  // Comparison operators.
  template <typename Data>
  bool StackLst<Data>::operator==(const StackLst& sl) const noexcept{
    return List<Data>::operator==(sl);
  }

  template <typename Data>
  bool StackLst<Data>::operator!=(const StackLst& sl) const noexcept{
    return List<Data>::operator!=(sl);
  }

  // Specific member functions (inherited from Stack).
  template <typename Data>
  void StackLst<Data>::Push(const Data& x){
    List<Data>::InsertAtFront(x);
  }

  template <typename Data>
  void StackLst<Data>::Push(Data&& x){
    List<Data>::InsertAtFront(std::move(x));
  }

  template <typename Data>
  Data& StackLst<Data>::Top() const{
    return List<Data>::Front();
  }

  template <typename Data>
  void StackLst<Data>::Pop(){
    List<Data>::RemoveFromFront();
  }

  template <typename Data>
  Data StackLst<Data>::TopNPop(){
    return List<Data>::FrontNRemove();
  }

  // Specific member functions (inherited from Container).
  template <typename Data>
  void StackLst<Data>::Clear(){
    List<Data>::Clear();
  }

}
