#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main ( int argc, char **argv )
{
	
	if ( argc != 2 )
	{
		printf ( "\n\tERROR : Incorrect Number of Arguments!\n" );
		fflush ( stdout );
		exit ( 1 );
	}
	
	int sock_fd;
	sock_fd = socket ( AF_INET, SOCK_STREAM, 0 );
	
	struct sockaddr_in server_specs;
	
	memset ( &server_specs, 0, sizeof(server_specs) );
	server_specs.sin_family = AF_INET;
	server_specs.sin_port = htons ( atoi ( argv[1] ) );
	server_specs.sin_addr.s_addr = htonl ( INADDR_ANY );
	
	int yes = 1;
	setsockopt ( sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int) );
	
	bind ( sock_fd, (struct sockaddr*) &server_specs, sizeof(server_specs) );
	
	listen ( sock_fd, 5 );
	
	struct sockaddr_in client_specs;
	socklen_t len = sizeof(client_specs);
	
	int client_sock_fd;
	client_sock_fd = accept ( sock_fd, (struct sockaddr*) &server_specs, &len );
	
	char message[100];
	
	while ( 1 )
	{
		recv ( client_sock_fd, message, 100, 0 );
		
		if ( ! strcmp ( message, "!q" ) )
		{
			printf ( "\n\n\tThey have closed connection!\n" );
			break;
		}
	
		printf ( "Them\t: %s", message );
		fflush ( stdout );
		
		printf ( "\nYou\t: " );
		fflush ( stdout );
		
		fgets ( message, 100, stdin );
		message[( strlen ( message ) - 1 )] = '\0';
	
		send ( client_sock_fd, message, ( strlen ( message ) + 1 ), 0 );
		
		if ( ! strcmp ( message, "!q" ) )
		{
			printf ( "\n\tYou have closed connection!\n" );
			break;
		}
	}
	
		close ( sock_fd );
		close ( client_sock_fd );
		
	return 0;
}
