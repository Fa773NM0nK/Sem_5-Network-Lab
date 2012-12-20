#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main ( int argc, char **argv )
{
	if ( argc != 2 )
	{
		printf ( "\n\tInvalid Number of Arguments\n" );
		exit ( 1 );
	}
	
	int srv_sock;
	srv_sock = socket ( AF_INET, SOCK_STREAM, 0 );
	
	struct sockaddr_in srv_specs;
	
	memset ( &srv_specs, 0, sizeof(srv_specs) );
	srv_specs.sin_family = AF_INET;
	srv_specs.sin_port = htons ( atoi ( argv[1] ) );
	srv_specs.sin_addr.s_addr = htonl ( INADDR_ANY );
	
	int yes = 1;
	setsockopt ( srv_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes) );
	
	bind ( srv_sock, (struct sockaddr *) &srv_specs, sizeof(srv_specs) );
	
	listen ( srv_sock, 5 );
	
	struct sockaddr_in cli_specs;
	socklen_t len = sizeof(cli_specs);
	int cli_sock;
	
	char message[101];
	
	printf ( "Enter Message : " ); fflush ( stdout );
	fgets ( message, 101, stdin );
	message[( strlen ( message ) - 1 )] = '\0';
	
	cli_sock = accept ( srv_sock, (struct sockaddr *) &cli_specs, &len );
	
	printf ( "\nEnter window size : " );
	unsigned int size;
	scanf ( "%u", &size );
	
	send ( cli_sock, &size, sizeof(size), 0 );
	
	unsigned int ct = 0;
	
	char to_send[101];
	unsigned int i;
	
	int ack;
	
	while ( ct < ( strlen ( message ) + 1 ) )
	{
		printf ( "\nSending : " );
		
		for ( i = 0; i < size; i ++ )
		{
			 to_send[i] = message[ct+i];
			 printf ( "%c", to_send[i] );
			 fflush ( stdout );
			 
			 if ( message[ct+i] == '\0' )
			 {
			 	i ++;
			 	break;
			 }
		}
		
		send ( cli_sock, to_send, size, 0 );
		
		recv ( cli_sock, &ack, sizeof(ack), 0 );
		
		if ( ack == -1 )
		{
			ct += i;
		}
		else
		{
			ct = ( ack - 1 );
		}
	}
	
	printf ( "\n\nMessage Sent!\n" );
	fflush ( stdout );
	
	return 0;
}

