/* Determine the size of the queue */
#define QUE_SIZE 20

/* Define the type of the queue */
typedef struct queue {
    int to_enqueue;
    int to_dequeue;
    int size;
    int queue[QUE_SIZE];
} Queue;

/* Prototypes */
void init(Queue * queue);
void enqueue(Queue * queue, int num);
int dequeue(Queue * queue);
int isEmpty(Queue * queue);
int isFull(Queue * queue);
