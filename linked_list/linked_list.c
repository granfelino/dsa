/* 
	TODO:
		- insert
		- testing
 */

#include <stdio.h>


struct node
{
	int index;	
	int data;
	node* previous, next;
};
#typedef struct node node;

struct linked_list
{
	node* head;
};
#typedef linked_list linked_list;


// create a linked_list
linked_list linked_list_create()
{
	linked_list *linked_list_ptr = malloc(sizeof(linked_list));
	if (linked_list_ptr == NULL)
	{
		fprintf(stderr, "linked list was not allocated in memory");
		exit(EXIT_FAILURE);
	}

	return linked_list_ptr;
}


// find the last element of the list
node* linked_list_find_last(linked_list *linked_list)
{
	node* node_iter = linked_list->head;
	while (node_iter->next != NULL)
	{
		node_iter = node_iter->next;
	}

	return node_iter;
}


// find the last but one elened of the list
node* linked_list_find_last_but_one(linked_list *linked_list)
{
	node* node_iter = linked_list->head;
	while (node_iter->next->next != NULL)
	{
		node_iter = node_iter->next;
	}

	return node_iter;
}

// push to linked_list
void linked_list_push(linked_list *linked_list_ptr, int input_data)
{
	if (linked_list->head == NULL)
	{
		linked_list->head = malloc(sizeof(node));
		linked_list->index = 0;
		linked_list->data = input_data;
		linked_list->head->previous = NULL;
		linked_list->head->next = NULL;
	} else {
		node* node_last = linked_list_find_last(linked_list);
		node_last->next = malloc(sizeof(node));
		node_last->next->index = node_last->index + 1;
		node_last->next->data = input_data;
		node_last->next->previous = node_last;
		node_last->next->next = NULL;
	}
}

void linked_list_push_first(linked_list *linked_list, int input_data)
{
	if (linked_list->head == NULL)
	{
		linked_list->head = malloc(sizeof(node));
		linked_list->head->index = 0;
		linked_list->head->data = input_data;
		linked_list->head->previous = NULL;
		linked_list->head->next = NULL;			
	} else {
		node *new_head = malloc(sizeof(node));
		new_head->index = 0;
		new_head->data = input_data;
		new_head->next = linked_list_ptr->head;
		new_head->previous = NULL;
		linked_list_ptr->head = new_head;

		// changing indexes
		*node current_node = linked_list_ptr->head->next;
		while(1)
		{
			current_node->index = current_node->previous->index + 1;
			if (current_node->next == NULL) break;
		}
	}
}


int linked_list_get_data(linked_list *linked_list, int index_get)
{
	node* current_node = linked_list->head;
	while (1)
	{
		if (current_node->index == index_get) break;
		else current_node = current_node->next;
	}

	return current_node->data;
}


int linked_list_get_index(linked_list *linked_list, int value_get)
{
	node* current_node = linked_list->head;
	while (1)
	{
		if (current_node->data = value_get) break;
		else current_node = current_node->next;
	}

	return current_node->index;
}


int linked_list_pop(linked_list *linked_list)
{
	node* last_but_one_node = linked_list_find_last_but_one(linked_list);
	int returned_data = last_but_one_node->next->data;
	free(last_but_one_node->next);
	last_but_one_node->next = NULL;

	return returned_data;
}


int linked_list_pop_first(linked_list *linked_list)
{
	node *old_head = linked_list->head;
	int returned_data = current_head->data;
	linked_list->head = linked_list->head->next;
	free(old_head);

	linked_list->head->index = 0;
	node *current_node = linked_list->head->next;
	while(1)
	{
		current_node->index = current_node->previous->index + 1;
		current_node = current_node->next;
		if (current_node->next == NULL) break;
	}

	return returned_data;
}


// insert before specified element
void linked_list_insert(linked_list *linked_list, int insert_index, int input_data)
{
	if (insert_index = 0)
	{
		// linked_list_push_first(linked_list, input_data);
	} else  {
		/* create new node
			search for specified node
			rewire previous from specified node to new node as next
			assign previous in the new node as previous node from specified
			assign next in the new node as the specified node
			assign previous in the specified node as the new node*/
	}
	
}

int main()
{

	return 0;
}