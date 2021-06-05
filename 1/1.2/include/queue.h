#ifndef _QUEUE_H_
#define _QUEUE_H_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<erron.h>

typedef struct car{
    int car_id;
    quaOrient from;
    float est_time;  //estimated time to pass the crossing
} car, elementType;

typedef struct QUEUE
{
    int capacity;        //max amount of elements
    int front;           //cursor of the front element
    int rear;            //cursor of the rear element
    int size;            //the amount of elements
    elementType *array;  //the array of elements
} QUEUE;

int isEmpty(QUEUE *q);                          //if empty
int isFull(QUEUE *q);                           //if full
QUEUE *createQueue(int maxElements);            //create a queue
void disposeQueue(QUEUE *q);                    //dispose a queue
void makeEmpty(QUEUE *q);                       //init or empty a queue
void enQueue(elementType element, QUEUE *q);    //enqueue a element 
elementType front(QUEUE *q);                    //return the front element
elementType deQueue(QUEUE *q);                  //return the front element and dequeue it

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
    QUEUE *q = (QUEUE *)malloc(sizeof(struct queueRecord));
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
        perror("Full queue!\n");
    }
}
elementType front(QUEUE *q)
{
    if(!isEmpty(q)) {
        return q->array[q->front];  
    } else {
        perror("Empty queue!\n");
    }
}
elementType deQueue(QUEUE *q)
{
    if(!isEmpty(q)) {
        int ret = q->array[q->front];
        q->size--;
        q->front = succ(q->front, q);
        return ret; 
    } else {
        perror("Empty queue!\n");
    }
}

#endif
