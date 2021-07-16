/*      BFS       */
BreadthFirstSearch(G){
  for each v £ V{
    c[v] = b;
    d[v] = inf;
    P[v] = null;
  }
  for each v £ V{
    if(c[v]==b) BreadthFirstSearchVisit(G, v);
  }
}

BreadthFirstSearchVisit(G, s){
  q.Enqueue(s);
  c[s] = g;
  d[s] = 0;
  while(q.IsNotEmpty()){
    v = q.Head();
    for each u £ Adj(v){
      if(c[u]==b){
        q.Enqueue(u);
        c[u] = g;
        d[u] = d[v] + 1;
        P[u] = v;
      }
    }
    q.Dequeue();
    c[v] = n;
  }
}

/*      DFS       */
DepthFirstSearch(G){
  for each v £ V{
    c[v] = b;
    P[v] = null;
  }
  time = 0;
  for each v £ V{
    if(c[v] = b) DepthFirstSearchVisit(G, v);
  }
}

DepthFirstSearchVisit(G, s){
  c[s] = g;
  d[s] = time;
  time++;
  for each u £ Adj(s){
    if(c[u] == b){
      DepthFirstSearchVisit(G, u);
      P[u] = s;
    }
  }
  c[s] = n;
  f[s] = time;
  time++;
}

/*      DFS for AcyclicyTest      */
AcyclicyTest(){
  for each v £ V c[v] = b;
  for each v £ V{
    if(c[v] == b){
      if(DFS_A(G, v)==false) return false;
    }
  }
  return true;
}

DFS_A(G, s){
  c[s] = g;
  for each u £ Adj(s){
    if(c[u] == b){
      if(DFS_A(G, u)==false) return false;
    }
    else{
      if(c[u] == g) return false;
    }
  }
  c[s] = n;
  return true;
}

/*      Topological Ordering       */
TopologicalOrdering1(G){
  InDegree(G, id[]);
  q.InitQueue(G, id[]);
  while(q.IsNotEmpty()){
    v = q.Head;
    fun(v);
    for each u £ Adj(v){
      ge[u] = ge[u] - 1;
      if(ge[u] == 0) q.Enqueue(u);
    }
    q.Dequeue();
  }
}

TopologicalOrdering2(G){
  for each v £ V{
    if(c[v] == b) st = DFS_TO(G, v, st);
  }
  return st;
}

DFS_TO(G, s, st){
  c[s] = g;
  for each u £ Adj(s){
    if(c[u] == b) st = DFS_TO(G, u, st);
  }
  c[v] = n;
  st.Push(v);
  return st;
}

/*      Strongly Conncected Components       */
SCC(G){
  st = DFSI(G);
  GT = TransposeGraph(G);
  return DFSII(GT, st);
}

DFSI(G){
  for each v £ V{
    if(c[v] == b) st = DFS_V(G, v, st);
  }
  return st;
}

DFS_V_I(G, s, st){
  c[s] = g;
  for each u £ Adj(s){
    if(c[u] == b) st = DFS_V_I(G, u, st);
  }
  c[s] = n;
  st.Push(s);
  return st;
}

DFS_II(G, st){
  c = 1;
  while(st.IsNotEmpty()){     // Or just follow the order of the stack, by catching the first white vertex...
    v = st.TopNPop();
    if(c[v] == b){
      DFS_V_II(G, v, c, st);
      c++;
    }
  }
  return c - 1;     // Number of SCCs.
}

DFS_V_II(G, s, c, st){
  SCC[s] = c;
  c[s] = g;
  for each u £ Adj(s){
    if(c[u] == b) DFS_V_II(G, u, c, st);
  }
  c[s] = n;
}
