#include "hash_table.h"

int main()
{
    /* Insert the keys and names to the hastable and run the functions of them */
    char * names[] = {"moshe", "david", "israel", "baruch", "dudi"};
    char * keys[] = {"purple", "silver", "yellow", "orange", "blue"};

    for (int i = 0; i < 5; ++i)
        install(names[i], keys[i]);
    
    print_hash();

    install(names[3], "red");
    install("4", "numbers");
    install("10", "numbers");

    print_hash();

    for (int i = 0; i < 5; ++i)
        undef(names[i]);
    undef("10");
    print_hash();

    clean_hastab();

    print_hash();

    return 0;
}