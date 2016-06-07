#include "mymalloc.h"
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>


typedef struct node *memory_node;
memory_node next_fit_block(int);
memory_node allocate_space(memory_node, int);
void *my_nextfit_malloc(int size);
memory_node deallocate_space(void *block);
memory_node coalesce_block(memory_node);
void my_free(void *ptr);
int check_block(void *ptr);

void *first_node = NULL;
void *current_node = NULL;

struct node {
	int available;
	int block_size;
	memory_node next_node;
	memory_node previous_node;
	void *data;
	char ptr[1];
};


void *my_nextfit_malloc(int size) {

	memory_node last_block;
	memory_node current_block;


	if (first_node != NULL) {

		last_block = current_node;

		current_block = next_fit_block(size);

		if (current_block != NULL) {

			current_block->available = 0;
		}

		else {

			current_block = allocate_space(last_block, size);

			if (current_block == NULL) {

				return(NULL);
			}

		}
	}
	else {

		current_block = allocate_space(NULL, size);

		if (current_block == NULL) {
			return NULL;


			first_node = current_block;
			current_node = current_block;

		}
	}

	return(current_block->ptr);

}

memory_node allocate_space(memory_node block, int size) {

	memory_node current_block = sbrk(0);

	if (sbrk(sizeof(struct node) + size) == (void*)-1) {
		return(NULL);
	}

	current_block->block_size = size;
	current_block->next_node = NULL;

	if (block != NULL) {
		block->next_node = current_block;
	}

	current_block->available = 0;
	return(current_block);
}

memory_node next_fit_block(int size) {

	memory_node current_block = current_node;

	while (current_block != NULL && !(current_block->available)
		&& (current_block->block_size <= size)) {

		if (current_block != NULL) {
			current_block = current_block->next_node;
		}
		else {
			current_block = first_node;

			if (current_block == current_node) {
				return NULL;
			}
		}

	}

	current_node = sbrk(0);

	return current_block;
}
void my_free(void *ptr) {
	memory_node current_block;

	if (check_block(ptr)) {
		current_block = deallocate_space(ptr);
		current_block->available = 1;

		if (current_block->previous_node->available && current_block != NULL) {
			current_block = coalesce_block(current_block->previous_node);
		}

		if (current_block->next_node != NULL) {
			coalesce_block(current_block);
		}
		else {
			if (current_block->previous_node != NULL) {
				current_block->previous_node->next_node = NULL;
			}
			else {
				first_node = NULL;
			}
			brk(current_block);
		}
	}
}

memory_node deallocate_space(void *block) {
	char *space;
	space = block;
	space = space - sizeof(struct node);
	block = space;

	return block;
}
memory_node coalesce_block(memory_node block) {

	if (block->next_node != NULL && block->next_node->available) {


		block->block_size = block->block_size + sizeof(struct node) + block->next_node->block_size;

		block->next_node = block->next_node->next_node;


		if (block->next_node != NULL) {

			block->next_node->previous_node = block;
		}
	}

	return block;
}
int check_block(void *ptr) {
	if (first_node != NULL) {
		if (ptr < sbrk(0) && ptr > first_node) {
			return(ptr == (deallocate_space(ptr))->data);
		}
	}


	return(0);
}