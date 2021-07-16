
namespace lasd {

  // Destructor.
  template <typename Data>
  QueueLst<Data>::~QueueLst(){
    Clear();
  }

  // Copy assignment.
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& ql){
    List<Data>::operator=(ql);
    return *this;
  }

  // Move assignment.
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& ql) noexcept{
    List<Data>::operator=(ql);
    return *this;
  }

  // Specific member functions (inherited from Queue).
  template <typename Data>
  void QueueLst<Data>::Enqueue(const Data& x){
    List<Data>::InsertAtBack(x);
  }

  template <typename Data>
  void QueueLst<Data>::Enqueue(Data&& x){
    List<Data>::InsertAtBack(x);
  }

  template <typename Data>
  Data& QueueLst<Data>::Head() const{
    return List<Data>::Front();
  }

  template <typename Data>
  void QueueLst<Data>::Dequeue(){
    List<Data>::RemoveFromFront();
  }

  template <typename Data>
  Data QueueLst<Data>::HeadNDequeue(){
    return List<Data>::FrontNRemove();
  }


  // Comparison operators.
  template <typename Data>
  bool QueueLst<Data>::operator==(const QueueLst& ql) const noexcept{
    return List<Data>::operator==(ql);
  }

  template <typename Data>
  bool QueueLst<Data>::operator!=(const QueueLst& ql) const noexcept{
    return List<Data>::operator!=(ql);
  }

  // Specific member functions (inherited from Container).
  template <typename Data>
  void QueueLst<Data>::Clear(){
    List<Data>::Clear();
  }

}
