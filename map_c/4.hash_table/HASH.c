/***************************************************************************
 *                              From K&R2                                  *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"



/* lookup: From K&R2 page 145. Look for s in hashtab. */
struct nlist *lookup(char *s)
{
	struct nlist *np;
	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

/* install: From K&R2 page 145. Put (name, defn) in hashtab. */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
	
	if((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if(np == NULL || (np->name = strduplicates(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
		free((void *) np->defn);
	if((np->defn = strduplicates(defn)) == NULL)
		return NULL;
	return np;
}

/* hash: From K&R2 page 144.  Form hash value for string s. */
unsigned hash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; ++s)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* strdup: From K&R2 page 143. Makes a duplicate of s. */
char *strduplicates(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
}

/* Print the hashtable */
void print_hash()
{
    for(int i = 0; i < HASHSIZE; ++i)
    {
        if (hashtab[i])
		{
			printf("%d: ", i);
			print_hash_index(i);
		}
    }
	printf("\n");
}

/* Remove a name and definition (and free them) from the table */
void undef(char *s)
{
    struct nlist * np = lookup(s);

    if (np)
    {
        free(np->defn);
        free(np->name);
		np->defn = NULL;
		np->name = NULL;
    }
}

/* Print specific index in the table */
void print_hash_index(int i)
{
	struct nlist * np = hashtab[i];
    while (np!= NULL)
    {
        printf("%s : %s, ", np->defn, np->name);
        np = np->next;
    }
	printf("\n");
}

/* Clean and free the table */
void clean_hastab()
{
	for(int i = 0; i < HASHSIZE; ++i)
    {
        if (hashtab[i])
		{
			struct nlist * np = hashtab[i];
			struct nlist * nq;
    		while (np!= NULL)
			{
				nq = np;
				if(np->defn)
					free(np->defn);
				if(np ->name)
					free(np ->name);
				np = np->next;
				free(nq);				
			}
			hashtab[i] = NULL;
		}
	}
	printf("The hash table cleaned \n");

}