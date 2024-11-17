#ifndef MY_STACK_H
#define MY_STACK_H

#include "my_container.h"
#include "my_vector.h"

//注意这里Container为模版参数，将具体的stack实现定义为MyVector
template <typename T, typename Container = MyVector<T> >
class MyStack : public Container {
public:
    void push(const T& value) {
        Container::push(value); //用MyVector的push
    }

    void pop() {
        if (!this->empty()) {
            Container::pop();
        }
    }

    T& top() {
        return Container::top();
    }

    const T& top() const {
        return Container::top();
    }

    bool empty() const {
        return Container::empty();
    }

    size_t size() const {
        return Container::size();
    }
};

#endif // MY_STACK_H

