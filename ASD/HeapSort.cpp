HeapSort(A, sizeof(A)){
  BuildHeap(A, sizeof(A));
  for(i=sizeof(A); i>=2; i--){
    swap(A, 1, HEAPSIZE);
    HEAPSIZE--;
    Heapify(A, 1)
  }
}

Heapify(A, i){
  max = i;
  l = 2 * i;
  r = (2*i)+1;
  if(l<=HEAPSIZE && A[l] > A[max]) max = l;
  if(r=HEAPSIZE && A[r] > A[max]) max = r;
  if(max!=i){
    swap(A, i, max);
    Heapify(A, max);
  }
}

BuildHeap(A, sizeof(A)){
  HEAPSIZE = sizeof(A);
  for(i=n/2; i>=1; i--) Heapify(A, i);
}
