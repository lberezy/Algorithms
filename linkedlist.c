#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int data;
	struct node *next;
} node_t;


node_t* new_node(node_t* nxt, int data){
	node_t *tmp = (node_t*)malloc(sizeof(node_t));
	tmp->next = nxt;
	tmp->data = data;
	return tmp;
}

node_t* append_tail(node_t *list, int data) {
	if (list == NULL) {
		list = new_node(NULL,-123);
				puts("List was null, created new node.");
				return list;
	}
	node_t *current = list;
	node_t *temp;

	while (current->next != NULL) {
		current = current->next;
	}
	temp = new_node(NULL, data);
	current->next = temp;
	temp->data = data;
	return list;
}

void printlist(node_t *head){
	while (head != NULL) {
		printf("%d\n",head->data);
		head = head->next;
	}
}

node_t* append_head(node_t *head, int data){
	node_t *tmp = new_node(head,data);
	return tmp;
}

node_t* deQ(node_t *head){
	node_t *tmp = head;
}



int main(int argc,char **argv){
	int i;
	node_t *list = NULL;

	puts("Testing linked list.");

	for (i = 0; i < 10; i++) {
		/* append_head(list,i); */
		list = append_tail(list,i);
		list = append_head(list,i);
	}
	puts("Printing:");
	printlist(list);

	return EXIT_SUCCESS;
}
