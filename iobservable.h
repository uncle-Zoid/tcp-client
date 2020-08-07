#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include <inttypes.h>


class IObservable
{
public:
    IObservable() = default;
    virtual ~IObservable() = default;

    virtual void send(const uint32_t *data, int size) = 0;
    virtual void stop() {};
};


#endif // IOBSERVABLE_H
