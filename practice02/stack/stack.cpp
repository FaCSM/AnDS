#include "stack.h"
#include <iostream>


/// Print the stack
std::ostream& operator<< (std::ostream& os, const Stack& stack) {
    for (const auto& it : stack.items)
        std::cout << it << "; ";
    return os;
}


/// Add element to the end of the stack
void Stack::push(List &list) {
    items.push_front(list);
    size++;
}


/// Return top item and remove it from stack
List Stack::pop() {
    if (isEmpty()) return List(0);
    List list = items.front();
    items.pop_front();
    size--;
    return list;
}


/// Return top item without removing it
List * Stack::top() {
    if (isEmpty()) return nullptr;
    return &items.front();
}


/// Return size of the stack
unsigned Stack::getSize() const {
    return size;
}


/// Return false if stack is empty else true
bool Stack::isEmpty() const {
    return items.empty();
}