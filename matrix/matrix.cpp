namespace lasd {

  template <typename Data>
  inline const ulong& Matrix<Data>::RowNumber() const{
    return row;
  }

  template <typename Data>
  inline const ulong& Matrix<Data>::ColumnNumber() const{
    return col;
  }

}
