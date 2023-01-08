#define HASHSIZE 101

/* nlist:  From K&R2 page 144.  Points to a search text and
 * a replacement text */

/* Define the type of the node */
struct nlist
{
	struct nlist *next;
	char *name;
	char *defn;
};

/* Define the type of the hashtable */
static struct nlist *hashtab[HASHSIZE];

/* Declare of the functions */
/* My functions */
void undef(char *s);
void print_hash();
void print_hash_index(int i);
void clean_hastab();

/* Functions that given */
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
unsigned hash(char *s);
char *strduplicates(char *s);
