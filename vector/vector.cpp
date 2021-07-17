
namespace lasd {

  // Specific constructor with a size given.
  template <typename Data>
  Vector<Data>::Vector(const ulong newsize){
    Elements = new Data[newsize]{};                   //Curly brackets initialize the elements of the vector.
    size = newsize;
  }

  // Specific constructor with a LinearContainer given.
  template <typename Data>
  Vector<Data>::Vector(const LinearContainer<Data>& con){
    size = con.Size();
    Elements = new Data[size];
    for(ulong i = 0; i < size; i++){
      Elements[i] = con[i];
    }
  }

  // Copy constructor.
  template <typename Data>
  Vector<Data>::Vector(const Vector<Data>& vec){
    Elements = new Data[vec.size];
    std::copy(vec.Elements, vec.Elements + vec.size, Elements);   // Function "copy", takes trhree arguments: 1st and 2nd is the range, 3rd is the structure you want to write in.
    size = vec.size;
  }

  // Move constructor.
  template <typename Data>
  Vector<Data>::Vector(Vector<Data>&& vec) noexcept{
    std::swap(Elements, vec.Elements);      // Move operations expect that the structure where we "move" from, will be in ...
    std::swap(size, vec.size);              // ... a suitable condition for a possible future delete of it, so a "swap" will be proper.
  }

  // Destructor.
  template <typename Data>
  Vector<Data>::~Vector(){
    delete[] Elements;
  }

  // Copy assignment.
  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec){
    Vector<Data>* tmpvec = new Vector<Data>(vec);
    std::swap(*tmpvec, *this);      // "this" is a class-reserved keyword, it is the pointer to the object that uses "this".
    delete tmpvec;
    return *this;
  }

  // Move assignment.
  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept{
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
    return *this;
  }

  template <typename Data>
  bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept{
    ulong i = 0;
    if(size == vec.size){
      while(i < size && Elements[i] == vec.Elements[i]) i++;
      if (i >= size) return true;
    }
    return false;
  }

  template <typename Data>
  bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept{
    return !(*this==vec);
  }

  template <typename Data>
  void Vector<Data>::Resize(const ulong newsize){
    if(newsize == 0){
      Clear();
    }
    else{
      if(size != newsize){
        ulong limit = (size < newsize) ? size : newsize;
        Data* TmpElements = new Data[newsize] {};
        for(ulong i = 0; i < limit; i++){
          std::swap(Elements[i], TmpElements[i]);
        }
        std::swap(Elements, TmpElements);
        size = newsize;
        delete[] TmpElements;
      }
    }
  }

  template <typename Data>
  void Vector<Data>::Clear(){
    delete[] Elements;
    Elements = nullptr;
    size = 0;
  }

  template <typename Data>
  Data& Vector<Data>::Front() const{
    if(size != 0) return Elements[0];
    else throw std::length_error("The vector is empty!");
  }

  template <typename Data>
  Data& Vector<Data>::Back() const{
    if(size != 0) return Elements[size-1];
    else throw std::length_error("The vector is empty!");
  }

  template <typename Data>
  Data& Vector<Data>::operator[](const ulong i) const{
    if(i < size) return Elements[i];
    else throw std::out_of_range("Cannot access to the element n. " + std::to_string(i) + " in a " + std::to_string(size) + "-sized vector!");
  }

  template <typename Data>
  void Vector<Data>::MapPreOrder(const MapFunctor fun, void* par){
    for(ulong i = 0; i < size; i++){
      fun(Elements[i], par);
    }
  }

  template <typename Data>
  void Vector<Data>::MapPostOrder(const MapFunctor fun, void* par){
    ulong i = size;
    while(i > 0){
      fun(Elements[--i], par);
    }
  }

  template <typename Data>
  void Vector<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
    for(ulong i = 0; i < size; i++){
      fun(Elements[i], par, acc);
    }
  }

  template <typename Data>
  void Vector<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    ulong i = size;
    while(i > 0){
      fun(Elements[--i], par, acc);
    }
  }

}
