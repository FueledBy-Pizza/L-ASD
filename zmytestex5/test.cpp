#include <iostream>
#include "../matrix/matrix.hpp"
#include "../matrix/vec/matrixvec.hpp"
#include "../matrix/csr/matrixcsr.hpp"
#include <random>
#include <string>
using namespace std;

// Auxiliarities functions for MapFunctions.
template <typename Data>
void PrintItems(Data& x, void* p){
  cout << x << " ";
}

template <typename Data>
void Doubled(Data& x, void* p){
  x = 2*x;
}

template <typename Data>
void NegTripled(Data& y, void* p){
  y = -(y*y*y);
}

template <typename Data>
void AddStr(Data& x, void* s){
  x = *((string*)s) + x;
}

// Auxiliarities functions for FoldFunction.
template <typename Data>
void Multiplying(const Data& x, const void* par, void* acc){
  if(x < *((int*)par)) *((int*)acc) = *((int*)acc) * x;
}

template <typename Data>
void Adding(const Data& x, const void* par, void* acc){
  if(x > *((float*)par)) *((float*)acc) = *((float*)acc) + x;
}

template <typename Data>
void Concat(const Data& s, const void* par, void* sc){
  if (*((int*)(par)) >= s.size()) *((string*)sc) += s;            //stringname.size() is an #include<string> function
}

template <typename Data>
void Stampa(const Data& m, ulong i, ulong j){
  if(m.ExistsCell(i,j)) cout << m(i,j) << " ";
  else cout << "/ ";
}

template <typename Data>
bool Existing(lasd::Matrix<Data>& m, const Data& x){
  return m.Exists(x);
}

void mytest(){

  char t, t1;     //choice matrixvec, matrixcsr; choice matrixtype
  ulong rowsize, colsize;
  ulong i, j; // indexes
  int x, neutm = 1; // discriminante, neutro per la moltiplicazione
  float y, neuts = 0; //discriminante, neutro per l'addizione
  const string chara = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  string sb = ""; //string to build;
  string sc = ""; //string to concatenate
  char c1;

  cout << "1. MatrixVec\n2. MatrixCsr (Yale)\n\t";
  cin >> t;
  switch (t){
    case '1':{
      cout << "***** MatrixVec in Row-major order *****" << endl << "Type:\n1. Int MatrixVec\n2. Float MatrixVec\n3. String MatrixVec\n\t";
      cin >> t1;
      switch (t1) {
        case '1':{
          cout << "Choose Row size: ";
          cin >> rowsize;
          cout << "Choose Column size: ";
          cin >> colsize;
          lasd::MatrixVec<int> mat(rowsize, colsize);
          default_random_engine genr(random_device{}());
          uniform_int_distribution <int> distr(0, rowsize-1);
          default_random_engine genc(random_device{}());
          uniform_int_distribution <int> distc(0, colsize-1);
          default_random_engine genx(random_device{}());
          uniform_int_distribution <int> distx(1, 100);
          cout << "Number of elements in the matrix: ";
          cin >> rowsize;
          for(ulong i = 0; i < rowsize; ++i){
            mat(distr(genr), distc(genc)) = distx(genx);
          }
          cout << "Read the element (i,j) of the matrix: " << endl;
          cin >> i;
          cin >> j;
          cout << "Mat(" << i << "," << j << "): " << mat(i,j);
          cout << endl << "Write in matrix(" << i << "," << j << "): ";
          cin >> x;
          mat(i,j) = x;
          cout << "Verify if an element exists in the matrix: ";
          cin >> x;
          mat.Exists(x) ? cout << "The element exists in the matrix." : cout << "The element doesn't exist in the matrix!";
          cout << endl << "Multiply the elements of the matrix less than: ";
          cin >> x;
          mat.FoldPreOrder(Multiplying<int>, &x, &neutm);
          ((x>0) && (mat.Exists(0))) ? cout << "Result is 0." : cout << "Result is: " << neutm << ".";
          cout << endl << "Matrix: " << endl;
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
          cout << "Do you want to resize rows or columns? (r,c)\t";
          cin >> c1;
          if(c1=='r'){
            cout << "New row size: ";
            cin >> x;
            mat.RowResize(x);
            cout << endl << "Matrix resized: " << endl;
            for(ulong i = 0; i < mat.RowNumber(); i++){
              for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
              cout << endl;
            }
          }
          else if(c1=='c'){
            cout << "New column size: ";
            cin >> x;
            mat.ColumnResize(x);
            cout << endl << "Matrix resized: " << endl;
            for(ulong i = 0; i < mat.RowNumber(); i++){
              for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
              cout << endl;
            }
          }
          cout << endl << "Matrix doubled: " << endl;
          mat.MapPreOrder(Doubled<int>, nullptr);
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
        }break;
        case '2':{
          cout << "Choose Row size: ";
          cin >> rowsize;
          cout << "Choose Column size: ";
          cin >> colsize;
          lasd::MatrixVec<float> mat(rowsize, colsize);
          default_random_engine genr(random_device{}());
          uniform_int_distribution <int> distr(0, rowsize-1);
          default_random_engine genc(random_device{}());
          uniform_int_distribution <int> distc(0, colsize-1);
          default_random_engine genx(random_device{}());
          uniform_int_distribution <int> distx(1, 100);
          cout << "Number of elements in the matrix: ";
          cin >> rowsize;
          for(ulong i = 0; i < rowsize; ++i){
            mat(distr(genr), distc(genc)) = (float)(distx(genx))/10;
          }
          cout << "Read the element (i,j) of the matrix: " << endl;
          cin >> i;
          cin >> j;
          cout << "M(" << i << "," << j << "): " << mat(i,j);
          cout << endl << "Write in matrix(" << i << "," << j << "): ";
          cin >> y;
          mat(i,j) = y;
          cout << "Verify if an element exists in the matrix: ";
          cin >> y;
          mat.Exists(y) ? cout << "The element exists in the matrix." : cout << "The element doesn't exist in the matrix!";
          cout << endl << "Add the elements of the matrix greater than: ";
          cin >> y;
          mat.FoldPreOrder(Adding<float>, &y, &neuts);
          cout << "Result is " << neuts;
          cout << endl << "Matrix: " << endl;
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
          cout << endl << "Matrix negative tripled: " << endl;
          mat.MapPreOrder(NegTripled<float>, nullptr);
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
        }break;
        case '3':{
          cout << "Choose Row size: ";
          cin >> rowsize;
          cout << "Choose Column size: ";
          cin >> colsize;
          lasd::MatrixVec<string> mat(rowsize, colsize);
          default_random_engine genr(random_device{}());
          uniform_int_distribution <int> distr(0, rowsize-1);
          default_random_engine genc(random_device{}());
          uniform_int_distribution <int> distc(0, colsize-1);
          default_random_engine gen(random_device{}());
          uniform_int_distribution <int> dist(0, chara.size());
          default_random_engine genl(random_device{}());
          uniform_int_distribution <int> distl(1, 5);
          uint len = 0;
          cout << "Number of elements in the matrix: ";
          cin >> rowsize;
          for(ulong i = 0; i < rowsize; i++){
            len = distl(genl);
            for(ulong j = 0; j < len; j++){
              sc += chara[dist(gen)];
            }
            mat(distr(genr), distc(genc)) = sc;
            sc = "";
          }
          cout << "Read the element (i,j) of the matrix: " << endl;
          cin >> i;
          cin >> j;
          cout << "M(" << i << "," << j << "): " << mat(i,j);
          cout << endl << "Write in matrix(i,j): ";
          cin >> sc;
          mat(i,j) = sc;
          cout << "Verify if an element exists in the matrix: ";
          cin >> sc;
          mat.Exists(sc) ? cout << "The element exists in the matrix." : cout << "The element doesn't exist in the matrix!";
          cout << endl << "Concatenate string having length less equal than: ";
          cin >> x;
          mat.FoldPreOrder(Concat<string>, &x, &sb);
          cout << "Result is " << sb;
          cout << endl << "Matrix: " << endl;
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
          cout << endl << "Concatenate the following string to all the elements: ";
          cin >> sc;
          mat.MapPreOrder(AddStr<string>, &sc);
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
        }break;
        default:{
          cout << "Not a choice..." << endl;
        }
      }
    }break;
    case '2':{
      cout << "***** MatrixCSR (YALE) *****" << endl << "Type:\n1. Int MatrixCSR\n2. Float MatrixCSR\n3. String MatrixCSR\n\t";
      cin >> t1;
      switch (t1) {
        case '1':{
          cout << "Choose Row size: ";
          cin >> rowsize;
          cout << "Choose Column size: ";
          cin >> colsize;
          lasd::MatrixCSR<int> mat(rowsize, colsize);
          default_random_engine genr(random_device{}());
          uniform_int_distribution <int> distr(0, rowsize-1);
          default_random_engine genc(random_device{}());
          uniform_int_distribution <int> distc(0, colsize-1);
          default_random_engine genx(random_device{}());
          uniform_int_distribution <int> distx(1, 100);
          cout << "Number of elements in the matrix: ";
          cin >> rowsize;
          for(ulong i = 0; i < rowsize; ++i){
            mat(distr(genr), distc(genc)) = distx(genx);
          }
          cout << "Read the element (i,j) of the matrix: " << endl;
          cin >> i;
          cin >> j;
          cout << "M(" << i << "," << j << "): " << mat(i,j);
          cout << endl << "Write in matrix(" << i << "," << j << "): ";
          cin >> x;
          mat(i,j) = x;
          cout << "Verify if an element exists in the matrix: ";
          cin >> x;
          Existing(mat, x) ? cout << "The element exists in the matrix." : cout << "The element doesn't exist in the matrix!";
          cout << endl << "Multiply the elements of the matrix less than: ";
          cin >> x;
          mat.FoldPreOrder(Multiplying<int>, &x, &neutm);
          ((x>0) && (Existing(mat, 0))) ? cout << "Result is 0." : cout << "Result is: " << neutm << ".";
          cout << endl << "Matrix: " << endl;
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
          cout << endl << "Do you want to resize rows or columns? (r,c)\t";
          cin >> c1;
          if(c1=='r'){
            cout << "New row size: ";
            cin >> x;
            mat.RowResize(x);
            cout << endl << "Matrix resized: " << endl;
            for(ulong i = 0; i < mat.RowNumber(); i++){
              for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
              cout << endl;
            }
          }
          else if(c1=='c'){
            cout << "New column size: ";
            cin >> x;
            mat.ColumnResize(x);
            cout << endl << "Matrix resized: " << endl;
            for(ulong i = 0; i < mat.RowNumber(); i++){
              for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
              cout << endl;
            }
          }
          cout << endl << "Matrix doubled: " << endl;
          mat.MapPreOrder(Doubled<int>, nullptr);
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
        }break;
        case '2':{
          cout << "Choose Row size: ";
          cin >> rowsize;
          cout << "Choose Column size: ";
          cin >> colsize;
          lasd::MatrixCSR<float> mat(rowsize, colsize);
          default_random_engine genr(random_device{}());
          uniform_int_distribution <int> distr(0, rowsize-1);
          default_random_engine genc(random_device{}());
          uniform_int_distribution <int> distc(0, colsize-1);
          default_random_engine genx(random_device{}());
          uniform_int_distribution <int> distx(1, 100);
          cout << "Number of elements in the matrix: ";
          cin >> rowsize;
          for(ulong i = 0; i < rowsize; ++i){
            mat(distr(genr), distc(genc)) = (float)(distx(genx))/10;
          }
          cout << "Read the element (i,j) of the matrix: " << endl;
          cin >> i;
          cin >> j;
          cout << "M(" << i << "," << j << "): " << mat(i,j);
          cout << endl << "Write in matrix(" << i << "," << j << "): ";
          cin >> y;
          mat(i,j) = y;
          cout << "Verify if an element exists in the matrix: ";
          cin >> y;
          Existing(mat, y) ? cout << "The element exists in the matrix." : cout << "The element doesn't exist in the matrix!";
          cout << endl << "Add the elements of the matrix greater than: ";
          cin >> y;
          mat.FoldPreOrder(Adding<float>, &y, &neuts);
          cout << "Result is " << neuts;
          cout << endl << "Matrix: " << endl;
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
          cout << endl << "Matrix negative tripled: " << endl;
          mat.MapPreOrder(NegTripled<float>, nullptr);
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
        }break;
        case '3':{
          cout << "Choose Row size: ";
          cin >> rowsize;
          cout << "Choose Column size: ";
          cin >> colsize;
          lasd::MatrixCSR<string> mat(rowsize, colsize);
          default_random_engine genr(random_device{}());
          uniform_int_distribution <int> distr(0, rowsize-1);
          default_random_engine genc(random_device{}());
          uniform_int_distribution <int> distc(0, colsize-1);
          default_random_engine gen(random_device{}());
          uniform_int_distribution <int> dist(0, chara.size());
          default_random_engine genl(random_device{}());
          uniform_int_distribution <int> distl(1, 5);
          uint len = 0;
          cout << "Number of elements in the matrix: ";
          cin >> rowsize;
          for(ulong i = 0; i < rowsize; i++){
            len = distl(genl);
            for(ulong j = 0; j < len; j++){
              sc += chara[dist(gen)];
            }
            mat(distr(genr), distc(genc)) = sc;
            sc = "";
          }
          cout << "Read the element (i,j) of the matrix: " << endl;
          cin >> i;
          cin >> j;
          cout << "M(" << i << "," << j << "): " << mat(i,j);
          cout << endl << "Write in matrix(i,j): ";
          cin >> sc;
          mat(i,j) = sc;
          cout << "Verify if an element exists in the matrix: ";
          cin >> sc;
          Existing(mat, sc) ? cout << "The element exists in the matrix." : cout << "The element doesn't exist in the matrix!";
          cout << endl << "Concatenate string having length less equal than: ";
          cin >> x;
          mat.FoldPreOrder(Concat<string>, &x, &sb);
          cout << "Result is " << sb;
          cout << endl << "Matrix: " << endl;
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
          cout << endl << "Concatenate the following string to all the elements: ";
          cin >> sc;
          mat.MapPreOrder(AddStr<string>, &sc);
          for(ulong i = 0; i < mat.RowNumber(); i++){
            for(ulong j = 0; j < mat.ColumnNumber(); j++) Stampa(mat, i, j);
            cout << endl;
          }
        }break;
        default:{
          cout << "Not a choice..." << endl;
        }
    }break;
    default:{
      cout << endl << "Not a choice..." << endl;
    }
  }
}

}
