/***********************************************************
 *
 * list - 双向链表,从Linux内核中移植而来
 *
 ************************************** 高乙超.2017.0808 ***/
#pragma once

#include <types.h>

struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

/*
* list_entry - get the struct for this entry
* @ptr: the &struct list_head pointer.
* @type: the type of the struct this is embedded in.
* @member: the name of the list_struct within the struct.
*/
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
* list_first_entry - get the first element from a list
* @ptr:	the list head to take the element from.
* @type:	the type of the struct this is embedded in.
* @member:	the name of the list_struct within the struct.
*
* Note, that list is expected to be not empty.
*/
#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

/**
* list_first_entry_or_null - get the first element from a list
* @ptr:	the list head to take the element from.
* @type:	the type of the struct this is embedded in.
* @member:	the name of the list_struct within the struct.
*
* Note that if the list is empty, it returns NULL.
*/
#define list_first_entry_or_null(ptr, type, member) \
	(!list_empty(ptr) ? list_first_entry(ptr, type, member) : NULL)

/**
* list_last_entry - get the last element from a list
* @ptr:	the list head to take the element from.
* @type:	the type of the struct this is embedded in.
* @member:	the name of the list_struct within the struct.
*
* Note, that list is expected to be not empty.
*/
#define list_last_entry(ptr, type, member) \
    list_entry((ptr)->prev, type, member)

/**
* list_for_each	-	iterate over a list
* @pos:	the &struct list_head to use as a loop cursor.
* @head:	the head for your list.
*/
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
* list_for_each_prev	-	iterate over a list backwards
* @pos:	the &struct list_head to use as a loop cursor.
* @head:	the head for your list.
*/
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
* list_for_each_entry	-	iterate over list of given type
* @pos:	the type * to use as a loop cursor.
* @head:	the head for your list.
* @member:	the name of the list_struct within the struct.
*/
#define list_for_each_entry(pos, type, head, member)				\
	for (pos = list_entry((head)->next, type, member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, type, member))

/**
* list_for_each_entry_reverse - iterate backwards over list of given type.
* @pos:	the type * to use as a loop cursor.
* @head:	the head for your list.
* @member:	the name of the list_struct within the struct.
*/
#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_entry((head)->prev, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.prev, typeof(*pos), member))


void init_list_head(struct list_head* list);

void list_add(struct list_head* new, struct list_head* head);

void list_add_tail(struct list_head* new, struct list_head* head);

void list_del(struct list_head* entry);

void list_replace(struct list_head* old, struct list_head* new);

void list_replace_init(struct list_head* old, struct list_head* new);

void list_swap(struct list_head* u, struct list_head* v);

void list_del_init(struct list_head* entry);

void list_move(struct list_head* list, struct list_head* head);

void list_move_tail(struct list_head* list, struct list_head* head);

int list_is_last(const struct list_head* list, const struct list_head* head);

int list_empty(const struct list_head* head);

int list_is_singular(const struct list_head *head);

int list_len(const struct list_head* head);

int list_contains(const struct list_head* list, const struct list_head* head);

void list_cut_position(struct list_head *list, struct list_head *head, struct list_head *entry);

void list_cut_position_open(struct list_head *list, struct list_head *head, struct list_head *entry);

void list_splice(const struct list_head *list, struct list_head *head);

void list_splice_tail(struct list_head *list, struct list_head *head);

