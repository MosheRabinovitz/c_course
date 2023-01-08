/* Define the type of the cell and pointer to cell */
typedef struct cell * CellPtr;

typedef struct cell{
	int contents;
	CellPtr next;
	CellPtr prev;
} Cell;

/* Declare of the functions */
void print_list(CellPtr list);
void print_rev(CellPtr list);
CellPtr insert_first (CellPtr list, int input);
CellPtr remove_first (CellPtr list, int *output);
CellPtr insert_last (CellPtr list, int input);
CellPtr remove_last (CellPtr list, int *output);
void clean_list(CellPtr list);
