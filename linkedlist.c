#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int data;
	struct node *next;
} node_t;

void insert(node_t *head, int data){
	node_t *f=head,*b=head,*temp; /* holds front and behind pointers */
	puts("If you're happy any you know it, segfault!");
	/* segfault */
	while(f->next != NULL || (f->data) < data){
		puts("If you're happy any you know it, segfault!");
		b = f;
		f = f->next;
	}
	temp = (node_t*)malloc(sizeof(node_t));
	b->next = temp;
	temp->data = data;
	temp->next = f;
}

void printlist(node_t *head){
	while(head->next != NULL){
		printf("%d\n",head->data);
		head = head->next;
	}
}

int main(int argc,char **argv){
	int i;
	node_t *list;
	list = NULL;
	puts("hi");
	for(i = 0; i < 10; i++){
		insert(list,i);
	}
	puts("Printing");
	printlist(list);

	return EXIT_SUCCESS;
}

