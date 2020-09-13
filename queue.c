#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->size = 0;
    q->tail = q->head;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *cursor = q->head;
    while (cursor) {
        list_ele_t *tmp = cursor;
        cursor = tmp->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;


    newh = malloc(sizeof(list_ele_t));
    if (q == NULL || newh == NULL) {
        free(newh);
        return false;
    }
    char *tmp = malloc(sizeof(char) * (strlen(s) + 1));

    if (tmp == NULL) {
        free(newh);
        return false;
    }

    newh->next = q->head;
    newh->value = tmp;
    snprintf(newh->value, strlen(s) + 1, "%s", s);


    q->head = newh;
    q->size++;

    if (q->head->next == NULL) {
        q->tail = q->head;
    }

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newTail = NULL;
    newTail = malloc(sizeof(list_ele_t));
    if (newTail == NULL) {
        return false;
    }

    char *tmp = malloc(sizeof(char) * (strlen(s) + 1));

    if (tmp == NULL) {
        free(newTail);
        return false;
    }

    newTail->value = tmp;
    newTail->next = NULL;
    snprintf(newTail->value, (strlen(s) + 1), "%s", s);


    if (q->tail == NULL && q->head == NULL) {
        q->head = newTail;
        q->tail = newTail;
    } else {
        q->tail->next = newTail;
        q->tail = newTail;
    }
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->size == 0 || sp == NULL || q->head == NULL) {
        return false;
    }
    snprintf(sp, (strlen(q->head->value) + 1), "%s", q->head->value);
    free(q->head->value);
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    q->size--;
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q == NULL ? 0 : q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size == 0) {
        return;
    }
    list_ele_t *iter = q->head;
    list_ele_t *next = q->head->next;
    list_ele_t *tempNext;


    while (next) {
        tempNext = next->next;
        next->next = iter;
        iter = next;
        next = tempNext;
    }

    tempNext = q->head;
    q->head = q->tail;
    q->tail = tempNext;
    q->tail->next = NULL;
    return;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
