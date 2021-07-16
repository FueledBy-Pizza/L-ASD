InsertAVL(T, k){
  if(T!=null){
    if(T->Key == k) return T
    else{
      if(T->Key > k){
        T->SX = InsertAVL(T->SX, k);
        T = BalanceSx(T);
      }
      else{
        T->DX = InsertAVL(T->DX, k);
        T = BalanceDx(T);
      }
    }
  }
  else{
    T = new Node();
    T->h = 0;
    T->Key = k;
  }
}

BalanceSx(T){
  if((T->SX->h - T->DX->h) == 2){
    if((T->SX->SX->h) > (T->SX->DX->h)) T = RotationSx(T);
    else T = DoubleRotationSx(T);
  }
  else T->h = 1 + Max(T->SX->h, T->DX->h);
  return T;
}

RotationSx(T){
  NewRoot = T->SX;
  T->SX = NewRoot->DX;
  NewRoot->DX = T;
  T->h = 1 + Max(T->SX->h, T->DX->h);
  return NewRoot;
}

DoubleRotationSx(T){
  T->SX = RotationDx(T->SX);
  return RotationSx(T);
}

DeleteAVL(T, k){
  if(T!=null){
    if(T->Key > k){
      T->SX = DeleteAVL(T->SX, k);
      T = BalanceDx(T);
    }
    else{
      if(T->Key < k){
        T->DX = DeleteAVL(T->DX, k);
        T = BalanceSx(T);
      }
      else T = DeleteAVLRoot(T);
    }
  }
  return T;
}

DeleteAVLRoot(T){
  if(T!=null){
    Node* tmp;
    if(T->SX==null || T->DX==null){
      tmp = T;
      if(T->SX==null) T = T->DX
      else T = T->SX
    }
    else{
      tmp = DetachMinAVL(T->DX, T);
      T->Key = tmp->Key;
      T = BalanceSx(T);
    }
    delete tmp;
  }
  return T;
}

DetachMinAVL(T, P){
  if(T!=null){
    if(T->SX!=null){
      ret = DetachMinAVL(T->SX, T);
      NewRoot = BalanceDx(T);
    }
    else{
      ret = T;
      NewRoot = T->DX;
    }
    if(P->SX==T) P->SX = NewRoot;
    else P->DX = NewRoot;
  }
  return ret;
}
