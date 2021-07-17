#include <iostream>
#include <random>
#include <string>
#include "test.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/vec/queuevec.hpp"
using namespace std;

void mytest(){

  char c;  //structure choice
  char ch;  //vec\list choice
  char cht; //type choice
  char chop;  //op choice
  const string chara = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  string rs = "";

  do {

    cout << "\nWelcome to the menu, take one of the number choices below:\n1. Stack\n2. Queue\n3. Exit\n  \t";
    cin >> c;

    switch (c) {
      case '1':{

        do {

          cout << "\nWhich stack-model?\n1)\tl. Stack list\n1)\tv. Stack vector\n1)\tb. Back\n  \t";
          cin >> ch;
          switch (ch) {
            case 'l':{
              do {

                cout << "\nWhich Stack list type?\n1l)\t\ti. Int\n1l)\t\tf. Float\n1l)\t\ts. String\n1l)\t\tb. Back\n   \t";
                cin >> cht;
                switch (cht) {
                  case 'i':{
                    lasd::StackLst<int> sl{};
                    sl.Empty() ? cout << "Empty stack" : cout << "Not empty stack";               //Emptiness test.
                    default_random_engine gen(random_device{}());
                    uniform_int_distribution <int> dist(0, 100);
                    do {
                      cout << "\nWhat is your next operation?\n1li)\t\t\tp. Push a random int\n1li)\t\t\tt. Top\n1li)\t\t\to. Pop\n1li)\t\t\tn. TopNPop\n1li)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'p':{
                          int x = dist(gen);
                          sl.Push(x);
                          cout << "\nPushed " << x << ".";
                        }break;
                        case 't':{
                          if(sl.Size()!=0) cout << "\nTop of the stack: " << sl.Top();
                          else cout << "Stack is empty!";
                        }break;
                        case 'o':{
                          sl.Pop();
                          cout << "Popped.";
                        }break;
                        case 'n':{
                          cout << "Popped item of the stack: " << sl.TopNPop() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        // case 'r':{                           //Per testare costruttori
                        //   cout << "paperellar";
                          // lasd::StackLst<int> sl2(sl);
                          // lasd::StackLst<int> sl2 = sl;
                        //   lasd::StackLst<int> sl2(std::move(sl));
                        //   // lasd::StackLst<int> sl2 = std::move(sl);
                        //   sl2 != sl ? cout << "diversi" : cout << "uguali";
                        //   (sl2.Size()==0) ? cout << "\nsl2 is empty!" : cout << endl << sl2.Top();
                        //   if(sl2.Size()==0) cout << "\nsl2 is empty!";
                        //   else sl2.Pop();
                        //   if(sl2.Size()==0) cout << "\nsl2 is empty!";
                        //   else cout << "\nPopped " << sl2.TopNPop();
                        //   if(sl2.Size()!=0) cout << endl << sl2.Top();
                        //   else cout << "\nStack is empty!";
                        //   sl2.Push(4);
                        //   cout << endl << sl2.Top();
                        //   (sl.Size()==0) ? cout << "\nsl is empty!" : cout << endl << sl.Top();
                        //   // sl.Push(2);
                        //   // (sl.Size()==0) ? cout << "\nsl is empty!" : cout << endl << sl.Top();
                        // }break;
                        default:{
                          cout << "\nNot a choice...";
                        }break;
                      }
                    } while(chop!='b');
                  }break;

                  case 'f':{
                    lasd::StackLst<float> sl{};
                    default_random_engine gen(random_device{}());
                    uniform_int_distribution <int> dist(0, 100);
                    do {
                      cout << "\nWhat is your next operation?\n1lf)\t\t\tp. Push a random float\n1lf)\t\t\tt. Top\n1lf)\t\t\to. Pop\n1lf)\t\t\tn. TopNPop\n1lf)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'p':{
                          float x = ((float)dist(gen)/10);
                          sl.Push(x);
                          cout << "\nPushed " << x << ".";
                        }break;
                        case 't':{
                          if(sl.Size()!=0) cout << "\nTop of the stack: " << sl.Top();
                          else cout << "\nStack is empty!";
                        }break;
                        case 'o':{
                          sl.Pop();
                          cout << "Popped.";
                        }break;
                        case 'n':{
                          cout << "Popped item of the stack: " << sl.TopNPop() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }
                      }
                    } while(chop!='b');
                  }break;

                  case 's':{
                    lasd::StackLst<string> sl{};
                    default_random_engine gen(random_device{}());
            	      uniform_int_distribution <int> dist(0, chara.size());
                    default_random_engine genl(random_device{}());
            	      uniform_int_distribution <int> distl(1, 10);
                    do {
                      cout << "\nWhat is your next operation?\n1ls)\t\t\tp. Push a random string\n1ls)\t\t\tt. Top\n1ls)\t\t\to. Pop\n1ls)\t\t\tn. TopNPop\n1ls)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'p':{
                          int len = distl(genl);
                          for(uint j = 0; j < len; j++){
                            rs += chara[dist(gen)];
                          }
                          sl.Push(rs);
                          cout << "Pushed " << rs << ".";
                          rs = "";
                        }break;
                        case 't':{
                          if(sl.Size()!=0) cout << "\nTop of the stack: " << sl.Top();
                          else cout << "\nStack is empty!";
                        }break;
                        case 'o':{
                          sl.Pop();
                          cout << "Popped.";
                        }break;
                        case 'n':{
                          cout << "Popped item of the stack: " << sl.TopNPop() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }
                      }
                    } while(chop!='b');
                  }break;

                  case 'b':{
                    cout << "Back...";
                  }break;

                  default:{
                    cout << "Not a choice...";
                  }break;
                }
              } while(cht!='b');
            }break;

            case 'v':{
              do {

                cout << "\nWhich Stack vector type?\n1v)\t\ti. Int\n1v)\t\tf. Float\n1v)\t\ts. String\n1v)\t\tb. Back\n   \t";
                cin >> cht;
                switch (cht) {
                  case 'i':{
                    lasd::StackVec<int> sv{};
                    cout << endl << sv.Size();
                    default_random_engine gen(random_device{}());
                    uniform_int_distribution <int> dist(0, 100);
                    do {
                      cout << "\nWhat is your next operation?\n1vi)\t\t\tp. Push a random int\n1vi)\t\t\tt. Top\n1vi)\t\t\to. Pop\n1vi)\t\t\tn. TopNPop\n1vi)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'p':{
                          int x = dist(gen);
                          sv.Push(x);
                          cout << "\nPushed " << x << ".";
                        }break;
                        case 't':{
                          sv.Empty() ? cout << "\nStackVec is empty" : cout << "Top of the stack is " << sv.Top();
                        }break;
                        case 'o':{
                          sv.Pop();
                          cout << "Popped.";
                        }break;
                        case 'n':{
                          cout << "Popped item of the stack: " << sv.TopNPop() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        case 'r':{                           //Per testare costruttori
                          sv.Empty() ? cout << "\nStackVec is empty" : cout << "\nStackVec is not empty";     //Emptiness test.
                          cout << "\nStackVec size is " << sv.Size();
                          // sv.Clear();
                          char k;
                          lasd::Vector<int> vec(3);
                          default_random_engine genv(random_device{}());
                          uniform_int_distribution <int> distv(0, 10);
                          for(uint i = 0; i < vec.Size(); i++){
                            int o = distv(gen);
                            vec[i] = o;
                            cout << "\ninserito " << o;
                          }
                          lasd::StackVec<int> sv2(vec);
                          do {
                            cout << "\nScegli cosa fare con sv2:\n";
                            cin >> k;
                            switch (k) {
                              case 'p':{
                                int x = dist(gen);
                                sv2.Push(x);
                                cout << "\nPushed " << x << ".";
                              }break;
                              case 't':{
                                cout << "\nTop of the stack is " << sv2.Top();
                              }break;
                              case 'o':{
                                sv2.Pop();
                                cout << "Popped.";
                              }break;
                              case 'n':{
                                cout << "Popped item of the stack: " << sv2.TopNPop() << ".";
                              }break;
                              case 'b':{
                                cout << "Back...";
                              }break;
                              default:{
                                cout << "\nNot a choice...";
                              }
                            }
                          } while(k!='b');
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }break;
                      }
                    } while(chop!='b');
                  }break;

                  case 'f':{
                    lasd::StackVec<float> sv;
                    default_random_engine gen(random_device{}());
                    uniform_int_distribution <int> dist(0, 100);
                    do {
                      cout << "\nWhat is your next operation?\n1vf)\t\t\tp. Push a random float\n1vf)\t\t\tt. Top\n1vf)\t\t\to. Pop\n1vf)\t\t\tn. TopNPop\n1vf)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'p':{
                          float x = ((float)dist(gen)/10);
                          sv.Push(x);
                          cout << "\nPushed " << x << ".";
                        }break;
                        case 't':{
                          sv.Empty() ? cout << "\nStackVec is empty" : cout << "Top of the stack is " << sv.Top();
                        }break;
                        case 'o':{
                          sv.Pop();
                          cout << "Popped.";
                        }break;
                        case 'n':{
                          cout << "Popped item of the stack: " << sv.TopNPop() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        // case 'r':{
                        //   lasd::List<float> list{};
                        //   float y;
                        //   for(int j=0; j<2; j++){
                        //     y = ((float)dist(gen)/10);
                        //     list.InsertAtBack(y);
                        //     cout << "\nPushed " << y << " in the list.";
                        //   }
                        //   lasd::StackVec<float> sv2(list);        //per provare costruttore linearcontainer con una lista...
                        //   char k;
                        //   do {
                        //     cout << "\nScegli cosa fare con sv2:\n";
                        //     cin >> k;
                        //     switch (k) {
                        //       case 'p':{
                        //         int y2 = ((float)dist(gen)/10);
                        //         sv2.Push(y2);
                        //         cout << "\nPushed " << y2 << ".";
                        //       }break;
                        //       case 't':{
                        //         cout << "\nTop of the stack is " << sv2.Top();
                        //       }break;
                        //       case 'o':{
                        //         sv2.Pop();
                        //         cout << "Popped.";
                        //       }break;
                        //       case 'n':{
                        //         cout << "Popped item of the stack: " << sv2.TopNPop() << ".";
                        //       }break;
                        //       case 'b':{
                        //         cout << "Back...";
                        //       }break;
                        //       default:{
                        //         cout << "\nNot a choice...";
                        //       }
                        //     }
                        //   } while(k!='b');
                        // }break;
                        default:{
                          cout << "\nNot a choice...";
                        }
                      }
                    } while(chop!='b');
                  }break;

                  case 's':{
                    lasd::StackVec<string> sv;
                    default_random_engine gen(random_device{}());
            	      uniform_int_distribution <int> dist(0, chara.size());
                    default_random_engine genl(random_device{}());
            	      uniform_int_distribution <int> distl(1, 10);
                    do {
                      cout << "\nWhat is your next operation?\n1vs)\t\t\tp. Push a random string\n1vs)\t\t\tt. Top\n1vs)\t\t\to. Pop\n1vs)\t\t\tn. TopNPop\n1vs)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'p':{
                          int len = distl(genl);
                          for(uint j = 0; j < len; j++){
                            rs += chara[dist(gen)];
                          }
                          sv.Push(rs);
                          cout << "Pushed " << rs << ".";
                          rs = "";
                        }break;
                        case 't':{
                          sv.Empty() ? cout << "\nStackVec is empty" : cout << "Top of the stack is " << sv.Top();
                        }break;
                        case 'o':{
                          sv.Pop();
                          cout << "Popped.";
                        }break;
                        case 'n':{
                          cout << "Popped item of the stack: " << sv.TopNPop() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }
                      }
                    } while(chop!='b');
                  }break;

                  case 'b':{
                    cout << "Back...";
                  }break;

                  default:{
                    cout << "Not a choice...";
                  }break;
                }
              } while(cht!='b');
            }break;

            case 'b':{
              cout << "\nBack...";
            }break;

            default:{
              cout << "\nNot a choice...";
            }break;
          }

        }while(ch!='b');

      }break;

      case '2':{

        do {

          cout << "\nWhich queue-model?\n2)\tl. Queue list\n2)\tv. Queue vector\n2)\tb. Back\n  \t";
          cin >> ch;
          switch (ch) {
            case 'l':{
              do {
                cout << "\nWhich Queue list type?\n2l)\t\ti. Int\n2l)\t\tf. Float\n2l)\t\ts. String\n2l)\t\tb. Back\n   \t";
                cin >> cht;
                switch (cht) {
                  case 'i':{
                    lasd::QueueLst<int> ql{};
                    default_random_engine gen(random_device{}());
                    uniform_int_distribution <int> dist(0, 100);
                    do {
                      cout << "\nWhat is your next operation?\n2li)\t\t\te. Enqueue a random int\n2li)\t\t\th. Head\n2li)\t\t\td. Dequeue\n2li)\t\t\tn. HeadNDequeue\n2li)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'e':{
                          int x = dist(gen);
                          ql.Enqueue(x);
                          cout << "\nEnqueued " << x << ".";
                        }break;
                        case 'h':{
                          if(ql.Size()!=0) cout << "\nHead of the queue: " << ql.Head();
                          else cout << "Queue is empty!";
                        }break;
                        case 'd':{
                          ql.Dequeue();
                          cout << "Dequeued.";
                        }break;
                        case 'n':{
                          cout << "Dequeued item of the queue: " << ql.HeadNDequeue() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        // case 'r':{                           //Per testare costruttori
                        //   cout << "paperellar";
                        //   lasd::QueueLst<int> ql2(ql);
                        //   // lasd::QueueLst<int> ql2 = ql;
                        //   // lasd::QueueLst<int> ql2(std::move(ql));
                        //   // lasd::QueueLst<int> ql2 = std::move(ql);
                        //   ql2 != ql ? cout << "diversi" : cout << "uguali";
                        //   (ql2.Size()==0) ? cout << "\nql2 is empty!" : cout << endl << ql2.Head();
                        //   if(ql2.Size()==0) cout << "\nql2 is empty!";
                        //   else ql2.Dequeue();
                        //   if(ql2.Size()==0) cout << "\nql2 is empty!";
                        //   else cout << "\nPopped " << ql2.HeadNDequeue();
                        //   if(ql2.Size()!=0) cout << endl << ql2.Head();
                        //   else cout << "\nStack is empty!";
                        //   ql2.Enqueue(4);
                        //   cout << endl << ql2.Head();
                        //   (ql.Size()==0) ? cout << "\nql is empty!" : cout << endl << ql.Head();
                        //   ql.Enqueue(2);
                        //   (ql.Size()==0) ? cout << "\nql is empty!" : cout << endl << ql.Head();
                        // }break;
                        default:{
                          cout << "\nNot a choice...";
                        }break;
                      }
                    } while(chop!='b');
                  }break;

                  case 'f':{
                    lasd::QueueLst<float> ql{};
                    default_random_engine gen(random_device{}());
                    uniform_int_distribution <int> dist(0, 100);
                    do {
                      cout << "\nWhat is your next operation?\n2lf)\t\t\te. Enqueue a random float\n2lf)\t\t\th. Head\n2lf)\t\t\td. Dequeue\n2lf)\t\t\tn. HeadNDequeue\n2lf)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'e':{
                          float x = ((float)dist(gen)/10);
                          ql.Enqueue(x);
                          cout << "\nEnqueued " << x << ".";
                        }break;
                        case 'h':{
                          if(ql.Size()!=0) cout << "\nHead of the queue: " << ql.Head();
                          else cout << "Queue is empty!";
                        }break;
                        case 'd':{
                          ql.Dequeue();
                          cout << "Dequeued.";
                        }break;
                        case 'n':{
                          cout << "Dequeued item of the queue: " << ql.HeadNDequeue() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }break;
                      }
                    } while(chop!='b');
                  }break;

                  case 's':{
                    lasd::QueueLst<string> ql{};
                    default_random_engine gen(random_device{}());
            	      uniform_int_distribution <int> dist(0, chara.size());
                    default_random_engine genl(random_device{}());
            	      uniform_int_distribution <int> distl(1, 10);
                    do {
                      cout << "\nWhat is your next operation?\n2ls)\t\t\te. Enqueue a random string\n2ls)\t\t\th. Head\n2ls)\t\t\td. Dequeue\n2ls)\t\t\tn. HeadNDequeue\n2ls)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'e':{
                            int len = distl(genl);
                            for(uint j = 0; j < len; j++){
                              rs += chara[dist(gen)];
                            }
                            ql.Enqueue(rs);
                            cout << "Enqueued " << rs << ".";
                            rs = "";
                        }break;
                        case 'h':{
                          if(ql.Size()!=0) cout << "\nHead of the queue: " << ql.Head();
                          else cout << "Queue is empty!";
                        }break;
                        case 'd':{
                          ql.Dequeue();
                          cout << "Dequeued.";
                        }break;
                        case 'n':{
                          cout << "Dequeued item of the queue: " << ql.HeadNDequeue() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }break;
                      }
                    } while(chop!='b');
                  }break;

                  case 'b':{
                    cout << "Back...";
                  }break;

                  default:{
                    cout << "Not a choice...";
                  }break;
                }

              } while(cht!='b');
            }break;

            case 'v':{
              do {

                cout << "\nWhich Queue vector type?\n1v)\t\ti. Int\n1v)\t\tf. Float\n1v)\t\ts. String\n1v)\t\tb. Back\n   \t";
                cin >> cht;
                switch (cht) {
                  case 'i':{
                    lasd::QueueVec<int> qv{};
                    cout << endl << qv.Size();
                    cout << endl << qv.Empty();
                    default_random_engine gen(random_device{}());
                    uniform_int_distribution <int> dist(0, 100);
                    do {
                      cout << "\nWhat is your next operation?\n1vi)\t\t\te. Enqueue a random int\n1vi)\t\t\th. Head\n1vi)\t\t\td. Dequeue\n1vi)\t\t\tn. HeadNDequeue\n1vi)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'e':{
                          int x = dist(gen);
                          qv.Enqueue(x);
                          cout << "\nEnqueued " << x << ".";
                          cout << "\nSize() is " << qv.Size();
                        }break;
                        case 'h':{
                          qv.Empty() ? cout << "\nQueueVec is empty" : cout << "Head of the queue is " << qv.Head();
                        }break;
                        case 'd':{
                          qv.Dequeue();
                          cout << "Dequeued.";
                          cout << "\nSize() is " << qv.Size();
                        }break;
                        case 'n':{
                          cout << "Dequeued item of the queue: " << qv.HeadNDequeue() << ".";
                          cout << "\nSize() is " << qv.Size();
                        }break;
                        case 'b':{
                          qv.Clear();
                          if (qv.Empty()) cout << "\nQueueVec cleared.";
                          cout << "\nBack...";
                        }break;
                        case 'r':{
                          char k;
                          // lasd::Vector<int> v(2);            //Prova costruttore LinearContainer con vettore.
                          // v[0] = 5;
                          // v[1] = 6;
                          // lasd::QueueVec<int> qv2{v};
                          // lasd::List<int> l{};               //Prova costruttore LinearContainer con lista.
                          // l.InsertAtBack(5);
                          // l.InsertAtBack(6);
                          // lasd::QueueVec<int> qv2{l};
                          lasd::QueueVec<int> qv2{qv};       //Prove copy e move costructor/assignment.
                          // lasd::QueueVec<int> qv2 = qv;
                          // lasd::QueueVec<int> qv2(std::move(qv));
                          // lasd::QueueVec<int> qv2 = std::move(qv);
                          // qv == qv2 ? cout << "\nThe two Queues are equal" : cout << "\nThe two queues are different";
                          do {
                            cout << "\nScegli cosa fare con sv2:\n";
                            cin >> k;
                            switch (k) {
                              case 'e':{
                                int x = dist(gen);
                                qv2.Enqueue(x);
                                cout << "\nEnqueued " << x << ".";
                                cout << "\nSize() is " << qv2.Size();
                              }break;
                              case 'h':{
                                cout << "\nHead of the queue is " << qv2.Head();
                              }break;
                              case 'd':{
                                qv2.Dequeue();
                                cout << "\nDequeued.";
                                cout << "\nSize() is " << qv2.Size();
                              }break;
                              case 'n':{
                                cout << "Dequeued item of the queue: " << qv2.HeadNDequeue() << ".";
                                cout << "\nSize() is " << qv2.Size();
                              }break;
                              case 'b':{
                                cout << "Back...";
                              }break;
                              default:{
                                cout << "\nNot a choice...";
                              }
                            }
                          } while(k!='b');
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }break;
                      }
                    } while(chop!='b');
                  }break;

                  case 'f':{
                    lasd::QueueVec<float> qv{};
                    default_random_engine gen(random_device{}());
                    uniform_int_distribution <int> dist(0, 100);
                    do {
                      cout << "\nWhat is your next operation?\n1vf)\t\t\te. Enqueue a random float\n1vf)\t\t\th. Head\n1vf)\t\t\td. Dequeue\n1vf)\t\t\tn. HeadNDequeue\n1vf)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'e':{
                          float x = ((float)dist(gen)/10);
                          qv.Enqueue(x);
                          cout << "\nEnqueued " << x << ".";
                        }break;
                        case 'h':{
                          qv.Empty() ? cout << "\nQueueVec is empty" : cout << "Head of the queue is " << qv.Head();
                        }break;
                        case 'd':{
                          qv.Dequeue();
                          cout << "Dequeued.";
                        }break;
                        case 'n':{
                          cout << "Dequeued item of the stack: " << qv.HeadNDequeue() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }
                      }
                    } while(chop!='b');
                  }break;

                  case 's':{
                    lasd::QueueVec<string> qv{};
                    default_random_engine gen(random_device{}());
            	      uniform_int_distribution <int> dist(0, chara.size());
                    default_random_engine genl(random_device{}());
            	      uniform_int_distribution <int> distl(1, 10);
                    do {
                      cout << "\nWhat is your next operation?\n1vs)\t\t\te. Enqueue a random string\n1vs)\t\t\th. Head\n1vs)\t\t\td. Dequeue\n1vs)\t\t\tn. HeadNDequeue\n1vs)\t\t\tb. Back\n  \t";
                      cin >> chop;
                      switch (chop) {
                        case 'e':{
                          int len = distl(genl);
                          for(uint j = 0; j < len; j++){
                            rs += chara[dist(gen)];
                          }
                          qv.Enqueue(rs);
                          cout << "Enqueued " << rs << ".";
                          rs = "";
                        }break;
                        case 'h':{
                          qv.Empty() ? cout << "\nQueueVec is empty" : cout << "Head of the queue is " << qv.Head();
                        }break;
                        case 'd':{
                          qv.Dequeue();
                          cout << "Dequeued.";
                        }break;
                        case 'n':{
                          cout << "Dequeued item of the stack: " << qv.HeadNDequeue() << ".";
                        }break;
                        case 'b':{
                          cout << "Back...";
                        }break;
                        default:{
                          cout << "\nNot a choice...";
                        }
                      }
                    } while(chop!='b');
                  }break;

                  case 'b':{
                    cout << "Back...";
                  }break;

                  default:{
                    cout << "Not a choice...";
                  }break;
                }
              } while(cht!='b');
            }break;

            case 'b':{
              cout << "\nBack...";
            }break;

            default:{
              cout << "\nNot a choice...";
            }break;
          }

        }while(ch!='b');

      }break;

      case '3':{
        cout << "\nExit. . .\n";
      }break;

      default:{
        cout << "\nNot a choice...";
      }break;
    }

  } while(c!='3');

}
