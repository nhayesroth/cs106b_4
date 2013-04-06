/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	elems = new Vector<string>;
}

VectorPriorityQueue::~VectorPriorityQueue() {
	delete elems;
}

int VectorPriorityQueue::size() {
	return elems->size();
}

bool VectorPriorityQueue::isEmpty() {
	return (elems->isEmpty());
}

void VectorPriorityQueue::enqueue(string value) {
	elems->add(value);
}

string VectorPriorityQueue::peek() {
	if (elems->isEmpty())
		error("Peeked at an empty queue");
	else{
		string tmp = "";
		tmp=elems->get(0);
		for (int i=0;i<(elems->size());i++)
			if (elems->get(i)<tmp) tmp=elems->get(i);
		return tmp;
	}
}

string VectorPriorityQueue::dequeueMin() {
	if (elems->isEmpty())
		error("Dequeued an empty queue");
	else {
		string toRemove=peek();
		for (int i=0;i<(elems->size());i++){
			if (elems->get(i)==toRemove){
				elems->removeAt(i);
				return toRemove;
			}
		}
	}
}

