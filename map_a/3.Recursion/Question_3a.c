#include <stdio.h>

#define CHAR_SIZE 20

void lower(char* c);
int is_letter(char s);
int isPalindrome(char str[], int startFrom, int n);
int main();

/* Check the palindrome according the advanced definition of task A */
int isPalindrome(char str[], int startFrom, int n)
{
	int checkIfPalindrome = 1;
	
	if ((checkIfPalindrome) && (n >= startFrom))
	{
		if (is_letter(str[startFrom]))
		{
			if (is_letter(str[n]))
			{
				lower(&str[startFrom]);
				lower(&str[n]);
				printf("The compresion is between: %c, %c\n", str[startFrom], str[n]);
				if (str[startFrom] == str[n])
				{
					checkIfPalindrome = isPalindrome(str, startFrom + 1, n - 1);
				}
				else {
					checkIfPalindrome = 0;
				}
			}
			else
				checkIfPalindrome = isPalindrome(str, startFrom, n - 1);
		}
		else
			checkIfPalindrome = isPalindrome(str, startFrom + 1, n);
	}
	return (checkIfPalindrome);
}

/* Change capital letter to lower lettter */
void lower(char* c)
{
	if (*c >= 'A' && *c <= 'Z')
		*c = *c +32;
}

/* Ceck if the char is letter */
int is_letter(char c)
{
	if ((c >= 'A' && c <= 'Z')|| (c >= 'a' && c <= 'z'))
		return 1;
	return 0;
}

int main()
{
	printf("Enter string to check: ");
	char s[CHAR_SIZE];
	scanf("%s", s);
	printf("\n");
	
	int string_length = 0;
	while ( s[string_length] != '\0')
		string_length += 1;
	
	int isPalindrome1 = isPalindrome(s, 0, string_length-1);
	
	if (isPalindrome1)
		printf("\nis Palindrome!");
	else
		printf("\nis not Palindrome");
	printf("\n");
	
}
