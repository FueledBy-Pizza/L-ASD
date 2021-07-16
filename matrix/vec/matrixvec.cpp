
namespace lasd {

  // Destructor.
  template <typename Data>
  MatrixVec<Data>::~MatrixVec(){
    Clear();
  }

  // Copy assignment.
  template <typename Data>
  MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data>& m){
    Vector<Data>::operator=(m);
    row = m.row;
    col = m.col;
    return *this;
  }

  // Move assignment.
  template <typename Data>
  MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& m){
    Vector<Data>::operator=(std::move(m));
    std::swap(row, m.row);
    std::swap(col, m.col);
    return *this;
  }

  // Comparison operators.
  template <typename Data>
  bool MatrixVec<Data>::operator==(const MatrixVec<Data>& m) const noexcept{
    return (row==m.row) && (col==m.col) && (Vector<Data>::operator==(m));
  }

  template <typename Data>
  bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& m) const noexcept{
    return !(*this==m);
  }

  template <typename Data>
  void MatrixVec<Data>::RowResize(const ulong r){
    if(r!=row){
      Vector<Data>::Resize(r*col);
      row = r;
    }
  }

  template <typename Data>
  void MatrixVec<Data>::ColumnResize(const ulong c){
    if(c != col){
      if(c == 0) Clear();
      else{
        Data* TmpElements = new Data[row*c]{};
        ulong limit = (col < c) ? col : c;
        for(ulong i = 0; i < row ; i++){
          for(ulong j = 0; j < limit; j++){
            std::swap(Elements[(i*col)+j], TmpElements[(i*c)+j]);
          }
        }
        std::swap(Elements, TmpElements);
        size = row*c;
        delete[] TmpElements;
      }
      col = c;
    }
  }

  template <typename Data>
  bool MatrixVec<Data>::ExistsCell(const ulong r, const ulong c) const noexcept{
    if(r>=row || c>=col) return false;
    return true;
  }

  template <typename Data>
  const Data& MatrixVec<Data>::operator()(const ulong r, const ulong c) const{
    if(ExistsCell(r, c)) return Elements[(r*col)+c];
    throw std::out_of_range("MatrixVec: cannot access at the (" + std::to_string(r) + "," + std::to_string(c) + ") element in a " + std::to_string(row) + "x" + std::to_string(col) + " matrix!" );
  }

  template <typename Data>
  Data& MatrixVec<Data>::operator()(const ulong r, const ulong c){
    return const_cast<Data&>(static_cast<const MatrixVec<Data>*>(this)->operator()(r, c));
  }

  template <typename Data>
  void MatrixVec<Data>::Clear(){
    Vector<Data>::Clear();
    row = 0;
    col = 0;
    size = 0;
  }

}
