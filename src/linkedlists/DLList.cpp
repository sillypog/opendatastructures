/**
* Doubly-linked list implementing stack, queue, and deque interfaces.
*
* Each node contains a reference to the next and previous node.
* Rather than keep track of the head and tail (which would have no
* previous and next nodes, respectively), the list is made circular
* with a dummy node which contains no data but removes special cases
* by ensuring every node has a previous and next node.
*
* List operations should be twice as efficient as the SLList because
* if we are looking for an entry in the second half of the list, we
* can work backwards from the tail.
*
* Performance:
*        get(i): O(1+ min{i, n − i})
*      set(i,x): O(1+ min{i, n − i})
*      add(i,x): O(1+ min{i, n − i})
*     remove(i): O(1+ min{i, n − i})
*       push(x): O(1)
*         pop(): O(1)
*    enqueue(x): O(1)
*    dequeue(x): O(1)
*   addFirst(x): O(1)
* removeFirst(): O(1)
*    addLast(x): O(1)
* removeLast(x): O(1)
*/

template <class T>
DLList<T>::DLList(): dummy(DNode<T>(0)){
	dummy.next = &dummy;
	dummy.prev = &dummy;
}


template <class T>
DNode<T>* DLList<T>::getNode(int i){
	DNode<T>* p;

	if (i < n/2){
		// Start at the head and work forward
		p = dummy.next;

		for (int j=0; j < i; j++){
			p = p->next;
		}
	} else {
		// Start at the tail and work backward
		p = &dummy;
		for (int j=n; j > i; j--){
			p = p->prev;
		}
	}
	return p;
}

template <class T>
DNode<T>* DLList<T>::addBefore(DNode<T> *w, T x){
	DNode<T>* u = new DNode<T>(x);
	u->prev = w->prev;
	u->next = w;
	u->next->prev = u;	// Same as w->prev = u
	u->prev->next = u;
	n++;
	return u;
}


template <class T>
int DLList<T>::size(){
	return n;
}

template <class T>
T DLList<T>::get(int i){
	return getNode(i)->x;
}


template <class T>
T DLList<T>::set(int i, T x){
	DNode<T>* u = getNode(i);
	T old = u->x;
	u->x = x;
	return old;
}

template <class T>
void DLList<T>::add(int i, T x){
	addBefore(getNode(i), x);
}

template <class T>
T DLList<T>::remove(int i){
	DNode<T>* w = getNode(i);
	T x = w->x;

	w->prev->next = w->next;
	w->next->prev = w->prev;
	delete w;
	n--;

	return x;
}


template <class T>
void DLList<T>::addFirst(T x){
	add(0, x);
}

template <class T>
T DLList<T>::removeFirst(){
	return remove(0);
}

template <class T>
void DLList<T>::addLast(T x){
	add(n, x);
}

template <class T>
T DLList<T>::removeLast(){
	return remove(n-1);
}


template <class T>
void DLList<T>::push(T x){
	addFirst(x);
}

template <class T>
T DLList<T>::pop(){
	return removeFirst();
}


template <class T>
void DLList<T>::enqueue(T x){
	addFirst(x);
}

template <class T>
T DLList<T>::dequeue(){
	return removeLast();
}
