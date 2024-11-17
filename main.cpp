#include <iostream>
#include "my_vector.h"
#include "my_stack.h"
#include "my_container.h"
#include "my_deque.h"
#include "my_list.h"

void testContainer(Container<int>& container) {
    std::cout << "Testing container:" << std::endl;
    
    // 添加元素
    for (int i = 0; i < 5; ++i) {
        container.push(i);
    }

    // 显示大小
    std::cout << "Size: " << container.size() << std::endl;

    // 显示顶部元素
    std::cout << "Top element: " << container.top() << std::endl;

    // 弹出元素
    container.pop();

    // 再次显示大小和顶部元素
    std::cout << "Size after pop: " << container.size() << std::endl;
    std::cout << "New top element: " << container.top() << std::endl;
}

void testList(MyList<int>& list) {
    std::cout << "\nTesting MyList:" << std::endl;

    // 测试 push_back 和 push_front
    for (int i = 0; i < 5; ++i) {
        std::cout << i*100 << std::endl;
        list.push_back(i);
    }
    for (int i = 5; i < 10; ++i) {
        list.push_front(i);
    }

    // 显示链表内容
    std::cout << "List contents: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 pop_back 和 pop_front
    list.pop_back();
    list.pop_front();

    // 显示链表内容
    std::cout << "List contents after pop: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 size 和 empty
    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "Is list empty? " << (list.empty() ? "Yes" : "No") << std::endl;

    // 测试 clear
    list.clear();
    std::cout << "List size after clear: " << list.size() << std::endl;
    std::cout << "Is list empty after clear? " << (list.empty() ? "Yes" : "No") << std::endl;
}

void testDeque(MyDeque<int>& deque) {
    std::cout << "\nTesting MyDeque:" << std::endl;
    
    std::cout << (deque.size()) << std::endl;
    std::cout << (deque.empty()) << std::endl;
    
    for (int i = 0; i < 100; ++i) {
        deque.push_back(i);
        std::cout << "Deque size after push_back: " << deque.size() << std::endl;
    }
    
    std::cout << "Deque size after push_back: " << deque.size() << std::endl;
    std::cout << "Front element: " << deque.front() << std::endl;
    std::cout << "Back element: " << deque.back() << std::endl;

    for (int i = 0; i < 50; ++i) {
        deque.pop_front();
    }
    
    std::cout << "Deque size after pop_front: " << deque.size() << std::endl;
    std::cout << "Front element: " << deque.front() << std::endl;

    for (int i = 0; i < 10; ++i) {
        deque.pop_back();
    }
    
    std::cout << "Deque size after pop_back: " << deque.size() << std::endl;
    for (int i = 0; i < deque.size(); ++i) {
        std::cout << deque[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Deque size after push_front: " << deque.size() << std::endl;
    deque.clear();
    std::cout << "Deque size after clear: " << deque.size() << std::endl;
    std::cout << (deque.size()) << std::endl;
    std::cout << (deque.empty()) << std::endl;
    
    for (int i = 0; i < 20; i++) {
        deque.push_front(i * i);
    }
    for (int i = 0; i < 20; i++) {
        deque.push_back(i * i * i);
    }
    
    std::cout << (deque.start_iterator == deque.end_iterator) << std::endl;
    std::cout << "Deque size after push_back: " << deque.size() << std::endl;
    for (int i = 0; i < deque.size(); i++) {
        std::cout << deque.at(i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    MyVector<int> vec;
    MyStack<int> stack;
    MyDeque<int> deque;
    MyList<int> list;

    std::cout << "Testing MyVector:" << std::endl;
    testContainer(vec);

    std::cout << "\nTesting Stack:" << std::endl;
    testContainer(stack);

    testDeque(deque);

    // 测试 MyList
    testList(list);

    return 0;
}
