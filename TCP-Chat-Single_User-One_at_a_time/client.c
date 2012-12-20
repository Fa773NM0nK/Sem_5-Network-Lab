#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main ( int argc, char **argv )
{
	if ( argc != 3 )
	{
		printf ( "\n\tERROR : Incorrect Number of Arguments!\n" );
		fflush ( stdout );
		exit ( 1 );
	}
	
	int sock_fd;
	sock_fd = socket ( AF_INET, SOCK_STREAM, 0 );
	
	struct sockaddr_in srv_specs;
	
	memset ( &srv_specs, 0, sizeof(srv_specs) );
	srv_specs.sin_family = AF_INET;
	srv_specs.sin_port = htons ( atoi ( argv[2] ) );
	srv_specs.sin_addr.s_addr = inet_addr ( argv[1] );
	
	connect ( sock_fd, (struct sockaddr*) &srv_specs, sizeof(srv_specs) );
	
	char message[100];
	
	while ( 1 )
	{
		printf ( "\nYou\t: " );
		fflush ( stdout );
		
		fgets ( message, 100, stdin );
		message[( strlen ( message ) - 1 )] = '\0';
	
		send ( sock_fd, message, ( strlen ( message ) + 1 ), 0 );
		
		if ( ! strcmp ( message, "!q" ) )
		{
			printf ( "\n\tYou have closed connection!\n" );
			break;
		}
	
		recv ( sock_fd, message, 100, 0 );
		
		if ( ! strcmp ( message, "!q" ) )
		{
			printf ( "\n\n\tThey have closed connection!\n" );
			break;
		}
		
		printf ( "Them\t: %s", message );
		fflush ( stdout );
	}
	
	close ( sock_fd );
	
	return 0;
}

