#include <iostream>
#include <random>
#include <string>
#include "test.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
using namespace std;

void mytest(){

  int c, ran, x, neuts = 0;              //structure choice, range, neutral sum
  float neutm = 1;                       //neutral multiply
  float y, ftf;                          //float to search
  ulong s;                               //size
  char ch, chl;                          //type choice, list op choice
  const string chara = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  string es = "";                        //empty string
	string rs, sts;                        //random string and string to search

  do{
    cout << "\nWelcome to the menu, take one of the number choices below:\n1. Vectors\n2. Lists\n3. Exit\n";
    cin >> c;
    switch(c){

      case 1:{

        do{

          cout << "\nWrite your letter choice:\n1)\ti. Build a new random int vector with a given integer size\n1)\tf. Build a new random float vector with a given integer size\n1)\ts. Build a new random string vector with a given integer size\n1)\tb. Back\n  \t";
          cin >> ch;

          switch(ch){

            case 'i':{
              cout << "Write your vector size: ";
              cin >> s;
              lasd::Vector<int> vec(s);
              cout << "Choose the range of generated numbers (from zero to): ";
              cin >> ran;
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dist(0, ran);
              for(uint i = 0; i < s; i++){
                vec[i] = dist(gen);
              }
              cout << "First item of the integer vector: " << vec.Front();            //Prints the first item of the vector.
              cout << "\nLast item of the integer vector: " << vec.Back();            //Prints the last item of the vector.
              cout << "\nFull items of the integer vector: ";
              vec.MapPreOrder(PrintItems<int>, nullptr);                              //Prints the vector.
              cout << "\nSpecificy which other n-th item of the vector you want to visualize: ";
              cin >> ran;
              cout << vec[ran-1];                                                     //Operand [].
              // /*                                                                      //Activate this to test:
              lasd::Vector<int> vecp(vec);                                            //Copy constructor.
              lasd::Vector<int> vec1(s);
              vec1 = vec;                                                             //Copy assignment.
              cout << endl << (vecp == vec);                                          //Operands "=" and "!=".
              for(uint i = 0; i < s; i++){
                vec1[i] = dist(gen);
              }
              cout << endl << (vec1 != vec);
              // */
              cout << "\nSearch a given value in the vector: ";
              cin >> ran;
              vec.Exists(ran) ? cout << "The value exists in the random vector!" : cout << "The value doesn't exist in the random vector!";
              cout << "\nSum the elements of the vector less than: ";
              cin >> ran;
              vec.FoldPreOrder(Adding<int>, &ran, &neuts);
              cout << "The sum is " << neuts << "!";
              neuts = 0;
              cout << "\nDoubled items of the integer vector: " << endl;
              vec.MapPreOrder(Doubled<int>, nullptr);
              vec.MapPreOrder(PrintItems<int>, nullptr);
              cout << "\nResize vector: ";
              cin >> ran;
              vec.Resize(ran);
              cout << "Vector resized: ";
              if(vec.Empty()) cout << "Empty vector";                                 //Emptiness test.
              else vec.MapPreOrder(PrintItems<int>, nullptr);
              cout << "\nCleared vector: ";
              vec.Clear();
              vec.MapPreOrder(PrintItems<int>, nullptr);
            }break;

            case 'f':{
              cout << "Write your vector size: ";
              cin >> s;
              lasd::Vector<float> vec(s);
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dis(0, 1000);
              for (uint i = 0; i < s; i++){
                vec[i] = (float)((float)dis(gen)/100);
              }
              cout << "\nFirst item of the float vector: " << vec.Front();
              cout << "\nLast item of the float vector: " << vec.Back();
              cout << "\nFull items of the integer vector: ";
              vec.MapPreOrder(PrintItems<float>, nullptr);
              cout << "\nSpecificy which other n-th item of the vector you want to visualize: ";
              cin >> ran;
              cout << vec[ran-1];
              cout << "\nSearch a given value in the vector: ";
              cin >> ftf;
              vec.Exists(ftf) ? cout << "The value exists in the random vector!" : cout << "The value doesn't exist in the random vector!";
              cout << "\nMultiply the elements of the vector greater than: ";
              cin >> ftf;
              vec.FoldPreOrder(Multiplying<float>, &ftf, &neutm);
              ((neutm==1) && !(vec.Exists(1))) ? cout << "There are no items greater than " << ftf << "!" : cout << "The multiplication is " << neutm;
              neutm = 1;
              cout << "\nSquared items of the float vector: " << endl;
              vec.MapPreOrder(Squared<float>, nullptr);
              vec.MapPreOrder(PrintItems<float>, nullptr);
              cout << "\nResize vector: ";
              cin >> ran;
              vec.Resize(ran);
              cout << "Vector resized: ";
              vec.MapPreOrder(PrintItems<float>, nullptr);
              cout << "\nCleared vector: ";
              vec.Clear();
              vec.MapPreOrder(PrintItems<float>, nullptr);
            }break;

            case 's':{
              cout << "Write your vector size: ";
              cin >> s;
              lasd::Vector<string> vec(s);
              default_random_engine gen(random_device{}());
            	uniform_int_distribution <int> dist(0, chara.size());
              default_random_engine genl(random_device{}());
            	uniform_int_distribution <int> distl(1, 10);
              for(uint i = 0; i < s; i++){
                int l = distl(genl);
                for(uint j = 0; j < l; j++){
              		rs += chara[dist(gen)];
              	}
                vec[i] = rs;
                rs = "";
              }
              cout << "\nFirst item of the string vector: " << vec.Front();
              cout << "\nLast item of the string vector: " << vec.Back();
              cout << "\nFull items of the integer vector: ";
              vec.MapPreOrder(PrintItems<string>, nullptr);
              cout << "\nSpecificy which other n-th item of the vector you want to visualize: ";
              cin >> ran;
              cout << vec[ran-1];
              cout << "\nSearch a given string in the vector (CASE SENSITIVE!): ";
              cin >> sts;
              vec.Exists(sts) ? cout << "The string exists in the random vector!\n" : cout << "The string doesn't exist in the random vector!\n";
              cout << "-PreOrder sort- Concatenate strings of the vector having less or equal length than: ";
              cin >> ran;
              vec.FoldPreOrder(Concat<string>, &ran, &es);
              cout << es << endl;
              es = "";
              cout << "-PostOrder sort- Concatenate strings of the vector having less or equal length than: ";
              cin >> ran;
              vec.FoldPostOrder(Concat<string>, &ran, &es);
              cout << es;
              es = "";
              cout << "\nTo upper-ed strings: ";
              vec.MapPreOrder(UpperCased<string>, nullptr);
              vec.MapPreOrder(PrintItems<string>, nullptr);
              cout << "\nResize vector: ";
              cin >> ran;
              vec.Resize(ran);
              cout << "Vector resized: ";
              vec.MapPreOrder(PrintItems<string>, nullptr);
              cout << "\nCleared vector: ";
              vec.Clear();
              vec.MapPreOrder(PrintItems<string>, nullptr);
              cout << endl;
            }break;

            case 'b':{
              cout << "Back...";
            }break;

            default:{
              cout << "Not a choice...";
            }
          }

        }while(ch!='b');

      }break;

      case 2:{

        do{

          cout << "\nWrite your letter choice:\n2)\ti. Build a new random int list\n2)\tf. Build a new random float list\n2)\ts. Build a new random string list\n2)\tb. Back\n  \t";
          cin >> ch;

          switch (ch){

            case 'i':{
              lasd::List<int> list{};
              list.Empty() ? cout << "Empty\n" : cout << "Not empty\n";                         //Emptiness test.
              cout << "Choose the range of random generated numbers (from zero to): ";
              cin >> ran;
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dis(0, ran);
              do {

                cout << "\nWhat is your next operation?\n2i)\tp. Push a random integer\n2i)\ta. Append a random integer\n2i)\tr. Remove from front\n2i)\tf. Front and Remove\n2i)\tb. Back\n  \t";
                cin >> chl;

                switch (chl){

                  case 'p':{
                    x = dis(gen);
                    list.InsertAtFront(x);
                    cout << "Pushed " << x << ".";
                  }break;

                  case 'a':{
                    x = dis(gen);
                    list.InsertAtBack(x);
                    cout << "Appended " << x << ".";
                  }break;

                  case 'r':{
                    list.RemoveFromFront();
                  }break;

                  case 'f':{
                    cout << "Removed " << list.FrontNRemove();
                  }break;

                  case 'b':{
                    list.Empty() ? cout << "Empty\n" : cout << "Not empty\n";                         //Emptiness test.
                    cout << "\nFront of the list is: ";
                    cout << list.Front();
                    cout << "\nBack of the list is: ";
                    cout << list.Back();
                    cout << "\nFinal list obtained: ";
                    list.MapPreOrder(PrintItems<int>, nullptr);                                       //Prints the list.
                    cout << "\nSpecificy which other n-th item of the list you want to visualize: ";
                    cin >> ran;
                    cout << list[ran-1];
                    cout << "\nSearch a given value in the list: ";
                    cin >> ran;
                    list.Exists(ran) ? cout << "The value exist in the list!" : cout << "The value doesn't exist in the list!";
                    cout << "\nSum the elements of the list less than: ";
                    cin >> ran;
                    list.FoldPreOrder(Adding<int>, &ran, &neuts);
                    cout << "The sum is " << neuts << "!";
                    neuts = 0;
                    cout << "\nDoubled items of the list: " << endl;
                    list.MapPreOrder(Doubled<int>, nullptr);
                    list.MapPreOrder(PrintItems<int>, nullptr);
                    cout << "\nCleared list: ";
                    list.Clear();
                    list.MapPreOrder(PrintItems<int>, nullptr);
                    /*                                                                       //Activate this to test the constructor of a list obtained by a LinearContainer.
                    lasd::Vector<int> vec(5);
                    uniform_int_distribution <int> dis1(0, 1000);
                    default_random_engine gen1(random_device{}());
                    for (uint i = 0; i < 5; i++){
                      vec[i] = dis1(gen1);
                    }
                    cout << "\nVector: ";
                    vec.MapPreOrder(PrintItems<int>, nullptr);
                    lasd::List<int> list1(vec);
                    cout << "\nList list1: ";
                    list1.MapPreOrder(PrintItems<int>, nullptr);
                    */
                    /*                                                                         //Activate this to test the copy constructor.
                    lasd::List<int> l1(list1);
                    cout << "\nList l1: ";
                    l1.MapPreOrder(PrintItems<int>, nullptr);
                    */
                    /*                                                                         //Activate this to test the copy assignment.
                    lasd::List<int> l2 = list1;
                    cout << "\nList l2: ";                                                     //Operands "==", "!=".
                    l2.MapPreOrder(PrintItems<int>, nullptr);
                    list1 == l2 ? cout << "\nThe two lists are equal." : cout << "\nThe two lists are different.";
                    l2.InsertAtFront(0);
                    cout << "\nInsert 0 at the front of l2: ";
                    l2.MapPreOrder(PrintItems<int>, nullptr);
                    list1 != l2 ? cout << "\nThe two lists are different." : cout << "\nThe two lists are equal.";
                    */
                    cout << "\nBack...";
                  }break;

                  default:{
                    cout << "Not a choice...";
                  }
                }

              } while(chl!='b');

            }break;

            case 'f':{
              lasd::List<float> list{};
              default_random_engine gen(random_device{}());
              uniform_int_distribution <int> dis(0, 1000);
              do {

                cout << "\nWhat is your next operation?\n2i)\tp. Push a random float\n2i)\ta. Append a random float\n2i)\tr. Remove from front\n2i)\tf. Front and Remove\n2i)\tb. Back\n  \t";
                cin >> chl;

                switch (chl){

                  case 'p':{
                    y = (float)((float)dis(gen)/100);
                    list.InsertAtFront(y);
                    cout << "Pushed " << y << ".";
                  }break;

                  case 'a':{
                    y = (float)((float)dis(gen)/100);
                    list.InsertAtBack(y);
                    cout << "Appended " << y << ".";
                  }break;

                  case 'r':{
                    list.RemoveFromFront();
                  }break;

                  case 'f':{
                    cout << "Removed " << list.FrontNRemove();
                  }break;

                  case 'b':{
                    cout << "\nFront of the list is: ";
                    cout << list.Front();
                    cout << "\nBack of the list is: ";
                    cout << list.Back();
                    cout << "\nFinal list obtained: ";
                    list.MapPreOrder(PrintItems<float>, nullptr);
                    cout << "\nSpecificy which other n-th item of the list you want to visualize: ";
                    cin >> ran;
                    cout << list[ran-1];
                    cout << "\nSearch a given value in the list: ";
                    cin >> ftf;
                    list.Exists(ftf) ? cout << "The value exists in the list!" : cout << "The value doesn't exist in the list!";
                    cout << "\nMultiply the elements of the list greater than: ";
                    cin >> ftf;
                    list.FoldPreOrder(Multiplying<float>, &ftf, &neutm);
                    ((neutm==1) && !(list.Exists(1))) ? cout << "There are no items greater than " << ftf << "!" : cout << "The multiplication is " << neutm;
                    neutm = 1;
                    cout << "\nSquared items of the float list: ";
                    list.MapPreOrder(Squared<float>, nullptr);
                    list.MapPreOrder(PrintItems<float>, nullptr);
                    cout << "\nList cleared: ";
                    list.Clear();
                    list.MapPreOrder(PrintItems<float>, nullptr);
                    cout << "\nBack...";
                  }break;

                  default:{
                    cout << "Not a choice...";
                  }
                }

              } while(chl!='b');

            }break;

            case 's':{
              lasd::List<string> list{};
              default_random_engine gen(random_device{}());
            	uniform_int_distribution <int> dist(0, chara.size());
              default_random_engine genl(random_device{}());
            	uniform_int_distribution <int> distl(1, 10);
              do {

                cout << "\nWhat is your next operation?\n2i)\tp. Push a random string\n2i)\ta. Append a random string\n2i)\tr. Remove from front\n2i)\tf. Front and Remove\n2i)\tb. Back\n  \t";
                cin >> chl;
                int l;
                switch (chl){

                  case 'p':{
                      l = distl(genl);
                      for(uint j = 0; j < l; j++){
                    		rs += chara[dist(gen)];
                    	}
                      list.InsertAtFront(rs);
                    cout << "Pushed " << rs << ".";
                    rs = "";
                  }break;

                  case 'a':{
                      l = distl(genl);
                      for(uint j = 0; j < l; j++){
                    		rs += chara[dist(gen)];
                    	}
                      list.InsertAtBack(rs);
                    cout << "Appended " << rs << ".";
                    rs = "";
                  }break;

                  case 'r':{
                    list.RemoveFromFront();
                  }break;

                  case 'f':{
                    cout << "Removed " << list.FrontNRemove();
                  }break;

                  case 'b':{
                    cout << "\nFront of the list is: ";
                    cout << list.Front();
                    cout << "\nBack of the list is: ";
                    cout << list.Back();
                    cout << "\nFinal list obtained: ";
                    list.MapPreOrder(PrintItems<string>, nullptr);
                    cout << "\nSpecificy which other n-th item of the list you want to visualize: ";
                    cin >> ran;
                    cout << list[ran-1];
                    cout << "\nSearch a given string in the vector (CASE SENSITIVE!): ";
                    cin >> sts;
                    list.Exists(sts) ? cout << "The string exists in the random list!\n" : cout << "The string doesn't exist in the random list!\n";
                    cout << "-PreOrder sort- Concatenate strings of the vector having less or equal length than: ";
                    cin >> ran;
                    list.FoldPreOrder(Concat<string>, &ran, &es);
                    cout << es;
                    es = "";
                    cout << "\n-PostOrder sort- Concatenate strings of the vector having less or equal length than: ";
                    cin >> ran;
                    list.FoldPostOrder(Concat<string>, &ran, &es);
                    cout << es;
                    es = "";
                    cout << "\nTo upper-ed strings: ";
                    list.MapPreOrder(UpperCased<string>, nullptr);
                    list.MapPreOrder(PrintItems<string>, nullptr);
                    cout << "\nList cleared: ";
                    list.Clear();
                    list.MapPreOrder(PrintItems<string>, nullptr);
                    cout << "\nBack...";
                  }break;

                  default:{
                    cout << "Not a choice...";
                  }
                }

              } while(chl!='b');

            }break;

            case 'b':{
              cout << "Back...";
            }break;

            default:{
              cout << "\nNot a choice...";
            }
          }

        } while(ch!='b');

      }break;

      case 3:{
        cout << "\n\t\tExit...\n";
        break;
        // exit(0);
      }

      default:{
        cout << "Not a choice...";
        break;
      }

    }

  }while(c!=3);

}

// Aux to print vector by MapFunction.
template <typename Data>
void PrintItems(Data& x, void* p){
  cout << x << " ";
}

// Auxiliarities functions for FoldFunction.
template <typename Data>
void Adding(const Data& x, const void* par, void* acc){
  if(x < *((int*)par)) *((int*)acc) = *((int*)acc) + x;
}

template <typename Data>
void Multiplying(const Data& x, const void* par, void* acc){
  if(x > *((float*)par)) *((float*)acc) = *((float*)acc)*x;
}

template <typename Data>
void Concat(const Data& s, const void* par, void* sc){
  if (*((int*)(par)) >= s.size()) *((string*)sc) += s;            //stringname.size() is an #include<string> function
}

// Auxiliarities functions for MapFunctions.
template <typename Data>
inline void Doubled(Data& x, void* p){
  x = 2 * x;
}

template <typename Data>
inline void Squared(Data& x, void* p){
  x = x * x;
}

template <typename Data>
void UpperCased(Data& s, void* p){
  for(uint i = 0; i < s.size(); i++){
    s[i] = toupper(s[i]);
  }
}
