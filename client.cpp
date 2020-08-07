#include "client.h"
#include <algorithm>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <netdb.h>
#include <strings.h>
#include <cstring>

#include <chrono>

using namespace std;
using namespace std::chrono;

Client::Client()
    : fd_           (-1)
{}

Client::~Client()
{
    if(fd_>=0)
    {
        std::cout << "Client close" << std::endl;
        ::close(fd_);
    }
}


bool Client::connect(const char *ip, uint16_t port)
{
    struct hostent *he;
    struct sockaddr_in serverAddress;


    if ((he=gethostbyname(ip)) == NULL)
    {
        herror("gethostbyname");
        return false;
    }

    if ((fd_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return false;
    }

    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr = *((struct in_addr *)he->h_addr);

    if (::connect(fd_, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        return false;
    }

    return true;
}

int Client::write(const char *data, int size)
{
    return ::write(fd_, data, size);
}


///
/// \brief Client::recv
/// \param buffer
/// \param size
/// \return -1 ... error
///
int Client::recv(char *buffer, int size)
{
    return ::recv(fd_, buffer, size, 0);
}
