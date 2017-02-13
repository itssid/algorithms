#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int n,i,j,count_prime=0,copy;
	printf("Enter a positive integer\n");
	scanf("%d",&n);
	copy=n;
	double limit = sqrt(n);
	int* numbers = (int*)calloc(n-1,sizeof(int));
	
	for(i=0;i<=limit;i++)
	{
		if(numbers[i]==0)
		{	
			for(j=i+1;j<n-1;j++)
			{
				if((j+2)%(i+2)==0)
					numbers[j]=1;
			}
		}
	}
	
	for(i=0;i<n-1;i++)
	{
		if(numbers[i]==0)
			count_prime++;
	}
	
	int* prime_numbers=(int*)calloc(count_prime,sizeof(int));
	int* exponent=(int*)calloc(count_prime,sizeof(int));
	
	for(i=0,j=0;i<n-1;i++)
	{
		if(numbers[i]==0)
		{
			prime_numbers[j]=i+2;
			j++;
		}
	}
	
	i=0;
	free(numbers);
	int* sum = (int*)calloc(count_prime,sizeof(int));
	
	while(n!=1)
	{
		while(n%prime_numbers[i]==0)
		{
			n=n/prime_numbers[i];
			exponent[i]++;
		}
		i++;
	}
	
	int k=0,product=1;
	
	for(j=0;j<=i;j++)
	{
		if(exponent[j]>=1)
		{
			while(exponent[j]>=0)
			{
				sum[k]=sum[k]+(int)pow(prime_numbers[j],exponent[j]);
				exponent[j]=exponent[j]-1;
			}
		}
		if(sum[k]!=0)
			product=product*sum[k];
		k++;
	}
	free(prime_numbers);
	free(sum);
	free(exponent);
	printf("sum of divisor of %d is %d\n",copy,product);
	if(copy==product)
		printf("True\n");
	else
		printf("False\n");
	return 0;
}