#include <errno.h>
#include "network.h"
#include <unistd.h>
#include <stdlib.h>
#include "util.h"
#include <arpa/inet.h>
#include <string.h>
#include "Cookie.h"

//Return-value 1 : Recieving Message was ok
//Return-value 0: Client closed Connection
//Return-value -1: Error while reading Message

int clientReceive(int fd, char *buffer)
{
	//TODO: Receive length
	ssize_t bytes_read;

	bytes_read = read(fd, buffer, MSG_MAX);

	if(bytes_read > 0) {
		return 1;
	}
	else if (bytes_read == 0) {
		return 0;

	}

	return -1;
}


int clientSend(int fd, const char *buffer)
{


	return 0;

}
