/*
 * RemoteVariable.h
 *
 *  Created on: Oct 17, 2014
 *      Author: pavel
 */

#ifndef REMOTEVARIABLE_H_
#define REMOTEVARIABLE_H_

#include <functional>

template<typename T>
class RemoteVariable
{
    using Getter = std::function<T()>;
    using Setter = std::function<void(const T&)>;

    Getter _g;
    Setter _s;

public:
    RemoteVariable(Getter g = {}, Setter s = {}): _g(g), _s(s){}
    virtual ~RemoteVariable() = default;

    operator T() const
    {
        return _g();
    }

    RemoteVariable& operator=(const T& t)
    {
        _s(t);
        return *this;
    }
};

#endif /* REMOTEVARIABLE_H_ */
