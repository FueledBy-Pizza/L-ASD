# L-ASD
Algorithms and Data Structure pseudocodes, Lab Algorithms and Data Structures libraries.

            *** LASD ***

Exercise1: Vector and List.
Exercise2: Stack and Queue.
Exercise3: BinaryTree -BTVec and BTLink- and BTIterators.
Exercise4: Binary Search Tree.
Exercise5: Matrix - MatrixVec and Yale Matrix (by RowMajor: Compressed Sparse Row).
Exercise6: NOT IMPLEMENTED - JUST SOME GRAPH ITERATOR DRAFTS.

zmytestex* are personal tests.
zlasdtest are prof tests.

Exercise2. ***Vec structures***
  The structures have a strong property: having only a power-of-two size, starting from 4.
  We won't really pop/dequeue datas, we just decrement the index of where we will insert next.
  But there are Reducing methods of the structures, just like there are Expanding methods.
  Expand cause: insert the size-1th element.
  Expand effect: double size.
  Reduce cause: delete the (size/4)+1th element.
  Reduce effect: half size.

  -Stack-
    sentinel: where we will insert next data, it is also the number of concrete elements in the structure.
    Pop: decrement sentinel.
  -Queue-
    A circular queue,
    concrete elements will be calculated with tail-head if tail>=head, size-(head-tail) otherwise.
    head: where datas start.
    tail: where we will insert next data.
    Pop: decrement tail.

Exercise3.
  We build a Binary Tree from a Linear Container by going in breadth, so we'll have h = O(nlgn) if n is number of nodes.
  There are not Inserts and Deletes.

Exercise4.
  BST are only Linked.
  We build a BST from a Linear Container by inserting from the structure, because in average cases, we will still have an h = O(nlgn);
  anyway, the other way to surely have an h = O(nlgn), has been implemented (see comments at the end with QuickSort...).
  There are Inserts and Deletes. We will insert only if the element is not present yet.
  FindPointerTos are auxiliary functions in order to have a very flow code, by returning a reference to a const pointer to a NodeLnk.

Exercise5. ***CSR***
  If two or more values in the vec are the same, it means only the first one value points to a non-void row, all the others are void.
  The ()operator that returns a Data&, has to create the cell if that doesn't exist.
  Map&Fold functions are implemented with lambdaexpressions, to apply the function just at the first attribute of the pair.


            *** ASD ***
        !!Just pseudocode!!

You can find QuickSort algorithm in BST LASD code.
Sorting Algorithms: HeapSort.
Trees Algorithms: Adelson-Velsky Landis algorithms.
Graph algorithms: BFS, DFS, Acyclicy Test, Topologial Ordering, SCC.
