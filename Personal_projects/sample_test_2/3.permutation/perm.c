

int is_perm(int num1, int num2)
{
	int arr1[10],arr2[10];
	
	fill(num1, arr1);
	fill(num2, arr2);
	
	for (int i = 0; i < 10; ++i)
	{
		if (arr1[i] != arr2[i])
			return 0;
	}
	return 1;
}


void fill(int n, int arr[])
{
	for (int i = 0; i < 10; ++i)
		arr[i] = 0;
		
	int mod;
	while(n)
	{
		mod = n %10;
		arr[mod] += 1;
		n /=10;	
	}
}


int smallest_perm(int n)
{
	int arr[10], small_p = 0;
	
	fill(n, arr);
	
	int i = 1;
	while(i < 10)
	{
		if (arr[i]--)
		{
			small_p *= 10;
			small_p += i;
		
			while(arr[0]--)
				small_p *= 10;
		}
		else
			++i;
	}
	return small_p;
}
