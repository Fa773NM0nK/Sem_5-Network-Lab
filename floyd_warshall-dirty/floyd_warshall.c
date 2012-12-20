#include <stdio.h>

int main ( void )
{
	printf ( "Enter number of nodes : " );
	unsigned int no_nodes;
	scanf ( "%u", &no_nodes );
	
	printf ( "\nEnter Adjacency Matrix :-\n" );
	unsigned int i, j, k;
	unsigned int adjacency_matrix[100][100];
	for ( i = 0; i < no_nodes; i ++ )
	{
		printf ( "\n%u : ", i+1 );
		for ( j = 0 ; j < no_nodes; j ++ )
		{
			scanf ( "%u", &adjacency_matrix[i][j] );
		}
	}
	
	for ( i = 0 ; i < no_nodes; i ++ )
	{
		for ( j = 0; j < no_nodes; j ++ )
		{
			for ( k = 0; k < no_nodes; k ++ )
			{
				if ( ( adjacency_matrix[j][i] + adjacency_matrix[i][k] ) < adjacency_matrix[j][k] )
				{
					adjacency_matrix[j][k] = ( adjacency_matrix[j][i] + adjacency_matrix[i][k] );
				}
			}
		}
	}
	
	for ( i = 0 ; i < no_nodes; i ++ )
	{
		printf ( "\n" );
		for ( j = 0; j < no_nodes; j ++ )
		{
			printf ( "%u\t", adjacency_matrix[i][j] );
		}
	}
	
	return 0;
}
