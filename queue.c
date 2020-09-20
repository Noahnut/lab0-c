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
    if (q == NULL) {
        return;
    }
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
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;

    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
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
    if (q == NULL) {
        return false;
    }
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
    int stringSize = 0;
    if (q == NULL || q->size == 0 || sp == NULL || q->head == NULL) {
        return false;
    }

    stringSize =
        strlen(q->head->value) > bufsize ? bufsize : strlen(q->head->value) + 1;
    snprintf(sp, stringSize, "%s", q->head->value);
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
    if (q == NULL || q->size == 0 || q->size == 1) {
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

void ListSplit(list_ele_t *head, list_ele_t **left, list_ele_t **right)
{
    list_ele_t *fast;
    list_ele_t *slow;
    fast = head->next;
    slow = head;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

void MoveNode(list_ele_t **dst, list_ele_t **src)
{
    list_ele_t *tmpNode = *src;
    *src = tmpNode->next;
    tmpNode->next = *dst;
    *dst = tmpNode;
}


list_ele_t *SortMerge(list_ele_t *left, list_ele_t *right)
{
    list_ele_t dummyNode;
    list_ele_t *tail = &dummyNode;

    while (1) {
        if (left == NULL) {
            tail->next = right;
            break;
        } else if (right == NULL) {
            tail->next = left;
            break;
        }
        if (strcmp(left->value, right->value) < 0) {
            MoveNode(&(tail->next), &left);
        } else {
            MoveNode(&(tail->next), &right);
        }
        tail = tail->next;
    }
    return (dummyNode.next);
}

void MergeSort(list_ele_t **head)
{
    list_ele_t *h = *head;
    list_ele_t *left;
    list_ele_t *right;

    if ((h == NULL || (h->next == NULL))) {
        return;
    }

    ListSplit(h, &left, &right);
    MergeSort(&left);
    MergeSort(&right);

    *head = SortMerge(left, right);
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || q->size == 0 || q->size == 1) {
        return;
    }

    MergeSort(&q->head);
    list_ele_t *iter = q->head;
    while (iter->next != NULL) {
        iter = iter->next;
    }
    q->tail = iter;
}
