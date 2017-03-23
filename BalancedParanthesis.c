#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node
{
	char ch; 
	struct node* next;
}node;

node* create_node(char c)
{
	node* local = (node*)malloc(sizeof(node));
	local->next=NULL;
	local->ch=c;
	return local; 
}

void pop(node** top)
{
	node* temp;
	temp = (*top);
	(*top)=(*top)->next;
	free(temp);
}

void push(char c,node** top)
{
	if((*top)==NULL)
	{
		(*top) = create_node(c);
	}
	
	else
	{
		node* local = create_node(c);
		local->next=(*top);
		(*top)=local;
	}
}

int CheckBracketsMatch(char* string)
{
	int length,i,count=0;
	length=strlen(string);
	node* top=NULL;
	for(i=0;i<length;i++)
	{
		if(string[i]=='(')
		{
			push('(',&top);
			count++;
		}

		else
		{
			if(top==NULL)
				return -1;
			else
				pop(&top);
		}
	}
	
	if(top==NULL)
	return count;
	
	else
	return -1;
}

int main()
{
	int size,i;
	printf("Enter size of string\n");
	scanf("%d",&size);
	char* string = (char*) malloc(sizeof(char)*size);
	time_t t;
	srand((unsigned) time(&t));
	for(i=0;i<size;i++)
	{
		if(rand()%2==0)
		string[i]='(';
		else
		string[i]=')';	
	}
	//Test Case
	/*char string[]={'(','(','(',')',')',')'};
	size=sizeof(string)/sizeof(char);*/
	 
	printf("Input string is\n");
		for(i=0;i<size;i++)
			printf("%c",string[i]);
		int count = CheckBracketsMatch(string);
		if(count==-1)
		printf("\nBrackets don't match\n");
		else
		printf("\nString has %d pairs of matching brackets\n",count); 
	return 0;
}