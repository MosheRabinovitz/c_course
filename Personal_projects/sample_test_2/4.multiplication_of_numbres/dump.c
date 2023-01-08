int dmul(int n)
{
	if (n < 10)
		return n;
	
	return ((n %10) * (dmul(n/10)));
}

int signature(int n)
{
	int res = dmul(n);
	if(res < 10)
	 	return res;
	
	return signature(res);
}
