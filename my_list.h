#ifndef MY_LIST_H
#define MY_LIST_H
#include "my_container.h"

template <typename T>
class MyList : public Container<T> {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data, Node* next, Node* prev) : data(data), next(next), prev(prev) {}
    };
    class MyListIterator {
    private:
        Node* cur;
    public:
        MyListIterator(Node* cur) : cur(cur) {}
        T& operator*() const {
            return cur->data;
        }
        MyListIterator& operator++() {
            if (cur) {
                cur = cur->next;
            }
            else {
                throw std::out_of_range("Iterator out of range");
            }
            return *this;
        }
        MyListIterator operator++(int) {
            MyListIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        MyListIterator& operator--() {
            if (cur&&cur->prev) {
                cur = cur->prev;
            }
            else {
                throw std::out_of_range("Iterator out of range");
            }
            return *this;
        }
        MyListIterator operator--(int) {
            MyListIterator tmp = *this;
            --(*this);
            return tmp;
        }
        Node* operator->() const {
            return cur;
        }
        bool operator==(const MyListIterator& other) const {
            return cur == other.cur;
        }
        bool operator!=(const MyListIterator& other) const {
            return cur != other.cur;
        }
    };
    MyList() : head(new Node(T(), nullptr, nullptr)), tail(head), m_size(0) {}
    ~MyList() noexcept override {
        clear();
        if(head) {
            delete head;
            head = nullptr;
        }
    }
    void clear() override {
        if(head == nullptr) {
            return;
        }
        Node* current = head->next;  // 从哨兵节点的下一个节点开始
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
        head->next = nullptr;  // 确保哨兵节点的 next 指针被重置
        tail = head;  // 如果 tail 是哨兵节点，重置为 head
        m_size = 0;
    }
    void push(const T& value) override {
        push_back(value);
    }
    void push_back(const T& value)  {
        Node* new_node = new Node(value, nullptr, tail);
        std::cout<<2<<std::endl;
        if (head == tail) {
            head->next = new_node;
        }
        std::cout<<3<<std::endl;
        tail->next = new_node;
        std::cout<<4<<std::endl;
        tail = new_node;
        std::cout<<5<<std::endl;
        m_size++;
    }
    void insert_after(Node* pos, const T& value)  {
        if(!pos) {
            throw std::out_of_range("Iterator out of range");
        }
        if(pos == tail) {
            push_back(value);
        }
        else {
            Node* new_node = new Node(value, pos->next, pos);
            if(pos->next) {
                pos->next->prev = new_node;
            }
            pos->next = new_node;
            m_size++;
        }
    }
    void insert_before(Node* pos, const T& value)  {
        if(!pos||pos == head) {
            throw std::out_of_range("Iterator out of range");
        }
        if(pos->prev) {
            insert_after(pos->prev, value);
            m_size++;
        }
        else{
            throw std::out_of_range("Iterator out of range");
        }

    }

    void push_front(const T& value)  {
        insert_after(head, value);
    }
    void pop() override {
        pop_back();
    }
    void pop_back() {
        if (tail == head) {
            throw std::out_of_range("List is empty");
        }
        Node* tmp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete tmp;
        m_size--;
    }
    void erase(Node* pos) {
        if(!pos||pos == head) {
            throw std::out_of_range("Iterator out of range");
        }
        if(pos == tail) {
            pop_back();
        }
        else {
            if(pos->next) {
                pos->next->prev = pos->prev;
            }
            if(pos->prev) {
                pos->prev->next = pos->next;
            }
            delete pos;
            m_size--;
        }
    }
    void pop_front() {
        erase(head->next);
    }
    size_t size() const override {
        return m_size;
    }
    bool empty() const override {
        return m_size == 0;
    }
    T& top() override {
        return tail->data;
    }
    const T& top() const override {
        return tail->data;
    }
    

    MyListIterator begin() const {
        return MyListIterator(head->next);
    }
    MyListIterator before_begin() const {
        return MyListIterator(head);
    }
    MyListIterator end() const {
        return MyListIterator(nullptr);
    }


    


private:
    Node* head;
    Node* tail = head;
    size_t m_size;
};
#endif // MY_LIST_H

