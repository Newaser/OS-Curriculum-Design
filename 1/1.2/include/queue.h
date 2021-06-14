#ifndef _QUEUE_H_
#define _QUEUE_H_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include"definitions.h"

string assertThat(string prompt){
    printf("%s", prompt);
    exit(0);
}

int isEmpty(QUEUE *q)
{
    return (q->size == 0);
}
int isFull(QUEUE *q)
{
    return (q->size == q->capacity);
}
QUEUE *createQueue(int maxElements)
{
    QUEUE *q = (QUEUE *)malloc(sizeof(QUEUE));
    q->array = (elementType *)malloc(sizeof(elementType) * maxElements);
    q->capacity = maxElements;
    makeEmpty(q);
    return q;
}
void disposeQueue(QUEUE *q)
{
    if(q != NULL) {
        free(q->array);
        free(q);
    }
}
void makeEmpty(QUEUE *q)
{
    if(q != NULL) {
        q->front = 1;
        q->rear = 0;
        q->size = 0;
    }
}
static int succ(int value, QUEUE *q) 
{
    if(++value == q->capacity) 
        value = 0;
    return value;
}
void enQueue(elementType element, QUEUE *q)
{
    if(!isFull(q)) {
        q->size++;  
        q->rear = succ(q->rear, q);
        q->array[q->rear] = element;
    } else {
        assertThat("Full queue!\n");
    }
}
elementType front(QUEUE *q)
{
    if(!isEmpty(q)) {
        return q->array[q->front];  
    } else {
        assertThat("Empty queue!\n");
    }
}
elementType deQueue(QUEUE *q)
{
    if(!isEmpty(q)) {
        elementType ret = q->array[q->front];
        q->size--;
        q->front = succ(q->front, q);
        return ret; 
    } else {
        assertThat("Empty queue!\n");
    }
}

#endif
