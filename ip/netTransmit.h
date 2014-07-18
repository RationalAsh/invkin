#ifndef NETTRANSMIT_H
#define NETTRANSMIT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class netTransmit
{
public:
    netTransmit(const char* UDP_IP, int port);
    
    //Send UDP data
    void transmit(const char* msg);

private:
    int fd;
    struct sockaddr_in servaddr;
};

netTransmit::netTransmit(const char* UDP_IP, int port)
{
    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	cerr<<"Cannot create socket!"<<endl;
    }

    memset((char *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(UDP_IP);
    servaddr.sin_port = htons(port);
}

void netTransmit::transmit(const char* msg)
{
    sendto(fd, msg, strlen(msg), 0, (struct sockaddr *)&servaddr,
	   sizeof(servaddr));
}


#endif
