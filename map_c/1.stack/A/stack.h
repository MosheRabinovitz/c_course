/* Determine the size of the stack */
#define STK_SIZE 20

/* Define the type of the stack */
typedef struct stack {
    int stk_ptr;
    char stack[STK_SIZE];
} Stack;

/* Declare of the functions */
void init(Stack * stack);
void push(Stack * stack, int num);
int pop(Stack * stack);
int isEmpty(Stack * stack);
int isFull(Stack * stack);
