/*
// findAdj(x) ritorna un primo adiacente bianco, ritorna nullptr se x non ha adiacenti bianchi
// FindNode() ritorna un primo vertice bianco sul grafo
// terminated: curr==nullptr && structure.Empty()
*/

findAdj(v){
	if(next!=nullptr){
		if(c[next] == white){
			return next;
		}
		findAdj(next);
	}
	else return nullptr;
}

findNode(){
	i = 0;
	while(i<size){
		if(v[i].color==white) return v[i];
		i++;
	}
	return nullptr;
}

terminated(){
	return (curr==nullptr && structure.Empty());
}

/* ***BFS ITERATOR*** */
GraphBreadthIterator(){
	curr = g.findNode();
	c[curr] = black;
}

operator++(){
	if(!terminated){
		u = findAdj(curr);
		while(u!=nullptr) q.Enqueue(u);
		if(!q.Empty()){
			curr = q.HeadNDequeue();
			c[curr] = black;
		}
		else curr = FindNode();
	}
	else throw std::out_of_range();
}

/* ***DFS PREORDER ITERATOR*** */
/* INVARIANTE: NELLO STACK CI SONO SOLO VERTICI NERI
avanzo sul primo adiacente bianco del curr, mettendo il curr nello stack, quando poi sto su un curr che ha soli adiacenti neri (o nessun adiacente), esso NON VIENE PUSHATO, ma prendo la head dello stack,
e faccio una visita del primo adiacente bianco (se c'è) della head, quando non ne trovo più, faccio la pop dello stack, quando poi lo stack sarà vuoto, devo richiamare la funzione findNode */

GraphPreIterator(){
	curr = g.FindNode();
	c[curr] = black;
}

operator++{
	if(!terminated){
		v = findAdj(curr)
		if(v!=nullptr){				// la prima cosa che controllo è se il curr ha adiacenti bianchi...
			st.push(curr)
			c[curr] = black
			curr = v
		}
		else{
			if(!st.Empty){
				v = findAdj(st.top())
				while(!st.Empty() && v==nullptr){					// se il curr non ha adiacenti bianchi devo controllare il primo adiacente bianco IN TUTTO LO STACK
					st.pop()
					if(!st.Empty()) v = findAdj(st.top())
				}
				if(st.Empty()) curr = g.findNode()				// se ho svuotato tutto lo stack, allora nessun vertice più aveva adiacenti bianchi, quindi devo fare il "salto" sul grafo, prendendo un nuovo nodo non raggiungibile
				else{																			// altrimenti, se non ho svuotato tutto lo stack, devo continuare con uno degli adiacenti bianchi che ho trovato dallo stack
					st.push(curr)
					c[curr] = black
					curr = v
				}
			else{
				curr = g.findNode()												// "salto"...
			}
		}
	}
	else throw std::out_of_range("++exc.")
}


/* ***DFS POSTORDER ITERATOR*** */
/*
INVARIANTE: NELLO STACK CI SONO SOLO VERTICI GRIGI
navigo gli adiacenti bianchi finchè non ne trovo, quando sono finiti, visito il nodo corrente e lo annerisco, poi prendo la top dello stack, e faccio lo stesso ragionamento, cioè come se dovessi
applicare la leftmostleaf...
*/

GraphPOIterator(){
	curr = findNode();
	curr = LeftMostLeaf(curr);
}

LeftMostLeaf(Node v){
	u = findAdj(v);
	if(u!=nullptr){
		st.push(v);
		c[v] = grey;
		curr = LeftMostLeaf(u);
	}
	else{
		curr = v;
		c[v] = black;
	}
	return curr;
}

operator++(){
	if(!terminated){
		if(!st.Empty()){
			v = st.Top();				// temporaneamente ho il top ...
			v = findAdj(v);			// ... ma mi devo spostare sul suo primo bianco ...
			if(v!=nullptr) curr = LeftMostLeaf(v);		// ... dal suo primo bianco devo andare "all'ultimo" bianco
			else{
				curr = st.TopNPop();		// se quel top non ha adiacenti bianchi, allora sarà proprio il top ad essere il curr...
				c[curr] = black
			}
		}
		else{
			curr = findNode();				// "salto"...
			if(curr!=nullptr) curr = LeftMostLeaf(curr);
		}
	}
	else throw std::out_of_range("++exc.");
}
