/* Determine the size of the stack */
#define STK_SIZE 20

/* Declare the stack */
static int stk_ptr = 0;
static char stack[STK_SIZE]; /* stack and stack pointer */

/* Declare of the functions */
void calculate(char operator);
void insert(char * arg);
void print_result();