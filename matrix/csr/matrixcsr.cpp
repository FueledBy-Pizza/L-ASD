
namespace lasd {

// Default constructor.
template <typename Data>
MatrixCSR<Data>::MatrixCSR(){
  vec.Resize(1);
  vec[0] = &top;
}

// Specific constructor.
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const ulong r, const ulong c){
  vec.Resize(r+1);
  row = r;
  col = c;
  size = 0;
  for(ulong i = 0; i < vec.Size(); i++) vec[i] = &top;
}

// Copy constructor.
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& m) : MatrixCSR(m.row, m.col){
  // row = m.RowNumber();
  // col = m.ColumnNumber();
  // vec.Resize(row+1);
  // for(ulong i = 0; i < vec.Size(); i++) vec[i] = &top;
  for(ulong i = 0; i < row; i++){                                         // Cycling on the rows.
    for(Node** tmp = m.vec[i]; tmp!=m.vec[i+1]; tmp=&((**tmp).next)){     // Until the rows isn't finished, go forward with tmp.
      (*this)(i,(**tmp).x.second) = (**tmp).x.first;                      // mat(i,j) = tmp->x.
    }
  }
  size = m.size;
}

// Move constructor.
template <typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data>&& m) noexcept{
  vec.Resize(1);        // inizializzare il vettore riga... (non nell'assignment..)
  std::swap(top, m.top);
  std::swap(tail, m.tail);
  std::swap(row, m.row);
  std::swap(col, m.col);
  std::swap(vec, m.vec);
  std::swap(size, m.size);
}

// Copy assignment.
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>& m){
  row = m.RowNumber();
  col = m.ColumnNumber();
  vec.Resize(row+1);
  for(ulong i = 0; i < vec.Size(); i++) vec[i] = &top;
  for(ulong i = 0; i < row; i++){
    for(Node** tmp = m.vec[i]; tmp!=m.vec[i+1]; tmp=&((**tmp).next)){
      (*this)(i,(**tmp).x.second) = (**tmp).x.first;
    }
  }
  size = m.size;        // ridondante?
  return *this;
}

// Move assignment.
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& m) noexcept{
  std::swap(top, m.top);
  std::swap(tail, m.tail);
  std::swap(row, m.row);
  std::swap(col, m.col);
  std::swap(vec, m.vec);
  std::swap(size, m.size);
  return *this;
}

template <typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& m) const noexcept{
  return (row==m.row) && (col==m.col) && (List<std::pair<Data,ulong>>::operator==(m));
}

template <typename Data>
bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& m) const noexcept{
  return !(*this==m);
}

template <typename Data>
void MatrixCSR<Data>::RowResize(const ulong r){
  if(r!=row){
    if(r==0) vec.Resize(1);
    else{
      if(r < row){                // Dobbiamo solo aggiornare il vettore riga, dopo aver eliminato, a partire dalla riga successiva, tutti i nodi.
        Node* tmp = *(vec[r]);    // Mi pongo sulla casella r del vettore, da lì dovrò eliminare.
        Node* tmp2 = tmp;
        while(tmp2!=nullptr){     // Eliminazione di tutti i nodi progressivamente.
          tmp2 = tmp2->next;
          delete tmp;
          tmp = tmp2;
          size--;                 // Per ogni nodo che elimino devo diminuire la size...
        }
        *(vec[r]) = nullptr;
        vec.Resize(r+1);
      }
      else{
        vec.Resize(r+1);
        for(ulong i = row; i < vec.Size(); i++) vec[i] = vec[row];    // Notare che row è ancora il valore vecchio, e parto proprio da lì.
      }
    }
    row = r;                                                          // In tutti i casi, aggiorno row, solo alla fine (utile proprio per l'ultimo ciclo effettuato).
  }
}

template <typename Data>
void MatrixCSR<Data>::ColumnResize(unsigned long c){
  if(c!=col){
    if(c==0) List<std::pair<Data, unsigned long>>::Clear();
    else{
      if(c < col){                  // Se c > col dobbiamo solo aggiornare l'attributo col, ma questo lo facciamo comunque dopo.
        ulong i = 1;
        Node** curr = &top;
        while(i <= row){            // Dobbiamo visitare tutte le righe.
          Node* nod = nullptr;
          Node** succ = vec[i];
          while(curr!=succ && (**curr).x.second < c){
            nod = *curr;
            curr = &(*nod).next;
          }
          if(curr!=succ){           // Abbiamo trovato una colonna da cui dobbiamo eliminare i nodi.
            Node* tmp = *curr;      // Dato che (DA QUI IN POI PER TUTTA LA RIGA) devo eliminare il nodo il cui indirizzo è contenuto nel campo next dereferenziato da curr, mi salvo questo valore in tmp ...
            *curr = *succ;          // ... perchè il campo next dereferenziato da curr, va cambiato, inoltre già so che deve puntare al primo elemento della successiva riga.
            *succ = nullptr;        // Stacchiamo, sempre a partire da qui, tutti i nodi di questa riga dalla lista, quindi all'ultimo nodo che eliminamo, settiamo a nullptr il campo next.
            while(tmp!=nullptr){    // Eliminazione di tutti quei nodi a partire dal primo...
              Node* del = tmp;
              tmp = tmp->next;
              delete del;
              size--;
            }
          }
          for(; (i<=row) && (vec[i]==succ); i++){    // Se non abbiamo eliminato, mi porto semplicemente avanti alla prima riga non vuota, altrimenti viene aggiornato il vettore riga.
            vec[i] = curr;
          }
        }
      }
    }
    col = c;
  }
}

template <typename Data>
bool MatrixCSR<Data>::ExistsCell(const ulong r, const ulong c) const noexcept{
  if(r >= row || c >= col) return false;
  Node** tmp = vec[r];
  while((*tmp)!=nullptr && tmp!=vec[r+1]){
    if((**tmp).x.second==c) return true;
    tmp = &((**tmp).next);
  }
  return false;
}

template <typename Data>
Data& MatrixCSR<Data>::operator()(const ulong r, const ulong c){
  if(r < row && c < col){
    Node** tmp = vec[r];
    Node** tmp2 = vec[r+1];                                     // N.B. è sempre lecita questa istruzione, infatti quando andiamo a costrutire il vettore riga, lo costruiamo di una dimensione pari ad r+1.
    while(tmp!=tmp2 && ((**tmp).x.second)<=c){                  // Scorro la lista controllando se la riga non è finita, e se non ho ecceduto l'indice di colonna ...
      if((**tmp).x.second==c) return (**tmp).x.first;           // Per verificare se esiste già quella cella, questo è proprio il caso in cui il riferimento a questa casella (r,c) già esisteva, quindi ritorno quello ...
      tmp = &(**tmp).next;
    }
    std::pair<Data, ulong> p;                                   // ... altrimenti, se sono arrivato qui, non esisteva quella cella (r,c), quindi la creiamo, e abbiamo già pronto il puntatore tmp che dovrà puntare a questa nuova cella.
    p.second = c;
    Node* n = new Node(p);
    size++;
    n->next = *tmp;                                             // IL next del nuovo nodo sarà il next a cui punta tmp ...
    *tmp = n;                                                   // ... mentre il campo next puntato da tmp punterà al nuovo nodo.
    ulong r2 = r+1;
    if(tmp==tmp2){                                              // Caso in cui abbiamo creato una nuova cella alla fine di una riga, oppure in una riga vuota: in questi casi dobbiamo aggiornare il vettore riga.
      while(r2<vec.Size() && tmp2==vec[r2]){
        vec[r2] = &(n->next);
        r2++;
      }
    }
    return n->x.first;
  }
  throw std::out_of_range("Matrix CSR: Cannot access to an (" + std::to_string(r) + "," + std::to_string(c) + ") element in a " + std::to_string(row) + "x" + std::to_string(col) + " matrix");
}

template <typename Data>
const Data& MatrixCSR<Data>::operator()(const ulong r, const ulong c) const{
  if(r < row && c < col){
    Node** tmp = vec[r];
    while(tmp!=vec[r+1]){                                     // Cycling until the row isn't finished.
      if((**tmp).x.second==c) return (**tmp).x.first;
      tmp = &((**tmp).next);
    }
    throw std::length_error("Matrix CSR: The element (" + std::to_string(r) + "," + std::to_string(c) + ") does not exist in the matrix!");
  }
  throw std::out_of_range("Matrix CSR: Cannot access to an (" + std::to_string(r) + "," + std::to_string(c) + ") element in a " + std::to_string(row) + "x" + std::to_string(col) + " matrix!");
}

template <typename Data>
void MatrixCSR<Data>::Clear(){
  List<std::pair<Data,ulong>>::Clear();
  vec.Resize(1);
  row = 0;
  col = 0;
  size = 0;
}

template <typename Data>
void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void* par){
  List<std::pair<Data,ulong>>::MapPreOrder([&fun](std::pair<Data,ulong>& d, void* parx) {fun(d.first, parx);}, par);
}

template <typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* par){
  List<std::pair<Data,ulong>>::MapPostOrder([&fun](std::pair<Data,ulong>& d, void* parx) {fun(d.first, parx);}, par);
}

template <typename Data>
void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
  List<std::pair<Data,ulong>>::FoldPreOrder([&fun](const std::pair<Data,ulong>& d, const void* parx, void* accx) {fun(d.first, parx, accx);}, par, acc);
}

template <typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
  List<std::pair<Data,ulong>>::FoldPostOrder([&fun](const std::pair<Data,ulong>& d, const void* parx, void* accx) {fun(d.first, parx, accx);}, par, acc);
}

}
