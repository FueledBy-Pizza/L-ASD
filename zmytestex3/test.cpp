#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include "test.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../stack/lst/stacklst.hpp"
using namespace std;

// Auxiliarities functions for MapFunctions.
template <typename Data>
void PrintElement(Data& x, void* p){
  cout << x << " ";
}

template <typename Data>
void Triple(Data& x, void* p){
  x*=3;
}

template <typename Data>
void Cubed(Data& x, void* p){
  x = pow(x, 3.0);
}

template <typename Data>
void AddStr(Data& x, void* s){
  x = *((string*)s) + x;
}

// Auxiliarities functions for FoldFunctions.
template <typename Data>
void Adding(const Data& x, const void* par, void* acc){
  if(x > *((float*)par)) *((float*)acc) = *((float*)acc) + x;
}

template <typename Data>
void Multiply(const Data& x, const void* par, void* acc){
  if(x < *((int*)par)) *((int*)acc) = *((int*)acc) * x;
}

template <typename Data>
void Concat(const Data& s, const void* par, void* acc){
  if( s.size() <= *((int*)par) ) *((string*)acc) += s;
}

void mytest(){

  uint s = 0;                        // dimensione array
  uint l = 0;                        // dimensione lunghezza stringhe
  int x = 0;                         // discriminante per la moltiplicazione di interi < x, discriminante per la concatenazione di stringhe con una lunghezza <= di x, valore da inserire per la modifica di un nodo (l-r navigation)
  float y = 0;                       // discriminante per la somma di float > x, valore da inserire per la modifica di un nodo (l-r navigation)
  string sc = "";                    // string to concatenate, valore da inserire per la modifica di un nodo (l-r navigation)
  const string chara = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  float neuts = 0;                   // neutral sum
  int neutm = 1;                     // neutral multiply
  char c, c2, c3 = '0', c4;          // choice, choice BT type, choice iterator, choice ON iterator

  do {
    cout << "\nPick a choice:\n1. Build a BTLnk from a Linear Container\n2. Build  BTVec from a Linear Container\n3. Exit\n";
    cin >> c;
    switch (c) {
      case '1':{
        do {
          cout << "\n1)\ti. Build an integer BTLnk from a Linear Container\n1)\tf. Build a float BTLnk from a Linear Container\n1)\ts. Build a string BTLnk from a Linear Container\n\tb. Back\n\t";
          cin >> c2;
          switch (c2) {
            case 'i':{
              cout << "\nEnter vector size: ";
              cin >> s;
              lasd::Vector<int> vec(s);
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dist(0, 100);
              for(ulong i = 0; i<vec.Size(); i++){
               vec[i] = dist(gen);
              }
              cout << "Linear Container (Vettore):" << endl;
              vec.MapPreOrder(PrintElement<int>, nullptr);
              lasd::BinaryTreeLnk<int> bt(vec);
              cout << "\nAlberoLnk in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<int>, nullptr);
              cout << "\nAlberoLnk in PostOrder:" << endl;
              bt.MapPostOrder(PrintElement<int>, nullptr);
              cout << "\nAlberoLnk in InOrder:" << endl;
              bt.MapInOrder(PrintElement<int>, nullptr);
              cout << "\nAlberoLnk in BreadthOrder:" << endl;
              bt.MapBreadth(PrintElement<int>, nullptr);
              lasd::BinaryTree<int>::Node* n(&(bt.Root()));                             /*Navigation with Left-Right*/
              c3 = '0';
              do {
                cout << "\n***1i) BT Left-Right Navigation***";
                if(c3!='4'){
                  cout << "\nWhat is your choice?\n1) Re-write Node\n2)Node->sx\n3)Node->dx\n4)None";
                  cin >> c3;
                }
                switch (c3) {
                  case '1':{
                    cout << "\nInsert: ";
                    cin >> x;
                    n->Element() = x;
                    x = 0;
                  }break;
                  case '2':{
                    if(n->HasLeftChild()) n = &(n->LeftChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '3':{
                    if(n->HasRightChild()) n = &(n->RightChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '4':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice...";
                  }break;
                }
              } while(c3!='4');
              do {                                                            /*Navigation with iterator*/
                cout << "\n***1i) BT iterator Navigation*** Pick your iterator:\nP. PreOrder\nI. InOrder\nO. PostOrder\nR. BreadthOrder\nB. Back\t";
                cin >> c3;
                switch (c3) {
                  case 'p':{
                    lasd::BTPreOrderIterator<int> i(bt);
                    do {
                      cout << "\n***1i) BT Navigation***\n**PreOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'i':{
                    lasd::BTInOrderIterator<int> i(bt);
                    do {
                      cout << "\n***1i) BT iterator Navigation***\n**InOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'o':{
                    lasd::BTPostOrderIterator<int> i(bt);
                    do {
                      cout << "\n***1i) BT iterator Navigation***\n**PostOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'r':{
                    lasd::BTBreadthIterator<int> i(bt);
                    do {
                      cout << "\n***1i) BT iterator Navigation***\n**BreadthOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'b':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice . . .";
                  }break;
                }
              } while(c3!='b');
              cout << "\nVerify if an element exists in the binary tree: ";
              cin >> x;
              bt.Exists(x) ? cout << "\nThe element exists in the binary tree!" : cout << "\nThe element doesn't exist in the binary tree!";
              cout << "\nMultiply the elements of the tree less than: ";
              cin >> x;
              bt.FoldPreOrder(Multiply<int>, &x, &neutm);
              cout << "The multiply is: " << neutm;
              neutm = 1;
              cout << "\nTripled elements of the tree (PreOrder visit): ";
              bt.MapPostOrder(Triple<int>, nullptr);
              bt.MapPreOrder(PrintElement<int>, nullptr);
              cout << "\nClearing the tree...";
              bt.Clear();
              cout << "\nAlberoLnk in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<int>, nullptr);
            }break;
            case 'f':{
              cout << "\nEnter vector size: ";
              cin >> s;
              lasd::Vector<float> vec(s);
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dist(0, 100);
              for(ulong i = 0; i<vec.Size(); i++){
               vec[i] = ((float)dist(gen)/10);
              }
              cout << "Linear Container (Vettore):" << endl;
              vec.MapPreOrder(PrintElement<float>, nullptr);
              lasd::BinaryTreeLnk<float> bt(vec);
              cout << "\nAlberoLnk in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<float>, nullptr);
              cout << "\nAlberoLnk in PostOrder:" << endl;
              bt.MapPostOrder(PrintElement<float>, nullptr);
              cout << "\nAlberoLnk in InOrder:" << endl;
              bt.MapInOrder(PrintElement<float>, nullptr);
              cout << "\nAlberoLnk in BreadthOrder:" << endl;
              bt.MapBreadth(PrintElement<float>, nullptr);
              lasd::BinaryTree<float>::Node* n(&(bt.Root()));                             /*Navigation with Left-Right*/
              c3 = '0';
              do {
                cout << "\n***1f) BT Left-Right Navigation***";
                if(c3!='4'){
                  cout << "\nWhat is your choice?\n1) Re-write Node\n2)Node->sx\n3)Node->dx\n4)None";
                  cin >> c3;
                }
                switch (c3) {
                  case '1':{
                    cout << "\nInsert: ";
                    cin >> y;
                    n->Element() = y;
                    y = 0;
                  }break;
                  case '2':{
                    if(n->HasLeftChild()) n = &(n->LeftChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '3':{
                    if(n->HasRightChild()) n = &(n->RightChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '4':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice...";
                  }break;
                }
              } while(c3!='4');
              do {                                                                          /*Navigation with iterator*/
                cout << "\n***1f) BT iterator Navigation*** Pick your iterator:\nP. PreOrder\nI. InOrder\nO. PostOrder\nR. BreadthOrder\nB. Back\t";
                cin >> c3;
                switch (c3) {
                  case 'p':{
                    lasd::BTPreOrderIterator<float> i(bt);
                    do {
                      cout << "\n***1i) BT iterator Navigation***\n**PreOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'i':{
                    lasd::BTInOrderIterator<float> i(bt);
                    do {
                      cout << "\n***1f) BT iterator Navigation***\n**InOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'o':{
                    lasd::BTPostOrderIterator<float> i(bt);
                    do {
                      cout << "\n***1f) BT iterator Navigation***\n**PostOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'r':{
                    lasd::BTBreadthIterator<float> i(bt);
                    do {
                      cout << "\n***1f) BT iterator Navigation***\n**BreadthOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'b':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice . . .";
                  }break;
                }
              } while(c3!='b');
              cout << "\nVerify if an element exists in the binary tree: ";
              cin >> y;
              bt.Exists(y) ? cout << "\nThe element exists in the binary tree!" : cout << "\nThe element doesn't exist in the binary tree!";
              cout << "\nSum the elements of the tree greater than: ";
              cin >> y;
              bt.FoldPreOrder(Adding<float>, &y, &neuts);
              cout << "\nThe sum is: " << neuts;
              neuts = 0;
              cout << "\nCubed elements of the tree (PostOrder visit): ";
              bt.MapPreOrder(Cubed<float>, nullptr);
              bt.MapPostOrder(PrintElement<float>, nullptr);
              cout << "\nClearing the tree...";
              bt.Clear();
              cout << "\nAlberoLnk in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<float>, nullptr);
            }break;
            case 's':{
              cout << "\nEnter vector size: ";
              cin >> s;
              lasd::Vector<string> vec(s);
              string rs = "";
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dist(0, chara.size());
              default_random_engine genl(random_device{}());
              uniform_int_distribution <int> distl(1, 10);
              for(uint i = 0; i < s; i++){
                l = distl(genl);
                for(uint j = 0; j < l; j++){
              		rs += chara[dist(gen)];
              	}
                vec[i] = rs;
                rs = "";
              }
              cout << "Linear Container (Vettore):" << endl;
              vec.MapPreOrder(PrintElement<string>, nullptr);
              lasd::BinaryTreeLnk<string> bt(vec);
              cout << "\nAlberoLnk in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<string>, nullptr);
              cout << "\nAlberoLnk in PostOrder:" << endl;
              bt.MapPostOrder(PrintElement<string>, nullptr);
              cout << "\nAlberoLnk in InOrder:" << endl;
              bt.MapInOrder(PrintElement<string>, nullptr);
              cout << "\nAlberoLnk in BreadthOrder:" << endl;
              bt.MapBreadth(PrintElement<string>, nullptr);
              lasd::BinaryTree<string>::Node* n(&(bt.Root()));                             /*Navigation with Left-Right*/
              c3 = '0';
              do {
                cout << "\n***1s) BT Left-Right Navigation***";
                if(c3!='4'){
                  cout << "\nWhat is your choice?\n1) Re-write Node\n2)Node->sx\n3)Node->dx\n4)None";
                  cin >> c3;
                }
                switch (c3) {
                  case '1':{
                    cout << "\nInsert: ";
                    cin >> sc;
                    n->Element() = sc;
                    sc = "";
                  }break;
                  case '2':{
                    if(n->HasLeftChild()) n = &(n->LeftChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '3':{
                    if(n->HasRightChild()) n = &(n->RightChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '4':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice...";
                  }break;
                }
              } while(c3!='4');
              do {                                                                                                 /*Navigation with iterator*/
                cout << "\n***1s) BT iterator Navigation*** Pick your iterator:\nP. PreOrder\nI. InOrder\nO. PostOrder\nR. BreadthOrder\nB. Back\t";
                cin >> c3;
                switch (c3) {
                  case 'p':{
                    lasd::BTPreOrderIterator<string> i(bt);
                    do {
                      cout << "\n***1i) BT iterator iterator Navigation***\n**PreOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'i':{
                    lasd::BTInOrderIterator<string> i(bt);
                    do {
                      cout << "\n***1s) BT iterator Navigation***\n**InOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'o':{
                    lasd::BTPostOrderIterator<string> i(bt);
                    do {
                      cout << "\n***1s) BT iterator Navigation***\n**PostOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'r':{
                    lasd::BTBreadthIterator<string> i(bt);
                    do {
                      cout << "\n***1s) BT iterator Navigation***\n**BreadthOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'b':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice . . .";
                  }break;
                }
              } while(c3!='b');
              cout << "\nVerify if an element exists in the binary tree: ";
              cin >> sc;
              bt.Exists(sc) ? cout << "\nThe element exists in the binary tree!" : cout << "\nThe element doesn't exist in the binary tree!";
              sc = "";
              cout << "\n-Pre Order- Concatenate string of the BT having less or equal length than: ";
              cin >> x;
              bt.FoldPreOrder(Concat<string>, &x, &sc);
              cout << "The concatenated string is: " << sc;
              sc = "";
              cout << "\n-Post Order- Concatenate string of the BT having less or equal length than: ";
              cin >> x;
              bt.FoldPostOrder(Concat<string>, &x, &sc);
              cout << "The concatenated string is: " << sc;
              sc = "";
              cout << "\n-In Order- Concatenate string of the BT having less or equal length than: ";
              cin >> x;
              bt.FoldInOrder(Concat<string>, &x, &sc);
              cout << "The concatenated string is: " << sc;
              sc = "";
              cout << "\n-Breadth Order- Concatenate string of the BT having less or equal length than: ";
              cin >> x;
              bt.FoldBreadth(Concat<string>, &x, &sc);
              cout << "The concatenated string is: " << sc;
              sc = "";
              cout << "\nInsert a string that will be pushed to every string: ";
              cin >> sc;
              bt.MapPreOrder(AddStr<string>, &sc);
              cout << "\nAlberoLnk in InOrder:" << endl;
              bt.MapInOrder(PrintElement<string>, nullptr);
              cout << "\nClearing the tree...";
              bt.Clear();
              cout << "\nAlberoLnk in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<string>, nullptr);
            }break;
            case 'b':{
              cout << "Back . . .\n";
            }break;
            default:{
              cout << "\nNot a choice...";
            }break;
          }
        } while(c2!='b');
      }break;
      case '2':{
        do {
          cout << "\n2)\ti. Build an integer BTVec from a Linear Container\n2)\tf. Build a float BTVec from a Linear Container\n2)\ts. Build a string BTVec from a Linear Container\n\tb. Back\n\t";
          cin >> c2;
          switch (c2) {
            case 'i':{
              cout << "\nEnter vector size: ";
              cin >> s;
              lasd::Vector<int> vec(s);
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dist(0, 100);
              for(ulong i = 0; i<vec.Size(); i++){
               vec[i] = dist(gen);
              }
              cout << "Linear Container (Vettore):" << endl;
              vec.MapPreOrder(PrintElement<int>, nullptr);
              lasd::BinaryTreeVec<int> bt(vec);
              cout << "\nAlberoVec in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<int>, nullptr);
              cout << "\nAlberoVec in PostOrder:" << endl;
              bt.MapPostOrder(PrintElement<int>, nullptr);
              cout << "\nAlberoVec in InOrder:" << endl;
              bt.MapInOrder(PrintElement<int>, nullptr);
              cout << "\nAlberoVec in BreadthOrder:" << endl;
              bt.MapBreadth(PrintElement<int>, nullptr);
              lasd::BinaryTree<int>::Node* n(&(bt.Root()));
              c3 = '0';
              do {
                cout << "\n***2i) BT Left-Right Navigation***";                                 /*Navigation with Left-Right*/
                if(c3!='4'){
                  cout << "\nWhat is your choice?\n1) Re-write Node\n2)Node->sx\n3)Node->dx\n4)None";
                  cin >> c3;
                }
                switch (c3) {
                  case '1':{
                    cout << "\nInsert: ";
                    cin >> x;
                    n->Element() = x;
                    x = 0;
                  }break;
                  case '2':{
                    if(n->HasLeftChild()) n = &(n->LeftChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '3':{
                    if(n->HasRightChild()) n = &(n->RightChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '4':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice...";
                  }break;
                }
              } while(c3!='4');
              do {
                cout << "\n***2i) BT iterator Navigation*** Pick your iterator:\nP. PreOrder\nI. InOrder\nO. PostOrder\nR. BreadthOrder\nB. Back\t";
                cin >> c3;
                switch (c3) {
                  case 'p':{
                    lasd::BTPreOrderIterator<int> i(bt);                                                            /*Navigation with iterator*/
                    do {
                      cout << "\n***1i) BT iterator Navigation***\n**PreOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'i':{
                    lasd::BTInOrderIterator<int> i(bt);
                    do {
                      cout << "\n***2i) BT iterator Navigation***\n**InOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'o':{
                    lasd::BTPostOrderIterator<int> i(bt);
                    do {
                      cout << "\n***2i) BT iterator Navigation***\n**PostOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'r':{
                    lasd::BTBreadthIterator<int> i(bt);
                    do {
                      cout << "\n***2i) BT iterator Navigation***\n**BreadthOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'b':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice . . .";
                  }break;
                }
              } while(c3!='b');
              cout << "\nVerify if an element exists in the binary tree: ";
              cin >> x;
              bt.Exists(x) ? cout << "\nThe element exists in the binary tree!" : cout << "\nThe element doesn't exist in the binary tree!";
              cout << "\nMultiply the elements of the tree less than: ";
              cin >> x;
              bt.FoldPreOrder(Multiply<int>, &x, &neutm);
              cout << "The multiply is: " << neutm;
              neutm = 1;
              cout << "\nTripled elements of the tree (PreOrder visit): ";
              bt.MapPostOrder(Triple<int>, nullptr);
              bt.MapPreOrder(PrintElement<int>, nullptr);
              cout << "\nClearing the tree...";
              bt.Clear();
              cout << "\nAlberoVec in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<int>, nullptr);
            }break;
            case 'f':{
              cout << "\nEnter vector size: ";
              cin >> s;
              lasd::Vector<float> vec(s);
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dist(0, 100);
              for(ulong i = 0; i<vec.Size(); i++){
               vec[i] = ((float)dist(gen)/10);
              }
              cout << "Linear Container (Vettore):" << endl;
              vec.MapPreOrder(PrintElement<float>, nullptr);
              lasd::BinaryTreeVec<float> bt(vec);
              cout << "\nAlberoVec in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<float>, nullptr);
              cout << "\nAlberoVec in PostOrder:" << endl;
              bt.MapPostOrder(PrintElement<float>, nullptr);
              cout << "\nAlberoVec in InOrder:" << endl;
              bt.MapInOrder(PrintElement<float>, nullptr);
              cout << "\nAlberoVec in BreadthOrder:" << endl;
              bt.MapBreadth(PrintElement<float>, nullptr);
              lasd::BinaryTree<float>::Node* n(&(bt.Root()));
              c3 = '0';
              do {
                cout << "\n***2f) BT Left-Right Navigation***";                                                     /*Navigation with Left-Right*/
                if(c3!='4'){
                  cout << "\nWhat is your choice?\n1) Re-write Node\n2)Node->sx\n3)Node->dx\n4)None";
                  cin >> c3;
                }
                switch (c3) {
                  case '1':{
                    cout << "\nInsert: ";
                    cin >> y;
                    n->Element() = y;
                    y = 0;
                  }break;
                  case '2':{
                    if(n->HasLeftChild()) n = &(n->LeftChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '3':{
                    if(n->HasRightChild()) n = &(n->RightChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '4':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice...";
                  }break;
                }
              } while(c3!='4');
              do {
                cout << "\n***2f) BT iterator Navigation*** Pick your iterator:\nP. PreOrder\nI. InOrder\nO. PostOrder\nR. BreadthOrder\nB. Back\t";
                cin >> c3;
                switch (c3) {
                  case 'p':{
                    lasd::BTPreOrderIterator<float> i(bt);                                                              /*Navigation with iterator*/
                    do {
                      cout << "\n***2f) BT iterator Navigation***\n**PreOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'i':{
                    lasd::BTInOrderIterator<float> i(bt);
                    do {
                      cout << "\n***2f) BT iterator Navigation***\n**InOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'o':{
                    lasd::BTPostOrderIterator<float> i(bt);
                    do {
                      cout << "\n***2f) BT iterator Navigation***\n**PostOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'r':{
                    lasd::BTBreadthIterator<float> i(bt);
                    do {
                      cout << "\n***2f) BT iterator Navigation***\n**BreadthOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'b':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice . . .";
                  }break;
                }
              } while(c3!='b');
              cout << "\nVerify if an element exists in the binary tree: ";
              cin >> y;
              bt.Exists(y) ? cout << "\nThe element exists in the binary tree!" : cout << "\nThe element doesn't exist in the binary tree!";
              cout << "\nSum the elements of the tree greater than: ";
              cin >> y;
              bt.FoldPreOrder(Adding<float>, &y, &neuts);
              cout << "\nThe sum is: " << neuts;
              neuts = 0;
              cout << "\nCubed elements of the tree (PostOrder visit): ";
              bt.MapPreOrder(Cubed<float>, nullptr);
              bt.MapPostOrder(PrintElement<float>, nullptr);
              cout << "\nClearing the tree...";
              bt.Clear();
              cout << "\nAlberoVec in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<float>, nullptr);
            }break;
            case 's':{
              cout << "\nEnter vector size: ";
              cin >> s;
              lasd::Vector<string> vec(s);
              string rs = "";
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dist(0, chara.size());
              default_random_engine genl(random_device{}());
              uniform_int_distribution <int> distl(1, 10);
              for(uint i = 0; i < s; i++){
                l = distl(genl);
                for(uint j = 0; j < l; j++){
              		rs += chara[dist(gen)];
              	}
                vec[i] = rs;
                rs = "";
              }
              cout << "Linear Container (Vettore):" << endl;
              vec.MapPreOrder(PrintElement<string>, nullptr);
              lasd::BinaryTreeVec<string> bt(vec);
              cout << "\nAlberoVec in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<string>, nullptr);
              cout << "\nAlberoVec in PostOrder:" << endl;
              bt.MapPostOrder(PrintElement<string>, nullptr);
              cout << "\nAlberoVec in InOrder:" << endl;
              bt.MapInOrder(PrintElement<string>, nullptr);
              cout << "\nAlberoVec in BreadthOrder:" << endl;
              bt.MapBreadth(PrintElement<string>, nullptr);
              lasd::BinaryTree<string>::Node* n(&(bt.Root()));                             /*Navigation with Left-Right*/
              do {
                cout << "\n***2s) BT Left-Right Navigation***";
                if(c3!='4'){
                  cout << "\nWhat is your choice?\n1) Re-write Node\n2)Node->sx\n3)Node->dx\n4)None";
                  cin >> c3;
                }
                switch (c3) {
                  case '1':{
                    cout << "\nInsert: ";
                    cin >> sc;
                    n->Element() = sc;
                    sc = "";
                  }break;
                  case '2':{
                    if(n->HasLeftChild()) n = &(n->LeftChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '3':{
                    if(n->HasRightChild()) n = &(n->RightChild());
                    else{
                      cout << "\nReached an empty part of the three.";
                      c3 = '4';
                    }
                  }break;
                  case '4':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice...";
                  }break;
                }
              } while(c3!='4');
              do {
                cout << "\n***2s) BT iterator Navigation*** Pick your iterator:\nP. PreOrder\nI. InOrder\nO. PostOrder\nR. BreadthOrder\nB. Back\t";
                cin >> c3;
                switch (c3) {
                  case 'p':{
                    lasd::BTPreOrderIterator<string> i(bt);
                    do {
                      cout << "\n***1i) BT iterator Navigation***\n**PreOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'i':{
                    lasd::BTInOrderIterator<string> i(bt);
                    do {
                      cout << "\n***2s) BT iterator Navigation***\n**InOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'o':{
                    lasd::BTPostOrderIterator<string> i(bt);
                    do {
                      cout << "\n***2s) BT iterator Navigation***\n**PostOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'r':{
                    lasd::BTBreadthIterator<string> i(bt);
                    do {
                      cout << "\n***2s) BT iterator Navigation***\n**BreadthOrder iterator** Pick your choice:\nP. Print node element\nF. Go forward with your iterator\nB. Back\t";
                      cin >> c4;
                      switch (c4) {
                        case 'p':{
                          cout << endl << *i;
                        }break;
                        case 'f':{
                          ++i;
                        }break;
                        case 'b':{
                          cout << "\nBack . . .";
                        }break;
                        default:{
                          cout << "\nNot a choice . . .";
                        }break;
                      }
                    } while(c4!='b');
                  }break;
                  case 'b':{
                    cout << "\nBack . . .";
                  }break;
                  default:{
                    cout << "\nNot a choice . . .";
                  }break;
                }
              } while(c3!='b');
              cout << "\nVerify if an element exists in the binary tree: ";
              cin >> sc;
              bt.Exists(sc) ? cout << "\nThe element exists in the binary tree!" : cout << "\nThe element doesn't exist in the binary tree!";
              sc = "";
              cout << "\n-Pre Order- Concatenate string of the BT having less or equal length than: ";
              cin >> x;
              bt.FoldPreOrder(Concat<string>, &x, &sc);
              cout << "The concatenated string is: " << sc;
              sc = "";
              cout << "\n-Post Order- Concatenate string of the BT having less or equal length than: ";
              cin >> x;
              bt.FoldPostOrder(Concat<string>, &x, &sc);
              cout << "The concatenated string is: " << sc;
              sc = "";
              cout << "\n-In Order- Concatenate string of the BT having less or equal length than: ";
              cin >> x;
              bt.FoldInOrder(Concat<string>, &x, &sc);
              cout << "The concatenated string is: " << sc;
              sc = "";
              cout << "\n-Breadth Order- Concatenate string of the BT having less or equal length than: ";
              cin >> x;
              bt.FoldBreadth(Concat<string>, &x, &sc);
              cout << "The concatenated string is: " << sc;
              sc = "";
              cout << "\nInsert a string that will be pushed to every string: ";
              cin >> sc;
              bt.MapPreOrder(AddStr<string>, &sc);
              cout << "\nAlberoVec in InOrder:" << endl;
              bt.MapInOrder(PrintElement<string>, nullptr);
              cout << "\nClearing the tre...";
              bt.Clear();
              cout << "\nAlberoVec in PreOrder:" << endl;
              bt.MapPreOrder(PrintElement<string>, nullptr);
            }break;
            case 'b':{
              cout << "Back . . .\n";
            }break;
            default:{
              cout << "\nNot a choice...";
            }break;
          }
        } while(c2!='b');
      }break;
      case '3':{
        cout << "Exit . . ." << endl;
      }break;
      default:{
        cout << "\nNot a choice...";
      }break;
    }
  } while(c!='3');

}
