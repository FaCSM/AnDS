#ifndef PRACTICE01_STACK_H
#define PRACTICE01_STACK_H

#include <forward_list>
#include <iostream>
#include "../../practice01/structures/dl_list.h"

class Stack {
private:
    std::forward_list<List> items;
    int size = 0;
public:
    // Operators
    friend std::ostream& operator<< (std::ostream&, const Stack&);

    // Methods
    void push(List&);
    List pop();
    List * top();
    [[nodiscard]] unsigned getSize() const;
    [[nodiscard]] bool isEmpty() const;
};


#endif //PRACTICE01_STACK_H
