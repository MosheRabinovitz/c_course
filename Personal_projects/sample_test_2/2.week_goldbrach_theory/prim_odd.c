
void find_prime(int n, int sol[]);
int find_prime_with_2_numbers(int n, int arr[]);
int is_prime(int n);



void find_prime(int n, int sol[])
{
	int miss1, miss2;
	
	for (int i = 2; i < n; ++i)
	{
		if (is_prime(i))
		{
			miss1 = n - i;
			{
				for (int j = 2; j < miss1; ++j)
				{
					miss2 = miss1 - j;
					if (is_prime(miss2) && is_prime(miss1 - miss2))
					{
						sol[0] = i;
						sol[1] = miss1 - miss2;
						sol[2] = miss2;
						return;
					}
				}
			}
		}
	}
}



int is_prime(int n)
{
	for (int i = 2; i < n/2; ++i)
	{
		if (!n%i)
			return 0;
	}
	return 1;
}
