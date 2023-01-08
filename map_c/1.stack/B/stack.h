/* Determine the size of the stack */
#define STK_SIZE 20

/* The type of the stack */
typedef struct stack {
    int value;
    struct stack * next;;
} Stack;

/* Declare of the functions */
void push(Stack ** stack, int num);
int pop(Stack ** stack);
int isEmpty(Stack * stack);
int isFull(Stack * stack);
void clean(Stack ** stack);
