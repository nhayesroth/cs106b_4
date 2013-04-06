/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"



LinkedListPriorityQueue::LinkedListPriorityQueue() {
	list = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (list != NULL) {
		Cell* next = list->next;
		delete list;
		list = next;
	}
}

int LinkedListPriorityQueue::size() {
	int result = 0;
	for (Cell* curr = list; curr != NULL; curr = curr->next) {
		result++;
	}
	return result;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (list==NULL);
}

void LinkedListPriorityQueue::enqueue(string value) {
	// Create a new cell to hold the value.
	Cell* toAdd = new Cell;
	toAdd->value = value;
	// If the list is empty or the new element should go first, insert it at the front.
	if (list == NULL || list->value>toAdd->value) {
		toAdd->next = list;
		list = toAdd;
	}
	//Otherwise, step through the cell until you find the correct NEXT cell or the end
	else {
		Cell* next;
		for (Cell* curr = list; curr != NULL; curr = curr->next){
			next = curr->next;
			if (next == NULL || next->value > toAdd->value){
				curr->next = toAdd;
				toAdd->next = next;
				return;
			}
		}
	}
}

string LinkedListPriorityQueue::peek() {
	if (list == NULL)
		error("Peeked at an empty queue");
	else{
		return list -> value;
	}
}

string LinkedListPriorityQueue::dequeueMin() {
	if (list == NULL)
		error("Dequeued an empty queue");
	else {
		string toRemove = list->value;
		list = list->next;
		return toRemove;
	}
}

