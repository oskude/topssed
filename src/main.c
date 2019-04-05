#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int         bind_port = 53001;
const char *bind_host = "127.0.0.1";

int new_socket;
int root_socket;

/*******************************************************************************
* clean up any mess that we might have left
*/
void cleanup ()
{
	puts("Cleaning.");

	close(new_socket);
	close(root_socket);

	exit(errno);
}

/*******************************************************************************
* initialize `root_socket` into a state that can accept connections
*/
void init_root_socket ()
{
	struct sockaddr_in addr;

	// create IPv4 TCP socket
	if (
		(root_socket = socket(AF_INET, SOCK_STREAM, 0))
		== -1
	) {
		perror("could not create socket");
		raise(SIGINT);
	}

	// TODO: why do we need this? do we need this?
	fcntl(root_socket, F_SETFL, O_NONBLOCK);

	// bind to host:port
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(bind_host);
	addr.sin_port = htons(bind_port);
	if (
		bind(root_socket, (struct sockaddr *)&addr, sizeof(addr))
		< 0
	) {
		perror("could not bind socket");
		raise(SIGINT);
	}

	// start listening for new connections
	if (
		listen(root_socket, 1)
		== -1
	) {
		perror("could not listen socket");
		raise(SIGINT);
	}
}

/*******************************************************************************
* press play on tape
*/
int main ()
{
	signal(SIGINT, cleanup);

	init_root_socket();
	printf("Listening at http://%s:%d\n", bind_host, bind_port);

	while (1) {
		if (
			(new_socket = accept(root_socket, NULL, NULL))
			> 0
		) {
			close(new_socket);
		}
		usleep(1000);
	}

	cleanup();
	return 0;
}
