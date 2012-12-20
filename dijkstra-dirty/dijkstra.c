#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool all_visited ( bool visited[], unsigned int nodes )
{
	unsigned int i;
	
	for ( i = 0; i < nodes; i ++ )
	{
		if ( visited[i] == false )
		{
			return false;
		}
	}
	
	return true;
}

int main ( void )
{
	printf ( "Enter number of nodes : " );
	unsigned int no_nodes;
	scanf ( "%u", &no_nodes );
	
	printf ( "\nEnter Adjacency Matrix :-\n" );
	unsigned int i, j;
	unsigned int adjacency_matrix[100][100];
	for ( i = 0; i < no_nodes; i ++ )
	{
		printf ( "\n%u : ", i+1 );
		for ( j = 0 ; j < no_nodes; j ++ )
		{
			scanf ( "%u", &adjacency_matrix[i][j] );
		}
	}
	
	printf ( "\nEnter start node : " );
	unsigned int start_node;
	scanf ( "%u", &start_node );
	start_node--;
	
	printf ( "\nEnter end node : " );
	unsigned int end_node;
	scanf ( "%u", &end_node );
	end_node--;
	
	unsigned int tag[100], prev[100];
	bool visited_status[100];
	
	for ( i = 0; i < no_nodes; i ++ )
	{
		visited_status[i] = false;
		tag[i] = 1000;
	}
	
	tag[start_node] = 0;
	//visited_status[start_node] = true;
	
	unsigned int min_tag, min_node;
	
	while ( ! all_visited ( visited_status, no_nodes ) )
	{
		min_tag = 1000;
		
		for ( i = 0; i < no_nodes; i ++ )
		{
			if ( ( tag[i] < min_tag ) && ( visited_status[i] != true ) )
			{
				min_tag = tag[i];
				min_node = i;
			}
		}
		
		if ( min_tag == 1000 )
		{
			break;
		}
		
		printf ( "\nMIN:%u,%u\n", min_node, min_tag );
		
		visited_status[min_node] = true;
		
		if ( min_tag != 1000 )
		{
			for ( j = 0; j < no_nodes; j ++ )
			{
				if ( adjacency_matrix[min_node][j] != 1000 )
				{
					if ( ( tag[min_node] + adjacency_matrix[min_node][j] ) < tag[j] )
					{
						tag[j] = ( tag[min_node] + adjacency_matrix[min_node][j] );
						prev[j] = min_node;
					}
				}
			}
		}		
	}
	
	printf ( "\n\nWeight : %u", tag[end_node] );
	
	printf ( "\n\nShortest Path " );
	while ( end_node != start_node )
	{
		printf ( "%u <- ", end_node+1 );
		end_node = prev[end_node];
	}
	printf ( "%u\n", end_node+1 );	
	
	return 0;
}

