#include <stdio.h>
#include <limits.h>
#include "queue.h"


/* Initialize tho pointer of the queue to -1 */
void init(Queue * queue)
{
    queue->to_enqueue = 0;
    queue->to_dequeue = 0;
    queue->size = 0;
}


/* enqueue the num into the queue */
void enqueue(Queue * queue, int num)
{
    if (isFull(queue))
    {
        printf("The queue is full\n");
        return;
    }
    queue->queue[queue->to_enqueue] = num;
    queue->to_enqueue = (queue->to_enqueue + 1) % QUE_SIZE;
    ++queue->size;
    
}


/* dequeue the last elements from the queue */
int dequeue(Queue * queue)
{
     if (isEmpty(queue))
    {
        printf("The queue is empty\n");
        return INT_MIN;
    }
    int result = queue->queue[queue->to_dequeue];
    queue->to_dequeue = (queue->to_dequeue + 1) % QUE_SIZE;
    --queue->size;
    return result;
}


/* Check if the queue is empty */
int isEmpty(Queue * queue)
{
    if(queue->size == 0)
        return 1;
    
    return 0;
}


/* Check if the queue is full */
int isFull(Queue * queue)
{
    if(queue->size == QUE_SIZE-1)
        return 1;
    
    return 0;
}