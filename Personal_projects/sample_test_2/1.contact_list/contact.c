#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 128


struct contact{
	char * name;
	int number;
};


struct contact * inc_pb(struct contact pb[], int len, int x);
int add_contact(struct contact pb[], int len, char * name, int number);
int find(struct contact pb[], int len, char * name);
int str_cmp(char *s1, char * s2);
int close_to_name(char * s1, char * s2);
void fill(int arr[], char * s);
int min(int num1, int num2);



struct contact * inc_pb(struct contact pb[], int len, int x)
{
	struct contact * new_pb = (struct contact *)malloc((len+x) * sizeof(struct contact));
	if (!new_pb)
		exit(1);
		
	int i = 0;
	for (; i < len; ++i)
		*(new_pb +i) = pb[i];
	free(pb);
	for (; i < (len+x); ++i)
	{
		((new_pb +i)->number) = 0;
		((new_pb +i)->name) = NULL;
	}
	return new_pb;
}

int add_contact(struct contact pb[], int len, char * name, int number)
{
	int i = 0;	
	for(; i< len ; ++i)
		if (pb[i].number == 0)
			break;
	
	if (i == len)
		return 0;
		
	char * name1 = (char*)malloc(strlen(name) * sizeof(char));
	if (!name1)
		exit(1);
	name1 = name;
	pb[i].name = name1;
	pb[i].number = number;
	return 1;
}

int find(struct contact pb[], int len, char * name)
{
	if (pb[0].number == 0)
		return 0;
	
	for (int i = 0; i < len; ++i)
	{
		if (str_cmp(name, pb[i].name))
			return pb[i].number;
	}
	
	int max = -1;
	int number = 0;
	
	for (int i = 0; i < len; ++i)
	{
		int temp = close_to_name(name, pb[i].name); 
		if (max < temp)
		{	
			max = temp;
			number = pb[i].number;
		}
	}
	return number;
	
}

int str_cmp(char *s1, char * s2)
{
	if (strlen(s1) != strlen(s2))
		return 0;
	
	for(int i = 0; *(s1 +i) != '\0'; ++i)
		if (*(s1+i) != *(s2+i))
			return 0;
	
	return 1;
}


int close_to_name(char * s1, char * s2)
{
	int h1[N], h2[N], sum;
	
	fill(h1, s1);
	fill(h2, s2);
	
	for(int i = 0; i < N; ++i)
		sum += min(h1[i], h2[i]);
	return sum;
}

void fill(int arr[], char * s)
{
	for(int i = 0; i < N; ++i)
		arr[i] = 0;
	
	while (*s)
		arr[*s++] += 1;
}

int min(int num1, int num2)
{
	if (num1 < num2)
		return num1;
		
	return num2;
}


int main()
{
	struct contact * pb = (struct contact *)malloc(sizeof(struct contact));
	
	char name1[] = "moshe";
	char name2[] = "israel";
	char name3[] = "dudi";
	char name4[] = "didi";
	
	int a  = -1, b = -1, c = -1;
	
	a = add_contact(pb, 1, name1, 100);
	b = add_contact(pb, 1, name2, 250);
	c = add_contact(pb, 1, name3, 500);
	
	printf("a:%2d   b:%2d   c:%2d\n", a, b, c);
	
	pb = inc_pb(pb, 1, 2);
	b = add_contact(pb, 3, name2, 250);
	c = add_contact(pb, 3, name3, 500);
	
	printf("a:%2d   b:%2d   c:%2d\n", a, b, c);
	
	a = find(pb, 3, name1);
	b = find(pb, 3, name3);
	c = find(pb, 3, name4);
	
	printf("%d, %d, %d, \n", pb[0].number, pb[1].number, pb[2].number); 
	printf("%s, %s, %s, \n", pb[0].name, pb[1].name, pb[2].name); 

	printf("a:%2d   b:%2d   c:%2d\n", a, b, c);

}
