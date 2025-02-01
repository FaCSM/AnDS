#include "dynamic_array.h"


DArray::DArray() = default;


DArray::DArray(unsigned n, int value) {
    size = n;
    capacity = size * 2;
    array = new int[capacity];
    for (unsigned i = 0; i < size; ++i)
        array[i] = value;
}


DArray::DArray(unsigned n, const int* values) {
    size = n;
    capacity = size * 2;
    array = new int[capacity];
    for (unsigned i = 0; i < size; ++i)
        array[i] = values[i];
}


DArray::~DArray() {
    delete[] array;
}


DArray& DArray::operator= (const DArray& rhs) {
    if (this == &rhs) return *this;

    delete[] array;

    size = rhs.size;
    capacity = rhs.capacity;
    array = new int[capacity];
    for (int i = 0; i < size; ++i)
        array[i] = rhs.array[i];

    return *this;
}


std::ostream& operator<< (std::ostream& os, DArray& arr) {
    for (int i = 0; i < arr.getSize(); ++i)
        std::cout << *arr[i] << ' ';
    return os;
}


int * DArray::operator[] (int index) {
    return get(index);
}


int * DArray::get(int index) {
    if (isEmpty()) {
        std::cout << "IndexError: Массив пуст\n";
        return nullptr;
    } else if (abs(index) > getSize()) {
        std::cout << "IndexError: Index out of range\n";
        return nullptr;
    } else if (index < 0) {
        index = int(getSize()) + index;
    }

    return &array[index];
}


int DArray::find(int value) {
    for (int i = 0; i < getSize(); ++i)
        if (array[i] == value) return i;
    return -1;
}


void DArray::resize(unsigned newSize) {
    if (newSize == size)
        return;

    if (newSize < size) {
        size = newSize;
        if (size < capacity / 2)
            capacity /= 2;
        return;
    }

    if (newSize > capacity) {
        capacity *= 2;

        int * newArray = new int[capacity];
        for (unsigned i = 0; i < size; ++i)
            newArray[i] = array[i];

        delete[] array;
        array = newArray;
    }

    for (unsigned i = size; i < newSize; ++i)
        array[i] = 0;

    size = newSize;
}


void DArray::append(int value) {
    resize(size + 1);
    array[size - 1] = value;
}


void DArray::insert(unsigned index, int value) {
    if (index >= size) {
        std::cout << "IndexError: Индекс вне диапазона\n";
        return;
    }

    resize(size + 1);
    for (unsigned i = size - 1; i > index; --i)
        array[i] = array[i - 1];

    array[index] = value;
}


void DArray::remove(unsigned index) {
    if (index >= size) {
        std::cout << "IndexError: Индекс вне диапазона\n";
        return;
    }

    for (unsigned i = index; i < size - 1; ++i)
        array[i] = array[i + 1];
    resize(size - 1);
}


unsigned DArray::getSize() const {
    return size;
}


unsigned DArray::getCapacity() const {
    return capacity;
}


bool DArray::isEmpty() const {
    return size == 0;
}