#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main ( int argc, char **argv )
{
	if ( argc != 3 )
	{
		printf ( "\n\tInvalid Number of Arguments\n" );
		exit ( 1 );
	}
	
	int cli_sock;
	cli_sock = socket ( AF_INET, SOCK_STREAM, 0 );
	
	struct sockaddr_in srv_specs;
	
	memset ( &srv_specs, 0, sizeof(srv_specs) );
	srv_specs.sin_family = AF_INET;
	srv_specs.sin_port = htons ( atoi ( argv[2] ) );
	srv_specs.sin_addr.s_addr = inet_addr ( argv[1] );
	
	connect ( cli_sock, (struct sockaddr *) &srv_specs, sizeof(srv_specs) );
	
	unsigned int size;
	
	recv ( cli_sock, &size, sizeof(size), 0 );
	
	char message[101];
	
	char got[101];
	
	unsigned int i, ct = 0;
	
	int ack;
	
	while ( 1 )
	{
		recv ( cli_sock, got, 101, 0 );
		
		printf ( "Got Window : " );
		
		for ( i = 0; i < size; i ++ )
		{
			message[ct++] = got[i];
			
			if ( got[i] != '\0' )
			{
				printf ( "%c", got[i] );
			}
			else
			{
				break;
			}			
		}
		
		printf ( "\n\tEnter Acnowledgement : " );
		scanf ( "%d", &ack );
		
		send ( cli_sock, &ack, sizeof(ack), 0 );
		
		if ( ack != -1 )
		{
			ct = ( ack - 1 );
		}
		else if ( i != size )
		{
			break;
		}
		
	}
	
	printf ( "\n\nComplete Message : %s\n", message );
	
	return 0;
}
