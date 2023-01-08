#include "distance_from_string.h"

int main()
{
	char a[] = "israel";
	char b[] = "moshe";
	char c[] = "yossi";
	char d[] = "didi";
	char s[] = "oss";
	char * names[] = {a,b,c,d};
	
	print(names, 4);
	arrange(names, 4, s);
	print(names, 4);
	
}
