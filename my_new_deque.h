#ifndef MY_NEW_DEQUE_H
#define MY_NEW_DEQUE_H

#include "my_container.h"
#include "my_vector.h"
#include <stdexcept>
#include <iostream>
#include <memory>
constexpr size_t block_size = 4;
template <typename T>
class MyNewDequeIterator
{
public:
    T *cur;
    T **cur_map_pointer;
    size_t index_in_block;
    MyNewDequeIterator(T *cur, T **cur_map_pointer, size_t index_in_block) : cur(cur), cur_map_pointer(cur_map_pointer), index_in_block(index_in_block) {}
    MyNewDequeIterator &operator++()
    {
        if (index_in_block == block_size - 1)
        {
            cur_map_pointer++;
            cur = (*cur_map_pointer);
            index_in_block = 0;
        }
        else
        {
            cur++;
            index_in_block++;
        }
        return *this;
    }
    MyNewDequeIterator &operator--()
    {
        if (index_in_block == 0)
        {
            cur_map_pointer--;
            cur = (*cur_map_pointer)+block_size - 1;
            index_in_block = block_size - 1;
        }
        else
        {
            cur--;
            index_in_block--;
        }
        return *this;
    }
};

template <typename T>
class MyNewDeque : public Container<T>
{
private:
    MyVector<T*> map;
    size_t m_size;
    size_t m_capacity;
    MyNewDequeIterator<T> startIterator;
    MyNewDequeIterator<T> finishIterator;
    void allocate()
    {
        map = MyVector<T*>(1);
        map[0] = new T[block_size];
        startIterator = MyNewDequeIterator<T>(map[0], &map[0],0);
        finishIterator = MyNewDequeIterator<T>(map[0], &map[0],0);
        m_capacity = block_size;
    }
    void reallocate(bool is_back,size_t new_capacity)
    {
        size_t new_map_size = (new_capacity + block_size - 1) / block_size;
        MyVector<T*> new_map(new_map_size);
        size_t current_map_size = map.size();
        size_t start_map_counter = begin().cur_map_pointer - map.begin();
        size_t finish_map_counter = end().cur_map_pointer - map.begin();
        if (is_back)
        {
            for (size_t i = 0; i < current_map_size; ++i)
            {
                new_map[i] = std::move(map[i]);
            }
            for (size_t i = current_map_size; i < new_map_size; ++i)
            {
                new_map[i] = new T[block_size];
            }
            map = std::move(new_map);
            startIterator = MyNewDequeIterator<T>(map[start_map_counter] + startIterator.index_in_block, &map[start_map_counter],startIterator.index_in_block);
            finishIterator = MyNewDequeIterator<T>(map[finish_map_counter]+ finishIterator.index_in_block, &map[finish_map_counter],finishIterator.index_in_block);
        }
        else
        {
            for (size_t i = 0; i < current_map_size; ++i)
            {
                new_map[new_map_size - current_map_size + i] = std::move(map[i]);
            }
            for (size_t i = 0; i < new_map_size - current_map_size; ++i)
            {
                new_map[i] = new T[block_size];
            }
            map = std::move(new_map);
            startIterator = MyNewDequeIterator<T>(map[new_map_size-current_map_size+start_map_counter]+startIterator.index_in_block, &map[new_map_size-current_map_size+start_map_counter],startIterator.index_in_block);
            finishIterator = MyNewDequeIterator<T>(map[new_map_size-current_map_size+finish_map_counter]+finishIterator.index_in_block, &map[new_map_size-current_map_size+finish_map_counter],finishIterator.index_in_block);
        }
        m_capacity = new_capacity;
    }

public:
    MyNewDeque() : m_size(0), m_capacity(0), startIterator(nullptr, nullptr, 0), finishIterator(nullptr, nullptr, 0) {}

    ~MyNewDeque()
    {
        clear();
        for (size_t i = 0; i < map.size(); ++i)
        {
            delete[] map[i];
        }
        map.clear();
        m_capacity = 0;
    }
    MyNewDequeIterator<T> begin()
    {
        return startIterator;
    }
    MyNewDequeIterator<T> end()
    {
        return finishIterator;
    }
    bool empty() const override
    {
        return m_size == 0;
    }
    size_t size() const override
    {
        return m_size;
    }
    size_t capacity() const
    {
        return m_capacity;
    }
    void push_back(const T& value)
    {
        if(m_size==0)
        {
            allocate();
        }
        *finishIterator.cur = value;
        ++finishIterator;
        ++m_size;

        if (m_size == m_capacity || (finishIterator.cur_map_pointer==map.end()-1 && finishIterator.index_in_block==block_size-1))
        {
            reallocate(true, 2 * m_capacity);
        }
    }
    
    void push_front(const T& value)
    {
        if(m_size==0)
        {
            allocate();
        }
        if (m_size == m_capacity || (startIterator.index_in_block == 0&&startIterator.cur_map_pointer==map.begin()))
        {
            reallocate(false, 2 * m_capacity);
        }
        --startIterator;
        *startIterator.cur = value;
        ++m_size;
    }
    void pop_back()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Deque is empty");
        }
        --finishIterator;
        --m_size;
    }
    void pop_front()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Deque is empty");
        }
        ++startIterator;
        --m_size;
    }
    T& back()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Deque is empty");
        }
        return *finishIterator.cur;
    }
    const T& back() const
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Deque is empty");
        }
        return *finishIterator.cur;
    }
    T& front()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Deque is empty");
        }
        return *startIterator.cur;
    }
    const T& front() const
    {
        if (m_size == 0)
        {
            throw std::out_of_range("Deque is empty");
        }
        return *startIterator.cur;
    }
    void clear() override
    {
        while (!empty())
        {
            pop_back();
        }
    }
    void push(const T& value) override
    {
        push_back(value);
    }
    void pop() override
    {
        pop_back();
    }
    T& top() override
    {
        return back();
    }
    const T& top() const override
    {
        return back();
    }
};
#endif
