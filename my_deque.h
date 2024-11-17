#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include "my_container.h"
#include "my_vector.h"
#include <stdexcept>

template <typename T>
class MyDequeIterator {
private:
    T* first;
    T* last;
    T* cur;
    T** node;
    size_t m_index;

public:
    MyDequeIterator(T* first, T* last, T* cur, T** node, size_t index)
        : first(first), last(last), cur(cur), node(node), m_index(index) {}

    T& operator*() const {
        return *cur;
    }

    MyDequeIterator<T>& operator++() {
        ++cur;
        if (cur == last) {
            ++node;
            cur = *node;
            last = *node + m_index;
        }
        return *this;
    }

    MyDequeIterator<T> operator++(int) {
        MyDequeIterator<T> tmp = *this;
        ++(*this);
        return tmp;
    }

    MyDequeIterator<T>& operator--() {
        if (cur == first) {
            --node;
            cur = *node + m_index - 1;
            first = *node;
        }
        --cur;
        return *this;
    }

    MyDequeIterator<T> operator--(int) {
        MyDequeIterator<T> tmp = *this;
        --(*this);
        return tmp;
    }

    T* operator->() const {
        return cur;
    }

    bool operator==(const MyDequeIterator<T>& other) const {
        return cur == other.cur;
    }

    bool operator!=(const MyDequeIterator<T>& other) const {
        return cur != other.cur;
    }
};

template <typename T>
class MyDeque : public Container<T> {
private:
    size_t m_size;
    size_t m_capacity;
    size_t block_capacity;
    size_t iterator_count;

    MyVector<T*> map;
    T* start;
    T* finish;

    MyDequeIterator<T> start_iterator;
    MyDequeIterator<T> end_iterator;

    void reallocate_right(size_t new_capacity) {
        size_t new_iterator_count = (new_capacity + block_capacity - 1) / block_capacity;
        MyVector<T*> new_map(new_iterator_count);

        size_t current_iterator_count = (m_capacity + block_capacity - 1) / block_capacity;
        for (size_t i = 0; i < current_iterator_count; ++i) {
            new_map[i] = map[i];
        }
        size_t start_index = static_cast<size_t>(start - map[0]);
        size_t finish_index = static_cast<size_t>(finish - map[0]);
        start = map[0] + start_index;
        finish = map[0] + finish_index;
        map = std::move(new_map);
        m_capacity = new_capacity;
        iterator_count = new_iterator_count;
    }

    void reallocate_left(size_t new_capacity) {
        size_t new_iterator_count = (new_capacity + block_capacity - 1) / block_capacity;
        MyVector<T*> new_map(new_iterator_count);
        for (size_t i = 0; i < new_iterator_count; ++i) {
            new_map[i] = map[i];
        }
        size_t start_index = static_cast<size_t>(start - map[0] + new_iterator_count - 1);
        size_t finish_index = static_cast<size_t>(finish - map[0] + new_iterator_count - 1);
        start = new_map[0] + start_index;
        finish = new_map[0] + finish_index;

        map = std::move(new_map);
        m_capacity = new_capacity;
        iterator_count = new_iterator_count;
    }

public:
    MyDeque() : m_size(0), m_capacity(0), block_capacity(0), iterator_count(1),
        start(nullptr),
        finish(nullptr),
        start_iterator(nullptr, nullptr, nullptr, nullptr, block_capacity),
        end_iterator(nullptr, nullptr, nullptr, nullptr, block_capacity) 
        {
        map = MyVector<T*>(1);
        map[0] = new T[block_capacity];
        start = map[0];
        finish = map[0];
        start_iterator = MyDequeIterator<T>(start, finish, start, &map[0], block_capacity);
        end_iterator = MyDequeIterator<T>(start, finish, finish, &map[0], block_capacity);
        }

    
    void push_back(const T& value) {
        if (m_size == m_capacity || finish == (map[iterator_count - 1] + block_capacity)) {
            reallocate_right(m_capacity == 0 ? 1 : 2 * m_capacity);
        }
        *finish = value;
        ++finish;
        ++m_size;
        end_iterator = MyDequeIterator<T>(start, finish, finish, &map[iterator_count - 1], block_capacity);
    }

    void push_front(const T& value) {
        if (m_size == m_capacity || start == *(map[0])) {
            reallocate_left(m_capacity == 0 ? 1 : 2 * m_capacity);
        }
        --start;
        *start = value;
        ++m_size;
        start_iterator = MyDequeIterator<T>(start, finish, start, &map[0], block_capacity);
    }

    void pop_back() {
        if (m_size == 0) {
            throw std::out_of_range("Deque is empty");
        }
        --finish;
        --m_size;
        end_iterator = MyDequeIterator<T>(start, finish, finish, &map[iterator_count - 1], block_capacity);
    }

    void pop_front() {
        if (m_size == 0) {
            throw std::out_of_range("Deque is empty");
        }
        --m_size;
        ++start;
        start_iterator = MyDequeIterator<T>(start, finish, start, &map[0], block_capacity);
    }

    T& operator[](size_t index) {
        if(index >= m_size){
            throw std::out_of_range("Index out of range");
        }
        return *(start + index);
    }

    const T& operator[](size_t index) const {
        if(index >= m_size){
            throw std::out_of_range("Index out of range");
        }
        return *(start + index);
    }

    T& at(size_t index) {
        if(index >= m_size){
            throw std::out_of_range("Index out of range");
        }
        return *(start + index);
    }

    const T& at(size_t index) const {
        if(index >= m_size){
            throw std::out_of_range("Index out of range");
        }
        return *(start + index);
    }

    MyDequeIterator<T> begin() {
        return start_iterator;
    }

    MyDequeIterator<T> end() {
        return end_iterator;
    }

    T& front() {
        return *start;
    }

    const T& front() const {
        return *start;
    }

    T& back() {
        return *(finish - 1);
    }

    const T& back() const {
        return *(finish - 1);
    }

    bool empty() const override {
        return m_size == 0;
    }

    size_t size() const override {
        return m_size;
    }

    void clear() override {
        m_size = 0;
        start = finish = nullptr;
        for (size_t i = 0; i < iterator_count; ++i) {
            delete[] map[i];
            map[i] = nullptr;
        }
        map.clear();
        m_capacity = 0;
        iterator_count = 0;
    }

    void push(const T& value) override {
        push_back(value);
    }

    void pop() override {
        pop_back();
    }

    T& top() override {
        return back();
    }

    const T& top() const override {
        return back();
    }

};
#endif // MY_DEQUE_H

