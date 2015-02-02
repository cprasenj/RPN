#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

LinkedList createList() {
	LinkedList *list;
	list = calloc(sizeof(LinkedList),1);
	list->count = 0;
	list->head = list->tail = NULL;
	return *list;
}
Node* create_node(void* data){
	Node *n; 
	n = malloc(sizeof(Node));
	n->data = data;
	n->next = NULL;
	return *(int *)data ? n : 0;
}
int add_to_list(LinkedList* list,Node* s) {
	if(!s)return 0;
	!list->head ? (list->head = s) : (list->tail->next = s);
	list->tail = s;
	list->count++;
	return 1;
}
void *get_first_element(LinkedList list) {
	return list.head->data;	
}
void *get_last_element(LinkedList list) {
	return list.tail->data;	
}
void traverse(LinkedList list, void (*f)(void* data)) {
	Node* traverser;
	for(traverser = list.head;traverser;traverser = traverser->next) 
		f(traverser->data);
}
Node *getNodeAt(LinkedList list, int index) {
	Node* traverser;
	int count = 0;
	if(index > list.count || index<0) return NULL;
	for(traverser = list.head;traverser;traverser = traverser->next,count++) 
		if(count == index)
			return traverser;
}
void *getElementAt(LinkedList list, int index) {
	return getNodeAt(list,index)->data;
}
int indexOf(LinkedList list,void* data) {
	Node* traverser;
	int count = 0;
	for(traverser = list.head;traverser;traverser = traverser->next,count++) 
		if(!memcmp(traverser->data,data,sizeof((void*)data)))
			return count;
	return -1;
}
void *deleteElementAt(LinkedList* list, int index) {
	Node *element = getNodeAt(*list,index);
	if(list->count < index || index < 0 || !list->head)return NULL;
	list->count -= 1;
	!element->next && !list->count ? (list->head = list->tail = NULL) : (list->tail = getNodeAt(*list,index-1)); 
	!index && element->next && (list->head = list->head->next);
	list->count > 1 && index && (getNodeAt(*list,index-1)->next = getNodeAt(*list,index+1));
	list->count == 1 && (getNodeAt(*list,index-1)->next = NULL) && (list->tail=list->head);
	return element->data;
}
int asArray(LinkedList list, void** arr) {
	Node *traverser;
	int count = 0;
	for(traverser = list.head;traverser;traverser = traverser->next,count++) 
		arr[count] = traverser->data;
	return !list.head ? 0 : count;	
}
LinkedList *filter(LinkedList list, int (*f)(void *)) {
	Node *traverser,*n1;
	LinkedList *newList = calloc(sizeof(LinkedList),1);
	for(traverser = list.head;traverser;traverser = traverser->next) 
		f(traverser->data) && (n1 = create_node(traverser->data)) && add_to_list(newList,n1);
	return newList; 
}