#ifndef CLIENT_H
#define CLIENT_H

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <errno.h>
#include <vector>
#include <inttypes.h>

class Client
{
    int fd_;


public:
    Client();

    Client(Client &cl) = delete;
    Client(const Client &cl) = delete;
    void operator =(Client &d) = delete;
    void operator =(const Client &d) = delete;

    Client(Client &&cl)
    {
        swap(cl);
    }

    void operator =(Client &&d)
    {
        swap(d);
    }
    void swap(Client &d)
    {
        std::swap(fd_, d.fd_);
        d.fd_ = -1;
    }

    ~Client();

    int write(const char *data, int size);
    int recv(char *buffer, int size);
    bool connect(const char *ip, uint16_t port);
};


#endif // CLIENT_H
