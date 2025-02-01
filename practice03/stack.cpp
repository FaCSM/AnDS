#include "stack.h"

#include <iostream>


std::ostream& operator<< (std::ostream& os, const Stack& stack) {
    for (const auto& it : stack.items)
        std::cout << it << ' ';
    return os;
}


void Stack::push(std::string &value) {
    items.push_front(value);
    size++;
}


std::string Stack::pop() {
    if (isEmpty()) return "";
    std::string item = items.front();
    items.pop_front();
    size--;
    return item;
}


std::string * Stack::top() {
    if (isEmpty()) return nullptr;
    return &items.front();
}


unsigned Stack::getSize() const {
    return size;
}


bool Stack::isEmpty() const {
    return items.empty();
}