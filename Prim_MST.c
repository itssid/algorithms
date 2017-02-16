//C Program for finding MST using Prims Algorithm implemented using Adjacency Matrix
 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <time.h>

typedef struct graph
{
	int is_edge;//to check whetehr edge exists between pair of nodes
	int weight;// weight associated with edge between two nodes
	int is_seen;//to check whether particular set of nodes having been visited or not
}graph;

void print_MST(int* parent,int node,graph** Matrix)
{
	int i,sum=0;
	printf("Edge   Weight\n");
   for (i = 1; i < node; i++)
   {
      printf("%d - %d    %d \n", parent[i], i, Matrix[i][parent[i]].weight);
      sum=sum+Matrix[i][parent[i]].weight;
   }
   printf("Total cost is %d\n",sum);
}

int find_min_key(int* key,int* mstSet,int node)
{
	int i,index,min;
	min=INT_MAX;
	for(i=0;i<node;i++)
	{
		if((mstSet[i]==0)&&(key[i]<min)) //Finding index of the node having minimum key value and not already included in mstSet
		{
			min=key[i];
			index=i;
		}
	}
	return index;
}

void Prims_MST(graph** Matrix,int node,int edge)
{
	int* parent=(int*)calloc(node,sizeof(int));//creates the MST
	int* key=(int*)calloc(node,sizeof(int)); // key or weight associated with nodes in input graph
	int* mstSet=(int*)calloc(node,sizeof(int)); //keeps track of set of nodes which are part of minimum spanning tree
	
	int i,j,start_vertex,k;
	
	for(i=0;i<node;i++)
	{
		key[i]=INT_MAX;
		for(j=0;j<node;j++)
			Matrix[i][j].is_seen=0;
	}	

	start_vertex=rand()%node;
	printf("start vertex is %d\n",start_vertex);
	key[start_vertex]=0;
	for(i=0;i<node-1;i++) //As the tree will have node-1 edges
	{
		k = find_min_key(key,mstSet,node); //obtain index of vertex having minimum key value which is not already present in MST 
		mstSet[k]=1;//set value of the vertex included in MST as 1
		//Update the key value of adjacent vertices of the vertex included in MST
		for(j=0;j<node;j++)
		{
			if((Matrix[k][j].is_edge==1) && (mstSet[j]==0) && (Matrix[k][j].weight<key[j]) && (Matrix[k][j].is_seen==0 && Matrix[j][k].is_seen==0))
			{
				parent[j]=k;
				key[j]=Matrix[k][j].weight;
				Matrix[k][j].is_seen=1;
				Matrix[j][k].is_seen=1;
			}
			
		}
	}
	print_MST(parent,node,Matrix);			
}

int check_connected(graph** Matrix,int node,int edge)
{
	int i,j;
	//Reads adjacency matrix row-wise
	for(i=0;i<node;i++)
	{
		for(j=0;j<node;j++)
		{
			if(Matrix[i][j].is_edge==1)
				break;
			return 0; //The particular node is not connected to any node in graph and graph is disconnected
		}
	}
	return 1;
}

graph** create_graph(graph** Matrix,int node,int edge,int r)
{
	int i,j,weight;
	 Matrix = (graph**)calloc(node,sizeof(graph));
	for(i=0;i<node;i++)
		Matrix[i] = (graph*)calloc(node,sizeof(graph));
	while(edge)
	{
		i=rand()%node;
		j=rand()%node;
		if((Matrix[i][j].is_edge==0&&Matrix[j][i].is_edge==0)&&(i!=j))
		{
			Matrix[i][j].is_edge=1;
			Matrix[j][i].is_edge=1;
			weight=rand()%r+1;	
			Matrix[i][j].weight=weight;
			Matrix[j][i].weight=weight;
			edge--;
		}
	}
	return Matrix;
}

void print_graph(graph** Matrix,int node)
{
	int i,j;
	printf("Graph is\n");
	printf("node\tnode\tweight\n");
		for(i=0;i<node;i++)
		{
			for(j=0;j<node;j++)
			{
				if(Matrix[i][j].is_edge==1 && Matrix[i][j].is_seen==0)
				{
					printf("%d\t%d\t%d\n",i,j,Matrix[i][j].weight);
					Matrix[i][j].is_seen=1;
					Matrix[j][i].is_seen=1;
				}
			}
		}
}

int main()
{
	/*n is number of nodes and m is number of edges r is the weight limit
		edge-weight produced randomly in range(1,r)*/
	int n,m,r,i,j,is_connected=1;//assuming the graph generated is connected 
	time_t t;
	clock_t start,end;
	double time_taken;
	srand((unsigned) time(&t));
	int copy;
	graph** Matrix;
	printf("Enter no_of_nodes no_of_edges weight_limit\n");
	scanf("%d %d %d",&n,&m,&r);
	copy=m;
	start=clock();

	if(m<=(n*(n-1))/2)
	Matrix=create_graph(Matrix,n,m,r);
	else
	{
		printf("Number of edges exceed the limit\n");
		exit(0);
	}

	print_graph(Matrix,n);
	if(m<n)
	is_connected=check_connected(Matrix,n,m);
	if(is_connected==1)
	{
		printf("It is a connected Graph\n");
		Prims_MST(Matrix,n,m);		
	}
	else
		printf("It is a disconnected graph.\n");
	end=clock();
	time_taken=(double)(end-start)/CLOCKS_PER_SEC;
	printf("Time taken is %0.15f\n",time_taken);
	return 0;
}