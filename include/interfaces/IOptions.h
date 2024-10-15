#ifndef __IOPTION_H
#define __IOPTION_H

template <class T>
class IOption {
    virtual void setOption(T& opt) = 0;
};

#endif