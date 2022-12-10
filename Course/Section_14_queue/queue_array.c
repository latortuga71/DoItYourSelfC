#include <stdlib.h>
#include <stdio.h>



typedef struct Node Node;
struct Node {
	int data;
	///Node* next;
	//Node* prev;
};


typedef struct QueueArray QueueArray;

struct QueueArray {
	int size;
	int items;
	int head;
	int tail;
	Node** array;
};

QueueArray* init_queue_array(int size){
	if (size == 0) {
		return NULL;
	}
	QueueArray* q = (QueueArray*)malloc(sizeof(QueueArray) * 1);	
	q->size = size;
	q->items = 0;
	q->head = -1;
	q->tail = -1;
	q->array = (Node**)calloc(size,sizeof(Node*));
	return q;
}

Node* init_node(int data){
	Node* n = (Node*)malloc(sizeof(Node));
	n->data = data;
	return n;
}

void delete_queue_array(Node** n){
	free(n);
}

void delete_queue(QueueArray* q){
	int x = 0;
	Node* tmp = q->array[x];
	while (tmp != NULL){
		free(tmp);
		tmp = q->array[++x];
	}
	free(q->array);
	free(q);
	return;
}

void print_queue(QueueArray* q) {
	printf("items %d size %d tail idx %d head idx %d\n",q->items,q->size,q->tail,q->head);
	int x = q->head;
	for (; x < q->tail; x++){
		printf("[%d 0x%x]\n",x,q->array[x]);
	}
	printf("[%d 0x%x]\n",x,q->array[x]);
}

int dequeue(QueueArray* q) {
	// instead of removing just set data to be -1 or something like that so we can properly resize later
	if (q->head == -1)
		return -1;
	int dequeued_data = q->array[q->head]->data = -1;
	q->head++;
	q->items--;
	return dequeued_data;
}

int enqueue(QueueArray* q, Node* n) {
	if (q->items +1 >= q->size) {
		printf("realloc\n");
		q->size = q->size * 2;
		printf("new size? %d\n",q->size);
		Node** tmp = (Node**)realloc(q->array, sizeof(Node*) * q->size);
		if (tmp == NULL){
			fprintf(stderr,"ERROR: Failed to realloc!");
			exit(1);
		}
		q->array = tmp;
		printf("after relloc");
	}
	if (q->head == -1) {
		// this becomes the front of the queue
		q->head = 0; // zero is the front of the queue
		q->tail = 0; // zero index is the back of the queue
		q->array[0] = n;
		q->items++;
		return 0;
	}
	q->array[q->tail++] = n;
	q->items++;
	return 0;
}


void resize_queue(QueueArray* q){
	int i = 0;
	int j = 0;
	for (i = 0; i < q->head; i++) {
		// free all left over nodes
		if (q->array[i]->data == -1){
			printf("found -1 deleting node\n");
			free(q->array[i]);
			q->items--;
		}
	}
	// allocate a new memory block thats smaller and copy everything over
	int k = 0;
	int old_head = q->head;
	int new_size = (q->tail - i) + 1;
	Node** new_smaller_block = (Node**)calloc(new_size,sizeof(Node*));
	for (j = q->head; j < q->tail; j++) {
		printf("copying 0x%x\n",q->array[j]);
		new_smaller_block[k] = q->array[j];
		k++;
	}
	printf("RESIZE OK! old sz %d new sz %d\n",q->size,new_size);
	Node** old_block = q->array;
	q->size = new_size;
	q->items = k;
	printf("ITEMS %d\n",k);
	q->array = new_smaller_block;
	q->head = 0;
	q->tail = k;
	delete_queue_array(old_block);
	return;
}



int main(){
	QueueArray* q = init_queue_array(1);
	Node* a = init_node(2);
	Node* b = init_node(1);
	Node* c = init_node(1);
	Node* d = init_node(2);
	Node* e = init_node(1);
	Node* f = init_node(1);
	Node* g = init_node(1);
	Node* h = init_node(2);
	Node* i = init_node(1);
	Node* j = init_node(1);
	Node* k = init_node(1);
	Node* l = init_node(1);
	Node* m = init_node(1);
	enqueue(q,a);
	enqueue(q,b);
	enqueue(q,c);
	enqueue(q,d);
	enqueue(q,e);
	enqueue(q,f);
	enqueue(q,g);
	enqueue(q,h);
	enqueue(q,i);
	enqueue(q,j);
	enqueue(q,k);
	print_queue(q);
	dequeue(q);
	dequeue(q);
	dequeue(q);
	dequeue(q);
	dequeue(q);
	dequeue(q);
	print_queue(q);
	resize_queue(q);
	enqueue(q,l);
	enqueue(q,m);
	print_queue(q);
	delete_queue(q);

}
