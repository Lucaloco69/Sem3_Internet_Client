#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <network.h>
#include <errno.h>
#include <util.h>
#include <time.h>


int receiveMessage(const int fd, Message *msg) {
    if (msg == NULL) {
        errno = EINVAL;
        return -1;
    }

    memset(msg, 0, sizeof(*msg));

    if (recv(fd, msg, sizeof(msg->type) + sizeof(msg->length), MSG_WAITALL) <= 0) {
        return -1;
    }

    msg->length = ntohs(msg->length);

    if (msg->length < 0 || (size_t)msg->length > sizeof(Message) - 3) {
        errno = EINVAL;
        return -1;
    }

    if (recv(fd, ((char*)msg) + 3, msg->length, MSG_WAITALL) <= 0) {
        return -1;
    }

    if(msg->type == 0) {
        msg->LRQ.magic = ntohl(msg->LRQ.magic);
    }

    return 0;
}

int sendMessage(const int fd, Message *msg)
{
	printf("In sende Message\n");

    if(msg->type == 1) {
        msg->LRE.magic = htonl(msg->LRE.magic);
    } else if(msg->type == 3) {
        msg->S2C.timestamp = hton64u(time(NULL));
    } else if(msg->type == 4) {
        msg->UAD.timestamp = hton64u(time(NULL));
    } else if(msg->type == 5) {
        msg->URM.timestamp = hton64u(time(NULL));
    }

    if (msg->length <= 40 && msg->type == 3) {
        int padding = 40 - msg->length;
        msg->length += padding + strlen(msg->S2C.text);
    }

    const ssize_t messageSize = msg->length + sizeof(msg->type) + sizeof(msg->length);
    msg->length = htons(msg->length);

    if (send(fd, msg, messageSize, 0) < 0) {
        msg->LRE.code = 255;
        send(fd, &msg, msg->length, 0);
        return -1;
    }
    return 0;
}
