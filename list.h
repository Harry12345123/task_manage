/*
 * list.h
 *
 *  Created on: 2016-11-8
 *      Author: hsy
 */
#ifndef LIST_H_
#define LIST_H_
#include <pthread.h>
#include <stddef.h>

#define ME3630_USB_NAME 50

struct list_head {
    struct list_head *next, *prev;
};

#define LIST_HEAD(name) \
    struct list_head name = { &(name), &(name) }

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void list_init(struct list_head *head)
{
    head->prev = head->next = head;
}
/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new_member,
        struct list_head *prev, struct list_head *next)
{
    next->prev = new_member;
    new_member->next = next;
    new_member->prev = prev;
    prev->next = new_member;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_head *new_member,
        struct list_head *head)
{
    __list_add(new_member, head, head->next);
}

static inline void list_add_tail(struct list_head *new_member,
        struct list_head *head)
{
    __list_add(new_member, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void list_del2(struct list_head *elem)
{
    struct list_head *prev = elem->prev;
    struct list_head *next = elem->next;

    prev->next = next;
    next->prev = prev;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static inline void __list_del_entry(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}

static inline int list_empty(struct list_head *head)
{
    return head->next == head;
}

/**
 * list_entry - get the struct for this entry
 * @ptr: the &struct list_head pointer.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) \
    ((type *) ((char *) (ptr) - offsetof(type, member)))

#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

#define list_last_entry(ptr, type, field) \
    list_entry((ptr)->prev, type, field)
/**
 * list_for_each - iterate over a list
 * @pos: the &struct list_head to use as a loop cursor.
 * @head: the head for your list.
 */
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos: the &struct list_head to use as a loop cursor.
 * @n:  another &struct list_head to use as temporary storage
 * @head: the head for your list.
 */
#define list_for_each_safe(pos, p, head)    \
    for (pos = (head)->next, p = pos->next; \
         pos != (head);                     \
         pos = p, p = pos->next)

#define list_for_each_entry_safe(p, n, h, field)            \
    for (p = list_first_entry(h, __typeof__(*p), field),        \
            n = list_entry(p->field.next, __typeof__(*p), field); &p->field != (h);\
            p = n, n = list_entry(n->field.next, __typeof__(*n), field))

#define list_for_each_entry_safe_reverse(p, n, h, field)            \
    for (p = list_last_entry(h, __typeof__(*p), field),        \
            n = list_entry(p->field.prev, __typeof__(*p), field); &p->field != (h);\
            p = n, n = list_entry(n->field.prev, __typeof__(*n), field))

//#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) (type*)( (char*)(ptr) - offsetof(type, member) )
/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr: the pointer to the member.
 * @type: the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 *
 */

struct list_head_and_lock {
    pthread_mutex_t lock;
    struct list_head list; //
};

/*
 * init list_head_add_lock_init
 * return 0 is success
 * return -1 is lock init failed
 */
static inline int LIST_HEAD_ADD_LOCK_INIT(struct list_head_and_lock *list_lock)
{
    INIT_LIST_HEAD(&(list_lock->list));
    if(pthread_mutex_init(&(list_lock->lock), NULL) != 0)
    {
        return -1;
    }
    return 0;
}

static inline void list_add_member(struct list_head *new_member,
        struct list_head_and_lock *list_lock)
{
    pthread_mutex_lock(&(list_lock->lock));
    list_add(new_member, &(list_lock->list));
    pthread_mutex_unlock(&(list_lock->lock));
}

static inline void list_add_member_tail(struct list_head *new_member,
        struct list_head_and_lock *list_lock)
{
    pthread_mutex_lock(&(list_lock->lock));
    list_add_tail(new_member, &(list_lock->list));
    pthread_mutex_unlock(&(list_lock->lock));
}

static inline void list_del_member(struct list_head *entry,
        struct list_head_and_lock *list_lock)
{
    pthread_mutex_lock(&(list_lock->lock));
    list_del(entry);
    pthread_mutex_unlock(&(list_lock->lock));
}

/*
 * return 0 is success
 * or return error no
 */
static inline int list_destroy_lock(struct list_head_and_lock *list_lock)
{
    return pthread_mutex_destroy(&(list_lock->lock));
}

static inline void _list_add(struct list_head *_new, struct list_head *prev,
        struct list_head *next)
{

    next->prev = _new;
    _new->next = next;
    _new->prev = prev;
    prev->next = _new;
}

static inline void list_add_new(struct list_head *_new, struct list_head *head)
{
    _list_add(_new, head, head->next);
}

#endif /* LIST_H_ */
