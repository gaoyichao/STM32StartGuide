/***********************************************************
 *
 * list - 双向链表,从Linux内核中移植而来
 *
 ************************************** 高乙超.2017.0808 ***/
#include <list.h>

void init_list_head(struct list_head* list) {
    list->prev = list;
    list->next = list;
}

void __list_add(struct list_head* new, struct list_head* prev, struct list_head* next) {
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

/*
* list_add - add a new entry
*
* @new: new entry to be added
* @head: list head to add it after
*
* Insert a new entry after the specified head.
* This is good for implementing stacks.
*/
void list_add(struct list_head* new, struct list_head* head) {
    __list_add(new, head, head->next);
}

/*
* list_add_tail - add a new entry
* @new: new entry to be added
* @head: list head to add it before
*
* Insert a new entry before the specified head.
* This is useful for implementing queues.
*/
void list_add_tail(struct list_head* new, struct list_head* head) {
    __list_add(new, head->prev, head);
}

/*
* Delete a list entry by making the prev/next entries
* point to each other.
*
* This is only for internal list manipulation where we know
* the prev/next entries already!
*/
void __list_del(struct list_head * prev, struct list_head * next) {
    next->prev = prev;
    prev->next = next;
}


/**
* list_del - deletes entry from list.
* @entry: the element to delete from the list.
* Note: list_empty() on entry does not return true after this, the entry is
* in an undefined state.
*/
void __list_del_entry(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
}

void list_del(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}

/**
* list_replace - replace old entry by new one
* @old : the element to be replaced
* @new : the new element to insert
*
* If @old was empty, it will be overwritten.
*/
void list_replace(struct list_head *old, struct list_head *new) {
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

void list_replace_init(struct list_head *old, struct list_head *new) {
    list_replace(old, new);
    init_list_head(old);
}

void list_swap(struct list_head* u, struct list_head* v) {
    struct list_head tmp;
    tmp.next = &tmp;
    tmp.prev = &tmp;

    list_replace(u, &tmp);
    list_replace(v, u);
    list_replace(&tmp, v);
}

/**
* list_del_init - deletes entry from list and reinitialize it.
* @entry: the element to delete from the list.
*/
void list_del_init(struct list_head *entry) {
    __list_del_entry(entry);
    init_list_head(entry);
}

/**
* list_move - delete from one list and add as another's head
* @list: the entry to move
* @head: the head that will precede our entry
*/
void list_move(struct list_head *list, struct list_head *head) {
    __list_del_entry(list);
    list_add(list, head);
}

/**
* list_move_tail - delete from one list and add as another's tail
* @list: the entry to move
* @head: the head that will follow our entry
*/
void list_move_tail(struct list_head *list, struct list_head *head) {
    __list_del_entry(list);
    list_add_tail(list, head);
}

/**
* list_is_last - tests whether @list is the last entry in list @head
* @list: the entry to test
* @head: the head of the list
*/
int list_is_last(const struct list_head *list, const struct list_head *head) {
    return list->next == head;
}

/**
* list_empty - tests whether a list is empty
* @head: the list to test.
*/
int list_empty(const struct list_head *head) {
    return head->next == head;
}

/**
* list_is_singular - tests whether a list has just one entry.
* @head: the list to test.
*/
int list_is_singular(const struct list_head *head) {
    return !list_empty(head) && (head->next == head->prev);
}

int list_len(const struct list_head* head) {
    int i = 0;
    struct list_head* temp = head->next;

    while (temp != head) {
        i++;
        temp = temp->next;
    }
    return i;
}

int list_contains(const struct list_head* list, const struct list_head* head) {
    struct list_head* pos;
    for (pos = list->next; pos != list; pos = pos->next) {
        if (head == pos)
            return 1;
    }
    return 0;
}

void __list_cut_position(struct list_head *list, struct list_head *head, struct list_head *entry) {
    struct list_head *new_first = entry->next;
    list->next = head->next;
    list->next->prev = list;
    list->prev = entry;
    entry->next = list;
    head->next = new_first;
    new_first->prev = head;
}

/**
* list_cut_position - cut a list into two
* @list: a new list to add all removed entries
* @head: a list with entries
* @entry: an entry within head, could be the head itself
*	and if so we won't cut the list
*
* This helper moves the initial part of @head, up to and
* including @entry, from @head to @list. You should
* pass on @entry an element you know is on @head. @list
* should be an empty list or a list you do not care about
* losing its data.
*
*/
void list_cut_position(struct list_head *list, struct list_head *head, struct list_head *entry) {
    if (list_empty(head))
        return;
    if (list_is_singular(head) &&
        (head->next != entry && head != entry))
        return;
    if (entry == head)
        init_list_head(list);
    else
        __list_cut_position(list, head, entry);
}

/**
* list_cut_position_open - cut a list into two
*
* NOT including @entry
*
*/
void list_cut_position_open(struct list_head *list, struct list_head *head, struct list_head *entry) {
    if (list_empty(head))
        return;
    if (list_is_singular(head) &&
        (head->next != entry && head != entry))
        return;
    if (entry == head)
        init_list_head(list);
    else
        __list_cut_position(list, head, entry->prev);
}

void __list_splice(const struct list_head *list, struct list_head *prev, struct list_head *next) {
    struct list_head *first = list->next;
    struct list_head *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

/**
* list_splice - join two lists, this is designed for stacks
* @list: the new list to add.
* @head: the place to add it in the first list.
*/
void list_splice(const struct list_head *list, struct list_head *head) {
    if (!list_empty(list))
        __list_splice(list, head, head->next);
}

/**
* list_splice_tail - join two lists, each list being a queue
* @list: the new list to add.
* @head: the place to add it in the first list.
*/
void list_splice_tail(struct list_head *list, struct list_head *head) {
    if (!list_empty(list))
        __list_splice(list, head->prev, head);
}


