#include <stdio.h>
#include <stdlib.h>

struct list_entry {
	int data;
	struct list_entry *next;
};

struct list_entry list_head;

int __list_add(struct list_entry *head, struct list_entry *entry)
{
	struct list_entry *ptr = head;

	if (!head || !entry) {
		return -1;
	}

	while (ptr->next) {
		ptr = ptr->next;
	}

	ptr->next = entry;
	entry->next = NULL;
	return 0;
}

int list_add(struct list_entry *head, int data)
{
	struct list_entry *entry = (struct list_entry *)malloc(sizeof(struct list_entry));

	if (entry) {
		entry->data = data;
		return __list_add(head, entry);
	}
	return -1;
}

int list_del(struct list_entry *head, struct list_entry *entry)
{
	struct list_entry *ptr = head;
	struct list_entry *prev = head;

	if (!head || !entry) {
		return -1;
	}
	if (entry == head->next) {
		head->next = NULL;
		free(entry);
	}	

	while (ptr->next && ptr != entry) {
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == entry) {
		prev->next = ptr->next;
		free(ptr);
		return 0;
	}
	return -1;
}

struct list_entry *list_reverse(struct list_entry *head)
{
	struct list_entry *new_list = NULL;

	while (head) {
		struct list_entry *elm = head;
		head = head->next;
		elm->next = new_list;
		new_list = elm;
	}
	return new_list;
}

void list_show(struct list_entry *head)
{
	struct list_entry *ptr = head;

	printf("List info:\n");
	while (ptr) {
		printf("%d\t", ptr->data);		
		ptr = ptr->next;
	}
}

int main(int argc, char **argv)
{
	struct list_entry *ptr = NULL;
	printf("hello simple list\n");

	list_del(&list_head, NULL);
	list_add(&list_head, 1);
	list_add(&list_head, 2);
	list_add(&list_head, 3);
	list_add(&list_head, 4);
	ptr = list_reverse(&list_head);
	list_show(ptr);
	return 0;
}