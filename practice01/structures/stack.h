#ifndef PRACTICE01_STACK_H
#define PRACTICE01_STACK_H


#include <forward_list>
#include <string>
#include <iostream>

class Stack {
private:
    std::forward_list<std::string> items;
    int size = 0;
public:


    friend std::ostream& operator<< (std::ostream&, const Stack&);

    void push(std::string &value);
    std::string pop();
    std::string * top();
    [[nodiscard]] unsigned getSize() const;
    [[nodiscard]] bool isEmpty() const;
};


#endif
