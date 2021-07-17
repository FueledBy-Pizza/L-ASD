#include <iostream>
#include <string>
#include <random>
#include "../bst/bst.hpp"
using namespace std;

// Aux to print bst by MapFunction.
template <typename Data>
void PrintItems(Data& x, void* p){
  cout << x << " ";
}

// Auxiliarities functions for FoldFunction.
template <typename Data>
void Adding(const Data& x, const void* par, void* acc){
  if(x > *((float*)par)) *((float*)acc) = *((float*)acc) + x;
}

template <typename Data>
void Multiplying(const Data& x, const void* par, void* acc){
  if(x < *((int*)par)) *((int*)acc) = *((int*)acc) * x;
}

template <typename Data>
void Concat(const Data& s, const void* par, void* sc){
  if (*((int*)(par)) >= s.size()) *((string*)sc) += s;            //stringname.size() is an #include<string> function
}

void mytest(){

  char c, co;         // bst type choice, bst operation choice
  int sz;             // bst size choosen by user

  int x = 0;          // integer to insert/delete
  int neutm = 1;      // neutral multiply

  float y = 0;        // float to insert/delete
  float neuts = 0;    // neutral sum

  const string chara = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  string s = "";      // string to insert/delete
  string str = "";    // string to fill

  cout << endl << "Pick a choice:\n1. Build a random integer BST\n2. Build a random float BST\n3. Build a random string BST\n4. Exit\n\t";
  cin >> c;
  switch (c) {
    case '1':{
      cout << endl << "Choose BST size: ";
      cin >> sz;
      lasd::List<int> l{};
      default_random_engine gen(random_device{}());
      uniform_int_distribution <int> dist(0, 100);
      for(ulong i = 0; i < sz; i++){
        l.InsertAtBack(dist(gen));
      }
      cout << "BST creating from list: ";
      l.MapPreOrder(PrintItems<int>, nullptr);
      lasd::BST<int> bst(l);
      cout << endl;
      cout << "Bst in PreOrder: ";
      bst.MapPreOrder(PrintItems<int>, nullptr);
      cout << endl;
      cout << "Bst in Postrder: ";
      bst.MapPostOrder(PrintItems<int>, nullptr);
      cout << endl;
      cout << "Bst in InOrder: ";
      bst.MapInOrder(PrintItems<int>, nullptr);
      cout << endl;
      cout << "Bst in BreadthOrder: ";
      bst.MapBreadth(PrintItems<int>, nullptr);
      cout << endl << endl << "What operation do you want to do?\na. Insert a node\nb. Delete a node\nc. Read min\nd. Read max\ne. Remove min\nf. Remove max\ng. Read and remove min\nh. Read and remove max\ni. Find predecessor of\nj. Find successor of\nk. Remove predecessor of\nl. Remove successor of\nm. Read and remove predecessor of\nn. Read and remove successor of\n\t";
      cin >> co;
      switch (co) {
        case 'a':{
          cout << endl << "Element you want to insert: ";
          cin >> x;
          bst.Insert(x);
        }break;
        case 'b':{
          cout << endl << "Element you want to delete: ";
          cin >> x;
          bst.Remove(x);
        }break;
        case 'c':{
          cout << endl << "Min of the tree is: " << bst.Min() << ".";
        }break;
        case 'd':{
          cout << endl << "Max of the tree is: " << bst.Max() << ".";
        }break;
        case 'e':{
          bst.RemoveMin();
          cout << endl << "Min removed.";
        }break;
        case 'f':{
          bst.RemoveMax();
          cout << endl << "Max removed.";
        }break;
        case 'g':{
          cout << endl << "Min removed: " << bst.MinNRemove() << ".";
        }break;
        case 'h':{
          cout << endl << "Max removed: " << bst.MaxNRemove() << ".";
        }break;
        case 'i':{
          cout << endl << "Element you want to find predecessor of: ";
          cin >> x;
          cout << "Predecessor of " << x << " is " << bst.Predecessor(x) << ".";
        }break;
        case 'j':{
          cout << endl << "Element you want to find successor of: ";
          cin >> x;
          cout << "Successor of " << x << " is " << bst.Successor(x) << ".";
        }break;
        case 'k':{
          cout << endl << "Element you want to delete predecessor of: ";
          cin >> x;
          bst.RemovePredecessor(x);
          cout << "Removed predecessor of " << x << ".";
        }break;
        case 'l':{
          cout << endl << "Element you want to delete successor of: ";
          cin >> x;
          bst.RemoveSuccessor(x);
          cout << "Removed successor of " << x << ".";
        }break;
        case 'm':{
          cout << endl << "Element you want to delete predecessor of: ";
          cin >> x;
          cout << "Removed " << bst.PredecessorNRemove(x) << ", predecessor of " << x << ".";
        }break;
        case 'n':{
          cout << endl << "Element you want to delete successor of: ";
          cin >> x;
          cout << "Removed " << bst.SuccessorNRemove(x) << ", successor of " << x << ".";
        }break;
        default:{
          cout << endl << "Not a choice...";
        }break;
      }
      cout << endl;
      cout << "Bst in InOrder: ";
      bst.MapInOrder(PrintItems<int>, nullptr);
      cout << endl << "Multiply ints < of: ";
      cin >> x;
      bst.FoldInOrder(Multiplying<int>, &x, &neutm);
      ((x>0) && (bst.Exists(0))) ? cout << "Result is 0." : cout << "Result is: " << neutm << ".";
    }break;
    case '2':{
      cout << endl << "Choose BST size: ";
      cin >> sz;
      lasd::List<float> l{};
      default_random_engine gen(random_device{}());
      uniform_int_distribution <int> dist(0, 100);
      for(ulong i = 0; i < sz; i++){
        y = (float)dist(gen)/10;
        l.InsertAtBack(y);
      }
      cout << "BST creating from list: ";
      l.MapPreOrder(PrintItems<float>, nullptr);
      lasd::BST<float> bst(l);
      cout << endl;
      cout << "Bst in PreOrder: ";
      bst.MapPreOrder(PrintItems<float>, nullptr);
      cout << endl;
      cout << "Bst in Postrder: ";
      bst.MapPostOrder(PrintItems<float>, nullptr);
      cout << endl;
      cout << "Bst in InOrder: ";
      bst.MapInOrder(PrintItems<float>, nullptr);
      cout << endl;
      cout << "Bst in BreadthOrder: ";
      bst.MapBreadth(PrintItems<float>, nullptr);
      cout << endl << endl << "What operation do you want to do?\na. Insert a node\nb. Delete a node\nc. Read min\nd. Read max\ne. Remove min\nf. Remove max\ng. Read and remove min\nh. Read and remove max\ni. Find predecessor of\nj. Find successor of\nk. Remove predecessor of\nl. Remove successor of\nm. Read and remove predecessor of\nn. Read and remove successor of\n\t";
      cin >> co;
      switch (co) {
        case 'a':{
          cout << endl << "Element you want to insert: ";
          cin >> y;
          bst.Insert(y);
        }break;
        case 'b':{
          cout << endl << "Element you want to delete: ";
          cin >> y;
          bst.Remove(y);
        }break;
        case 'c':{
          cout << endl << "Min of the tree is: " << bst.Min() << ".";
        }break;
        case 'd':{
          cout << endl << "Max of the tree is: " << bst.Max() << ".";
        }break;
        case 'e':{
          bst.RemoveMin();
          cout << endl << "Min removed.";
        }break;
        case 'f':{
          bst.RemoveMax();
          cout << endl << "Max removed.";
        }break;
        case 'g':{
          cout << endl << "Min removed: " << bst.MinNRemove() << ".";
        }break;
        case 'h':{
          cout << endl << "Max removed: " << bst.MaxNRemove() << ".";
        }break;
        case 'i':{
          cout << endl << "Element you want to find predecessor of: ";
          cin >> y;
          cout << "Predecessor of " << y << " is " << bst.Predecessor(y) << ".";
        }break;
        case 'j':{
          cout << endl << "Element you want to find successor of: ";
          cin >> y;
          cout << "Successor of " << y << " is " << bst.Successor(y) << ".";
        }break;
        case 'k':{
          cout << endl << "Element you want to delete predecessor of: ";
          cin >> y;
          bst.RemovePredecessor(y);
          cout << "Removed predecessor of " << y << ".";
        }break;
        case 'l':{
          cout << endl << "Element you want to delete successor of: ";
          cin >> y;
          bst.RemoveSuccessor(y);
          cout << "Removed successor of " << y << ".";
        }break;
        case 'm':{
          cout << endl << "Element you want to delete predecessor of: ";
          cin >> y;
          cout << "Removed " << bst.PredecessorNRemove(y) << ", predecessor of " << y << ".";
        }break;
        case 'n':{
          cout << endl << "Element you want to delete successor of: ";
          cin >> y;
          cout << "Removed " << bst.SuccessorNRemove(y) << ", successor of " << y << ".";
        }break;
        default:{
          cout << endl << "Not a choice...";
        }break;
      }
      cout << endl;
      cout << "Bst in InOrder: ";
      bst.MapInOrder(PrintItems<float>, nullptr);
      cout << endl << "Add floats > of: ";
      cin >> y;
      bst.FoldInOrder(Adding<float>, &y, &neuts);
      cout << "Result is: " << neuts << ".";
    }break;
    case '3':{
      cout << endl << "Choose BST size: ";
      cin >> sz;
      lasd::List<string> l{};
      default_random_engine gen(random_device{}());
      uniform_int_distribution <int> dist(0, chara.size());
      default_random_engine genl(random_device{}());
      uniform_int_distribution <int> distl(1, 10);
      uint len = 0;
      for(ulong i = 0; i < sz; i++){
        len = distl(genl);
        for(ulong j = 0; j < len; j++){
          s += chara[dist(gen)];
        }
        l.InsertAtBack(s);
        s = "";
      }
      cout << "BST creating from list: ";
      l.MapPreOrder(PrintItems<string>, nullptr);
      lasd::BST<string> bst(l);
      cout << endl;
      cout << "Bst in PreOrder: ";
      bst.MapPreOrder(PrintItems<string>, nullptr);
      cout << endl;
      cout << "Bst in Postrder: ";
      bst.MapPostOrder(PrintItems<string>, nullptr);
      cout << endl;
      cout << "Bst in InOrder: ";
      bst.MapInOrder(PrintItems<string>, nullptr);
      cout << endl;
      cout << "Bst in BreadthOrder: ";
      bst.MapBreadth(PrintItems<string>, nullptr);
      cout << endl << endl << "What operation do you want to do?\na. Insert a node\nb. Delete a node\nc. Read min\nd. Read max\ne. Remove min\nf. Remove max\ng. Read and remove min\nh. Read and remove max\ni. Find predecessor of\nj. Find successor of\nk. Remove predecessor of\nl. Remove successor of\nm. Read and remove predecessor of\nn. Read and remove successor of\n\t";
      cin >> co;
      switch (co) {
        case 'a':{
          cout << endl << "Element you want to insert: ";
          cin >> s;
          bst.Insert(s);
        }break;
        case 'b':{
          cout << endl << "Element you want to delete: ";
          cin >> s;
          bst.Remove(s);
        }break;
        case 'c':{
          cout << endl << "Min of the tree is: " << bst.Min() << ".";
        }break;
        case 'd':{
          cout << endl << "Max of the tree is: " << bst.Max() << ".";
        }break;
        case 'e':{
          bst.RemoveMin();
          cout << endl << "Min removed.";
        }break;
        case 'f':{
          bst.RemoveMax();
          cout << endl << "Max removed.";
        }break;
        case 'g':{
          cout << endl << "Min removed: " << bst.MinNRemove() << ".";
        }break;
        case 'h':{
          cout << endl << "Max removed: " << bst.MaxNRemove() << ".";
        }break;
        case 'i':{
          cout << endl << "Element you want to find predecessor of: ";
          cin >> s;
          cout << "Predecessor of " << s << " is " << bst.Predecessor(s) << ".";
        }break;
        case 'j':{
          cout << endl << "Element you want to find successor of: ";
          cin >> s;
          cout << "Successor of " << s << " is " << bst.Successor(s) << ".";
        }break;
        case 'k':{
          cout << endl << "Element you want to delete predecessor of: ";
          cin >> s;
          bst.RemovePredecessor(s);
          cout << "Removed predecessor of " << s << ".";
        }break;
        case 'l':{
          cout << endl << "Element you want to delete successor of: ";
          cin >> s;
          bst.RemoveSuccessor(s);
          cout << "Removed successor of " << s << ".";
        }break;
        case 'm':{
          cout << endl << "Element you want to delete predecessor of: ";
          cin >> s;
          cout << "Removed " << bst.PredecessorNRemove(s) << ", predecessor of " << s << ".";
        }break;
        case 'n':{
          cout << endl << "Element you want to delete successor of: ";
          cin >> s;
          cout << "Removed " << bst.SuccessorNRemove(s) << ", successor of " << s << ".";
        }break;
        default:{
          cout << endl << "Not a choice...";
        }break;
      }
      cout << endl;
      cout << "Bst in InOrder: ";
      bst.MapInOrder(PrintItems<string>, nullptr);
      cout << endl << "Concatenate strings with length <= of: ";
      cin >> x;
      bst.FoldInOrder(Concat<string>, &x, &str);
      cout << "Result is: " << str << ".";
    }break;
    case '4':{
      cout << endl << "Exit . . ." << endl;
    }break;
    default :{
      cout << endl << "Not a choice...";
    }break;
  }
}
