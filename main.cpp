#include <iostream>
#include "my_vector.h"
#include "my_stack.h"
#include "container.h"

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

    std::cout << "Testing MyVector:" << std::endl;
    testContainer(vec);

    std::cout << "\nTesting Stack:" << std::endl;
    testContainer(stack);

    return 0;
}