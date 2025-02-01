#ifndef PRACTICE01_DYNAMIC_ARRAY_H
#define PRACTICE01_DYNAMIC_ARRAY_H

#include <iostream>

class DArray {
private:
    unsigned size = 0;
    unsigned capacity = 10;
    int * array = new int[capacity];
public:
    DArray();
    explicit DArray(unsigned size, int value = 0);
    explicit DArray(unsigned, const int*);
    ~DArray();

    DArray& operator= (const DArray&);
    friend std::ostream& operator<< (std::ostream&, DArray&);
    int * operator[] (int);

    int * get(int);
    int find(int);
    void resize(unsigned);
    void append(int);
    void insert(unsigned, int);
    void remove(unsigned);
    [[nodiscard]] unsigned getSize() const;
    [[nodiscard]] unsigned getCapacity() const;
    [[nodiscard]] bool isEmpty() const;
};


#endif
