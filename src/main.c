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
* send http header
*/
void send_http_header (int socket)
{
	fcntl(socket, F_SETFL, O_NONBLOCK);
	send(socket, "HTTP/1.1 200 OK\n", 16, 0);
	send(socket, "Access-Control-Allow-Origin: *\n", 31, 0);
	send(socket, "Content-Type: text/event-stream;charset=utf-8\n", 46, 0);
	send(socket, "\n", 1, 0);
}

/*******************************************************************************
* send all constants that client might need for calculations
*/
void send_config (int socket)
{
	int len;
	char config_data[64]; // TODO: lets not hope that is enough...

	long clock_tick = sysconf(_SC_CLK_TCK);
	long max_pages = sysconf(_SC_PHYS_PAGES);
	long num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	long page_size = sysconf(_SC_PAGESIZE);

	len = sprintf(
		config_data,
		"data: %li %li %li %li\n",
		clock_tick,
		max_pages,
		num_cpus,
		page_size
	);

	send(socket, "event: config\n", 14, 0);
	send(socket, config_data, len, 0);
	send(socket, "\n", 1, 0);
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
			send_http_header(new_socket);
			send_config(new_socket);
			close(new_socket);
		}
		usleep(1000);
	}

	cleanup();
	return 0;
}
