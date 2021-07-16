
namespace lasd {

  // All the costructor initialize QueueVec Elements starting from index 0
  // container.Size() -different behaviour from QueueVec.Size()- will be our tail, indipendently from how many concrete or (just) initialized elements container has.
  /* e.g.: Vector size: 10 elements, 5 inserted and the others 5 initialized by Vector constructor
           QueueVec.head will be 0, QueueVec.tail will be 10 as QueueVec.Size() (and QueueVec.size will be 16).*/

  template <typename Data>
  QueueVec<Data>::QueueVec(const LinearContainer<Data>& c){     // We want that the QueueVec.size will be a (greater or equal to 4) power of 2, that is, we want to mantain its structure design for future operations (for how we designed QueueVec, it always has a power-of-two size).
    head = 0;                                 // We want to start filling the queue since index 0.
    ulong x = c.Size();
    tail = c.Size();
    if(x<=2){                                 // If we have a number of elements less or equal to two, we can build a base QueueVec (size=4).
      size = 4;
      Elements = new Data[4] {};
    }
    else{
      while((x & (x-1)) != 0) x++;            // Incrementing x till it's a power of two to "discover" what size QueueVec must have...
      size = x;
      Elements = new Data[x] {};
    }
    for(ulong i = 0; i < tail; i++){          // Copying the elements.
      Elements[i] = c[i];
    }
    if(size==c.Size()-1) Expand();            // We anyway got to expand the structure if the conditions allow it...
  }

  // Copy constructor.
  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec<Data>& qv){
    Elements = new Data[qv.size];
    size = qv.size;
    head = 0;
    tail = 0;
    if(qv.tail != qv.head){
      if(qv.tail > qv.head) tail = qv.tail - qv.head;
      else{
        tail = qv.head - qv.tail;
        tail = qv.size - tail;
      }
    }
    ulong j = qv.head;
    for(ulong i=0; i < tail; i++){
      Elements[i] = qv.Elements[j];
      qv.IncrementQueueIndex(j);
    }
  }

  // Move constructor.
  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec<Data>&& qv){
    Elements = new Data[qv.size];
    size = qv.size;
    head = 0;
    tail = 0;
    if(qv.tail != qv.head){
      if(qv.tail > qv.head) tail = qv.tail - qv.head;
      else{
        tail = qv.head - qv.tail;
        tail = qv.size - tail;
      }
    }
    ulong j = qv.head;
    for(ulong i=0; i < tail; i++){
      std::swap(Elements[i], qv.Elements[j]);    // Elements[i] = qv.Elements[j];
      qv.IncrementQueueIndex(j);
    }
    qv.head = 0;                                 // Setting the old queue to a default state.
    qv.tail = 0;
    qv.size = 4;
  }

  // Copy assignment.
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qv){
    Elements = new Data[qv.size];
    size = qv.size;
    head = 0;
    tail = 0;
    if(qv.tail != qv.head){
      if(qv.tail > qv.head) tail = qv.tail - qv.head;
      else{
        tail = qv.head - qv.tail;
        tail = qv.size - tail;
      }
    }
    ulong j = qv.head;
    for(ulong i=0; i < tail; i++){
      Elements[i] = qv.Elements[j];
      qv.IncrementQueueIndex(j);
    }
    return *this;
  }

  // Move assignment.
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qv){
    Elements = new Data[qv.size];
    size = qv.size;
    head = 0;
    tail = 0;
    if(qv.tail != qv.head){
      if(qv.tail > qv.head) tail = qv.tail - qv.head;
      else{
        tail = qv.head - qv.tail;
        tail = qv.size - tail;
      }
    }
    ulong j = qv.head;
    for(ulong i=0; i < tail; i++){
      std::swap(Elements[i], qv.Elements[j]);    // Elements[i] = qv.Elements[j];
      qv.IncrementQueueIndex(j);
    }
    qv.head = 0;                                 // Setting the old queue to a default state.
    qv.tail = 0;
    qv.size = 4;
    return *this;
  }

  template <typename Data>
  bool QueueVec<Data>::operator==(const QueueVec<Data>& qv) const noexcept{
    if(Size()==qv.Size()){                // To compare, we have to consider the concrete elements existing in the queues, thus Size() and not size!!
      ulong fixedsize = Size();           // Max n elements I can compare (if they will all be equal).
      ulong i = 0;
      ulong scan1 = head;
      ulong scan2 = qv.head;
      while(i < fixedsize && Elements[scan1]==qv.Elements[scan2]){
        IncrementQueueIndex(scan1);
        IncrementQueueIndex(scan2);
        i++;
      }
      if(i==fixedsize) return true;       // After looping, if i compared all the elements, it means they were all equal.
      else return false;
    }
    else return false;
  }

  template <typename Data>
  bool QueueVec<Data>::operator!=(const QueueVec<Data>& qv) const noexcept{
    return !(*(this)==qv);
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(const Data& d){
    Elements[tail] = d;
    IncrementQueueIndex(tail);
    if(Size()==size-1) Expand();                  // We expand the queue if we inserted the (QueueVec.size-1)th element.
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(Data&& d){
    Elements[tail] = std::move(d);
    IncrementQueueIndex(tail);
    if(Size()==size-1) Expand();
  }

  template <typename Data>
  Data& QueueVec<Data>::Head() const{
    if(!Empty()) return Elements[head];
    else throw std::length_error("\nQueue is empty!");
  }

  template <typename Data>
  void QueueVec<Data>::Dequeue(){
    if(!Empty()){
      IncrementQueueIndex(head);
      if(size!=4 && Size()==(size/4)) Reduce();   // We reduce the queue if we removed the [(QueueVec.size/4)+1]th element.
    }
    else throw std::length_error("\nQueue is empty!");
  }

  template <typename Data>
  Data QueueVec<Data>::HeadNDequeue(){
    if(!Empty()){
      Data ret = Elements[head];
      IncrementQueueIndex(head);
      if(size!=4 && Size()==(size/4)) Reduce();
      return ret;
    }
    else throw std::length_error("\nQueue is empty!");
  }

  template <typename Data>
  inline bool QueueVec<Data>::Empty() const noexcept{
    return Size()==0;
  }

  template <typename Data>                          // Size() is not size !!!
  ulong QueueVec<Data>::Size() const noexcept{      //Size will return the number of concrete elements existing in the queue.
    ulong conc = 0;
    if(tail != head){
      if(tail > head) conc = tail - head;
      else{
        conc = head - tail;
        conc = size - conc;
      }
    }
    return conc;
  }

  template <typename Data>
  void QueueVec<Data>::Clear(){
    Data* TmpElements = new Data[4] {};
    std::swap(Elements, TmpElements);
    delete[] TmpElements;
    head = 0;
    tail = 0;
  }

  // Auxiliary member functions.
  template <typename Data>
  void QueueVec<Data>::IncrementQueueIndex(ulong& j) const noexcept{    // Proper increment of an index scanning a queue, thus based on circularity and on concrete size ( Size() ) of the queue.
    j++;
    if(j==size) j = 0;
  }

  template <typename Data>
  void QueueVec<Data>::Expand(){             // Same semantic for the Reduce()...
    Data* TmpElements = new Data[size*2] {};
    ulong j = head;                          // Pivoting on the old queue.
    ulong fixedsize = Size();                // fixedsize is fixed Size()...
    for(ulong i = 0; i < fixedsize; i++){    // Scanning till the concrete number of elements in the queue to extend.
      std::swap(Elements[j], TmpElements[i]);
      IncrementQueueIndex(j);
    }
    std::swap(Elements, TmpElements);
    size = size*2;
    head = 0;                                // When expanding, we store all the elements of the old queue from 0 to an n>0.
    tail = fixedsize;
    delete[] TmpElements;
  }

  template <typename Data>
  void QueueVec<Data>::Reduce(){
    Data* TmpElements = new Data[size/2] {};
    ulong j = head;
    ulong fixedsize = Size();
    for(ulong i = 0; i < fixedsize; i++){
      std::swap(Elements[j], TmpElements[i]);
      IncrementQueueIndex(j);
    }
    std::swap(Elements, TmpElements);
    size = size/2;
    head = 0;
    tail = fixedsize;
    delete[] TmpElements;
  }

}
