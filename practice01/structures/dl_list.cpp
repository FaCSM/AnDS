#include "dl_list.h"

#include <iostream>


List::List() = default;



List::List(unsigned size, int value) {
    if (size == 0) return;  // Empty list

    auto *current = new struct Node;
    struct Node *prev = nullptr;
    _head = current;

    for (int i = 0; i < size; ++i) {
        _tail = current;
        current->value = value + i;
        current->prev = prev;

        if (prev) prev->next = current;
        prev = current;

        current = new struct Node;
    }
    current->next = nullptr;
    _size = size;
}


List::List(unsigned size, const int *values) {
    if (size == 0) return;  // Empty list

    auto *current = new struct Node;
    struct Node *prev = nullptr;
    _head = current;

    for (int i = 0; i < size; ++i) {
        _tail = current;
        current->value = *(values + i);
        current->prev = prev;

        if (prev) prev->next = current;
        prev = current;

        current = new struct Node;
    }
    current->next = nullptr;
    _size = size;
}


List::~List() {
    clear();
    delete _head;
    delete _tail;
}


List& List::operator= (const List& rhs) {
    if (this == &rhs) return *this;

    clear();

    Node* current = rhs._head;
    while (current) {
        append(current->value);
        current = current->next;
    }

    return *this;
}

std::ostream& operator<< (std::ostream& os, const List& list) {
    for (struct Node *temp = list._head; temp; temp = temp->next)
        os << temp->value << ' ';
    return os;
}


struct Node * List::operator[](int index) {
    return get(index);
}


void List::clear() {
    while (_head) {
        struct Node *temp = _head;
        _head = _head->next;
        delete temp;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}


void List::append(int value) {
    auto *newNode = new struct Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (isEmpty()) {
        _head = newNode;
        _tail = newNode;
    } else {
        _tail->next = newNode;
        newNode->prev = _tail;
        _tail = newNode;
    }

    _size++;
}



struct Node * List::get(int index) {
    if (isEmpty()) {
        std::cout << "IndexError: The list is empty\n";
        return nullptr;
    } else if (abs(index) > getSize()) {
        std::cout << "IndexError: Index out of range\n";
        return nullptr;
    } else if (index < 0) {
        index = int(getSize()) + index;
    }

    struct Node *node = _head;
    for (unsigned i = 0; i < index; ++i) {
        if (!node->next) {
            std::cout << "IndexError: Index out of range\n";
            return nullptr;
        }
        node = node->next;
    }

    return node;
}


int List::find(int value) {
    if (isEmpty()) return -1;


    struct Node *node = _head;
    for (int i = 0; i < _size; ++i) {
        if (node->value == value) return i;
        if (!node->next) return -1;
        node = node->next;
    }
}



void List::insert(unsigned index, int value) {
    struct Node * found = get(index);


    if (!found) return;


    auto *newNode = new struct Node;
    newNode->value = value;
    newNode->prev = found->prev;
    newNode->next = found;
    if (newNode->prev) newNode->prev->next = newNode;
    if (newNode->next) newNode->next->prev = newNode;
    if (index == 0) _head = newNode;
}


void List::remove(unsigned index) {
    if (isEmpty()) return;


    struct Node *found = get(index);
    if (!found) return;


    found->prev ? found->prev->next = found->next : _head = found->next;
    found->next ? found->next->prev = found->prev : nullptr;
    delete found;
    _size--;
}



void List::swap(unsigned i1, unsigned i2) {

    if (isEmpty() || _head == _tail || i1 == i2) return;


    if (i1 > i2) std::swap(i1, i2);


    struct Node *node1 = get(i1);
    struct Node *node2 = get(i2);
    if (!node1 || !node2) return;


    if (node1 == _head) _head = node2;


    struct Node *temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
    if (node1->next) node1->next->prev = node1;
    if (node2->next) node2->next->prev = node2;


    temp = node1->prev;
    node1->prev = node2->prev;
    node2->prev = temp;
    if (node1->prev) node1->prev->next = node1;
    if (node2->prev) node2->prev->next = node2;
}



unsigned List::getSize() const {
    return _size;
}



bool List::isEmpty() const {
    return _size == 0;
}
