#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 20


char* squeeze(char *s1,char *s2)
{
	int string_length = 0;
	while (*(s1 + string_length) != '\0')
		++string_length;
	
		
	char * new_string = (char *)malloc(sizeof(char)*string_length);
	if (new_string == NULL)
		exit(1);
	int k = 0;
	for(int i = 0; i < string_length; ++i)
	{
		if (*(s2 + i) != *(s1 + i))
		{
			*(new_string +k) = *(s1 + i);
			++k;
		}
	}
	return new_string;	
}


int main()
{	
	char s1[CHAR_SIZE], s2[CHAR_SIZE];

	printf("Enter your first string: ");
	scanf("%s", s1);
	
	printf("Enter your secound string: ");
	scanf("%s", s2);
	
	char* c = squeeze(s1, s2);;
	
	int s = 0;
	while (*(c+s) != '\0')
		printf("%c", *(c+s++));
	
	printf("\n");
	free(c);
	
}
