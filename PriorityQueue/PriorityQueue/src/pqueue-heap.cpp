/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include <iostream>

int DEFAULT_SIZE = 1;

HeapPriorityQueue::HeapPriorityQueue() {
	logicalLength = 0;
	list = new string[DEFAULT_SIZE];
	allocatedLength = DEFAULT_SIZE;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] list;
}

int HeapPriorityQueue::size() {
	return logicalLength;
}

bool HeapPriorityQueue::isEmpty() {
	return (logicalLength==0);
}

void HeapPriorityQueue::grow() {
	/* Growing by a factor of two gives amortized O(1) push. */
	allocatedLength *= 2;
	string* newList = new string[allocatedLength];
	
	/* Copy over the old elements into the new array. */
	for (int i = 0; i < logicalLength; i++) {
		newList[i] = list[i];
	}
	
	/* Free memory for the old array. */
	delete[] list;
	
	/* Change which array of elements we are now using. */
	list = newList;
}

void HeapPriorityQueue::enqueue(string value) {
	/* double the list size when you're out of space */
	if (logicalLength == allocatedLength) grow();
	
	/* write to first open space */
	list[size()] = value;
	logicalLength ++;

	/*bubble-up*/

	//shift indexes to 1-indexed array
	int cIndex = size()-1;
	int pIndex = size()/2-1;
	
	//loop until parent/child are in lexicographical(sp?) order
	while (list[cIndex] < list[pIndex]){
		string newChild = list[pIndex];
		list[pIndex]=list[cIndex];
		list[cIndex]=newChild;
		//move indexes up for next pair
		cIndex=pIndex;
		pIndex=(cIndex+1)/2-1;
	}
}

string HeapPriorityQueue::peek() {
if (isEmpty())
		error("Peeked at an empty queue");
	else {
		return list[0];
	}
}

string HeapPriorityQueue::dequeueMin() {
	//cache the string to return
	string toReturn = list[0];
	//swap the first and last elements
	list[0] = list[size()-1];
	logicalLength--;

	/*bubble down*/
	//select indexes for parent and two children
	int parent=0;
	int fChild=parent*2+1;
	int sChild=fChild+1;
	//loop until both children come after the parent
	while (list[parent] < list[fChild] && list[parent] < list[sChild]){
		//move down the lower side
		int smaller = fChild;
		if (list[sChild]<list[fChild]) smaller=sChild;
		//swap parent and child
		string newChild = list[parent];
		list[parent]=list[smaller];
		list[smaller]=newChild;
		//select new indexes
		parent=smaller;
		int fChild=parent*2+1;
		int sChild=fChild+1;
	}
	return toReturn;
}

