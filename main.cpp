#include <iostream>
#include <chrono>

#include "client.h"
using namespace std;
using namespace std::chrono;

int main()
{
    uint16_t port = 55555;
    const char *ip = "192.168.1.137"; //"127.0.0.1";

    Client c;
    if(!c.connect(ip, port))
    {
        printf("CANNTO CONNECT TO: %s:%d\n", ip, port);
        exit(1);
    }
    char buffer[512];
    int r = 0;

    while(1)
    {
        if((r = c.recv(buffer, sizeof(buffer))) > 0)
        {
            c.write(buffer, r);

            std::time_t t = std::time(NULL);
            std::tm* now = std::localtime(&t);

            printf("%02d:%02d:%02d: ", now->tm_hour, now->tm_min, now->tm_sec);
            for(char *it = buffer; it != (buffer + r); ++it)
            {
                printf("%02X ", *it);
            }
            printf("\n");
            fflush(stdout);
        }
    }

    return 0;
}
