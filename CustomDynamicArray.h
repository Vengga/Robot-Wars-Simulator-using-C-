/*******
Program:CustomDynamicArray.h
Course:Object Oriented Programming and Data Structures
Trimester: 2410
Name:Venggadanaathan A/L K.Salvam
ID: 1231303562
Lecture Section: TC4L
Tutorial Section: T14L
Email: 1231303562@student.mmu.edu.my
Phone: 013-2777732
********/

#ifndef CUSTOMDYNAMICARRAY_H
#define CUSTOMDYNAMICARRAY_H

#include <iostream> // For standard input and output
#include <stdexcept> // For standard exceptions like out_of_range

// Template class for a dynamic array
template <typename T>
class CustomDynamicArray {
private:
    T* data; // Pointer to the array data
    size_t capacity; // Capacity of the array
    size_t size; // Current size of the array

    // Method to resize the array to a new capacity
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity]; // Allocate new array
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i]; // Copy old data to new array
        }
        delete[] data; // Delete old array
        data = newData; // Point to new array
        capacity = newCapacity; // Update capacity
    }

public:
    // Constructor to initialize the array with an initial capacity
    CustomDynamicArray(size_t initialCapacity = 10)
        : data(new T[initialCapacity]), capacity(initialCapacity), size(0) {}

        // Copy Constructor
    CustomDynamicArray(const CustomDynamicArray& other)
        : data(new T[other.capacity]), capacity(other.capacity), size(other.size) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i]; // Copy elements from other array
        }
    }

    // Destructor to clean up the allocated memory
    ~CustomDynamicArray() {
        delete[] data;
    }

    // Method to add an element to the end of the array
    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity * 2); // Resize if array is full
        }
        data[size++] = value; // Add value and increment size
    }

    // Method to remove an element at a specific index
    void remove_at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range in remove_at");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1]; // Shift elements to the left
        }
        size--; // Decrement size
    }

    // Operator to access an element by index (non-const version)
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range in operator[]");
        }
        return data[index]; // Return reference to the element
    }

    // Operator to access an element by index (const version)
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range in operator[] const");
        }
        return data[index]; // Return const reference to the element
    }

    // Method to get the current size of the array
    size_t getSize() const {
        return size;
    }

    // Method to set the size of the array
    void setSize(size_t newSize) {
        if (newSize > capacity) {
            resize(newSize); // Resize if new size is greater than capacity
        }
        size = newSize; // Update size
    }
};

#endif // CUSTOMDYNAMICARRAY_H

