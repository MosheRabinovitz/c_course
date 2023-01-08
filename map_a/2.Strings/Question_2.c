#include <stdio.h>

#define CHAR_SIZE 20


void reverse (char s[ ] );
void check_strong_password(char s[]);
void expand(char s[3]);


/* reverse character string */
void reverse (char s[ ] )
{
	int string_length;
	int i;
	char tmp;
	/* step 1: calculate length of s */
	string_length = 0;
	
	while ( s[string_length] != '\0')
	string_length = string_length + 1;
	
	/* step 2: reverse string */
	for (i = 0; i < string_length/2; i++)
	{
		tmp = s[i];
		s[i] = s[string_length - i - 1];
		s[string_length - i - 1] = tmp;
	}
}

/* Check if password contain at least one number, one capital letter, one of the symbols %!#@ and the length is at least 5 characters.*/
void check_strong_password(char s[])
{
	int string_length = 0, isContainNumber = 0, isContainCapital = 0, isContainSymbol = 0;
	
	while ( s[string_length] != '\0')
	{
		if (s[string_length] >= '0' && s[string_length] <= '9')
			isContainNumber = 1;
		else if (s[string_length] == '%' || s[string_length] == '!' || s[string_length] == '#' || s[string_length] == '@')
			isContainSymbol = 1;
		else if (s[string_length] >= 'A' && s[string_length] <= 'Z')
			isContainCapital = 1;
		string_length += 1;
	}
	
	if(isContainNumber && isContainCapital && isContainSymbol && string_length > 4)
		printf("The password is strong\n");
	else
		printf("The password is not strong\n");
}

/* Expand abbreviations string */
void expand(char s[3])
{
	int string_length = 0;
	while ( s[string_length] != '\0')
		string_length += 1;
		
	if(s[1] == '-' && string_length == 3)
		for(char i = s[0]; i <= s[2]; ++i)
			if (i <= '9' || (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z'))
				printf("%c, ", i);	
}

int main()
{
	printf("A.\n");
	printf("Enter your password: ");
	char s[CHAR_SIZE];
	scanf("%s", s);
	check_strong_password(s);
	
	printf("\nB.\n");
	printf("Enter your abbreviations: ");
	char s1[3];
	scanf("%s", s1);
	expand(s1);
	printf("\n");
	
}
