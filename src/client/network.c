/*
** network.c for network in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/client/
**
** Made by Nathan
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 10:13:52 2017 Nathan
** Last update Wed Jul 19 14:35:34 2017 Nathan
*/

// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char *recv_server(int sock)
{
    char *buffer;
    char buf[512];
    int recv = 0;
    fcntl(sock, F_SETFL, O_NONBLOCK);
    if ((buffer = malloc(sizeof(char) * 2)) == NULL)
    	return(NULL);
    memset(buf, '\0', 512);

    while (1) {
        recv = read(sock, buf, 512);
        buffer = realloc(buffer, strlen(buffer) + recv);
        if (recv == -1)
            return buffer;
        strncat(buffer, buf, recv);
        memset(buf, '\0', 512);
        if (recv < 511)
            break;
    }

    return buffer;
}

int socket_connect(const char *ip, const char *port_str)
{
    struct protoent *pe;
    int fd;
    struct sockaddr_in s_in;
    int port;
    port = atoi(port_str);
    pe = getprotobyname("TCP");
    if (!pe)
        return 1;
    fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    if (fd == -1)
        return 1;
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(port);
    s_in.sin_addr.s_addr = inet_addr((strcmp(ip, "localhost") == 0 ? "127.0.0.1" : ip));
    if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
        if (close(fd) == -1)
            return 1;
        return 1;
    }
  	printf("%s\n", "OKAY");
    return fd;
}



char *send_server(int sock, char *str) {
    char *buf;
    while (1) {
        write(sock, str, strlen(str));
        buf = recv_server(sock);
        if (!buf) {
            break;
        }
    }
    printf("%s\n", buf);
    return buf;
}
