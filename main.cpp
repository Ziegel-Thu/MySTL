#include <iostream>
#include "my_vector.h"
#include "my_stack.h"
#include "my_container.h"
#include "my_deque.h"

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

int main() {
    MyVector<int> vec;
    MyStack<int> stack;
    MyDeque<int> deque;

    std::cout << "Testing MyVector:" << std::endl;
    testContainer(vec);

    std::cout << "\nTesting Stack:" << std::endl;
    testContainer(stack);

    std::cout << "\nTesting MyDeque:" << std::endl;
    // 测试 MyDeque
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

    for (int i = 0; i < 50; ++i) {
        deque.pop_back();
    }
    std::cout << "Deque size after pop_back: " << deque.size() << std::endl;

    deque.clear();
    std::cout << "Deque size after clear: " << deque.size() << std::endl;

    return 0;
}
