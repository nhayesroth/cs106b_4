/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include <iostream>

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = tail = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (head != NULL) {
		Cell* next = head -> next;
		delete head;
		head = next;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	int result = 0;
	for (Cell* curr = head; curr != NULL; curr = curr->next) {
		result++;
	}
	return result;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return (head == NULL);
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	/* Create a new cell to hold the value. It goes in the front*/
	Cell* toAdd = new Cell;
	toAdd->value = value;
	toAdd->next = head;
	toAdd->prev = NULL;
	
	/* If the list was empty, now it's a single element. */
	if (head == NULL) {
		head = tail = toAdd;
	}
	/* Otherwise, rewire previous head to point back to it and set the new head */
	else {
		head->prev = toAdd;
		head = toAdd;
	}
}

string DoublyLinkedListPriorityQueue::peek() {
	if (head == NULL)
		error("Peeked at an empty queue");
	else{
		string toReturn = head -> value;
		for (Cell* curr = head; curr != NULL; curr = curr->next)
			if (curr->value < toReturn) toReturn = curr->value;
		return toReturn;
	}
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	
	/*empty list*/
	if (head==NULL){
		error("Dequeued an empty queue");
	}
	else if (head==tail){
		Cell* toRemove = head;
		string toReturn = toRemove->value;
		head = NULL;
		tail = NULL;
		delete toRemove; 
		return toReturn;
	}
	else{

		/*find the cell to remove and cache its string value*/
		Cell* toRemove = head;
		for (Cell* curr = head; curr != NULL; curr = curr->next){
			if (curr->value < toRemove->value) toRemove = curr;
		}
		string toReturn = toRemove->value;

		//toRemove is head
		if (toRemove == head){
			head = head->next;
			head->prev = NULL;
		}
		//toRemove is tail
		else if (toRemove == tail){
			tail = tail->prev;
			tail->next = NULL;
		}
		//toRemove in middle
		else {
			(toRemove->prev)->next = toRemove->next;
			(toRemove->next)->prev = toRemove->prev;
		}
		delete toRemove;
		return toReturn;
	}
}
