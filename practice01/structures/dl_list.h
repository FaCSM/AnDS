#ifndef PRACTICE01_DL_LIST_H
#define PRACTICE01_DL_LIST_H

#include <iostream>

/// Node structure represents a node in a Doubly-Linked List
struct Node {
    int value = 0;
    struct Node *next = nullptr;
    struct Node *prev = nullptr;
};


class List {
private:
    struct Node *_head = nullptr;
    struct Node *_tail = nullptr;
    unsigned _size = 0;
public:
    // Constructors and destructor
    List();
    explicit List(unsigned size, int value = 0);
    explicit List(unsigned, const int*);
    ~List();

    // Operators
    List& operator= (const List&);
    friend std::ostream& operator<< (std::ostream&, const List&);
    struct Node * operator[] (int);

    // Methods
    void clear();
    struct Node * get(int);
    int find(int);
    void append(int);
    void insert(unsigned, int);
    void remove(unsigned);
    void swap(unsigned, unsigned);
    [[nodiscard]] unsigned getSize() const;
    [[nodiscard]] bool isEmpty() const;
};


#endif //PRACTICE01_DL_LIST_H
