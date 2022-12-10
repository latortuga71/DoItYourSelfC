#include <stdlib.h>
#include <stdio.h>



typedef struct Node Node;
struct Node {
	int data;
	Node* next;
	Node* prev;
};


typedef struct QueueLinkedList QueueLinkedList;

struct QueueLinkedList {
	int size;
	Node* head;
	Node* tail;
};

QueueLinkedList* init_queue_ll(){
	QueueLinkedList* q = (QueueLinkedList*)malloc(sizeof(QueueLinkedList));	
	q->size = 0;
	q->head = NULL;
	q->tail = NULL;
	return q;
}

Node* init_node(int data){
	Node* n = (Node*)malloc(sizeof(Node));
	n->data = data;
	return n;
}


void dequeue(QueueLinkedList* q) {
	if (q->size == 0)
		return;
	Node* old_head = q->head;
	Node* new_head = q->head->prev;
	new_head->next = NULL;
	q->head = new_head;
	free(old_head);
	q->size--;
	return;
}

void enqueue(QueueLinkedList* q, Node* n) {
	// first node
	if (q->size == 0){
		q->tail = n;
		q->head = n;
		n->next = NULL;
		n->prev = NULL;
		q->size++;
		return;
	}
	Node* tmp_tail = q->head;
	// go to the back of the line to keep head intact
	while (tmp_tail->prev != NULL){
		tmp_tail = tmp_tail->prev;
	}
	// now add something at the back
	tmp_tail->prev = n;
	n->next = tmp_tail;
	n->prev = NULL;
	q->tail = n;
	q->size++;
}

void delete_queue(QueueLinkedList* q){
	Node* tmp = q->head;
	while (tmp->prev != NULL){
		Node* deleted_node = tmp;
		tmp = tmp->prev;
		free(deleted_node);
	}
	free(tmp);
	free(q);
	return;
}

void print(QueueLinkedList* q) {
	Node* tmp = q->tail;
	int counter = 0;
	while (tmp->next != NULL){
		printf("[%d] %d\n",counter++,tmp->data);
		tmp = tmp->next;
	}
	printf("[%d] %d\n",counter++,tmp->data);
	return;
}

int main(){
	QueueLinkedList* q = init_queue_ll();
	Node* a = init_node(2);
	Node* b = init_node(1);
	Node* c = init_node(0);
	enqueue(q,a);
	enqueue(q,b);
	enqueue(q,c);
	dequeue(q);
	print(q);
	delete_queue(q);
}
