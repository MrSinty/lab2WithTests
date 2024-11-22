#include <iostream>
#include <cassert>
#include <cstdlib>
#include <conio.h>
#include <cstring>

template<typename T>
class Array {
private:
    int curSize = 0;
    int capacity = 0;
    T* data = NULL;

public:
    Array() : curSize(0), capacity(8) { data = (T*)(malloc(capacity * sizeof(T))); }

    Array(int cap) : curSize(0), capacity(cap) { data = (T*)(malloc(capacity * sizeof(T))); }

    ~Array() {
        clear();
        curSize = 0;
        free(data);
    }

    int insert(const T& value) { return insert(curSize, value); }

    int insert(int index, const T& value) {
        assert(index >= 0 && index <= curSize);

        if (curSize >= capacity) {
            int newCapacity = capacity * 2;

            T* newData = static_cast<T*>(malloc(newCapacity * sizeof(T)));
            if (!newData) {
                throw std::bad_alloc();
            }

            for (int i = 0; i < index; ++i)
                new (newData + i) T(std::move(data[i]));
            new (newData + index) T(value);
            for (int i = index; i < curSize; ++i)
                new (newData + i + 1) T(std::move(data[i]));

            clear();
            free(data);

            data = newData;
            capacity = newCapacity;
        }
        else {
            for (int i = curSize; i > index; --i)
                data[i] = std::move(data[i - 1]);
            data[index] = value;
        }

        ++curSize;
        return index;
    }

    void remove(int index) {
        assert(index >= 0 && index < curSize);

        for (int i = index; i < curSize - 1; ++i)
            data[i] = std::move(data[i + 1]);

        --curSize;
    }

    const T& operator[](int index) const {
        assert(index >= 0 && index < curSize);
        return data[index];
    }

    T& operator[](int index) {
        assert(index >= 0 && index < curSize);
        return data[index];
    }

    int size() const {
        return curSize;
    }

    class Iterator {
    private:
        T* ptr;
        T* end;
        bool isNotReverse = false;

    public:
        Iterator(T* ptr, T* end, bool isNotReverse) : ptr(ptr), end(end), isNotReverse(isNotReverse) {}

        const T& get() const { return *ptr; }

        void set(const T& value) { *ptr = value; }

        void next() {
            if (isNotReverse)
                ++ptr;
            else
                --ptr;
        }

        bool hasNext() const { return ptr != end; }

        T& operator*() { return *ptr; }

        Iterator& operator++() {
            if (isNotReverse)
                ++ptr;
            else
                --ptr;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            if (isNotReverse)
                ++ptr;
            else
                --ptr;
            return temp;
        }

        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    class ConstIterator {
    private:
        const T* ptr;
        const T* end;
        bool isNotReverse = false;

    public:
        ConstIterator(const T* ptr, const T* end, bool isNotReverse) :
            ptr(ptr), end(end), isNotReverse(isNotReverse) {}

        const T& get() const { return *ptr; }

        void next() {
            if (isNotReverse)
                ++ptr;
            else
                --ptr;
        }

        bool hasNext() const { return ptr != end; }

        const T& operator*() const { return *ptr; }

        ConstIterator& operator++() {
            if (isNotReverse)
                ++ptr;
            else
                --ptr;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            if (isNotReverse)
                ++ptr;
            else
                --ptr;
            return temp;
        }

        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
    };

    Iterator iterator() { return Iterator(data, data + curSize, true); }
    ConstIterator iterator() const { return ConstIterator(data, data + curSize, true); }
    Iterator reverseIterator() { return Iterator(data + curSize - 1, data - 1, false); }
    ConstIterator reverseIterator() const { return ConstIterator(data + curSize - 1, data - 1, false); }
    Iterator begin() { return Iterator(data, data + curSize, true); }
    ConstIterator cbegin() const { return ConstIterator(data, data + curSize, true); }
    Iterator end() { return Iterator(data + curSize, data, true); }
    ConstIterator cend() const { return ConstIterator(data + curSize, data, true); }

private:
    void clear() {
        for (int i = 0; i < curSize; ++i)
            data[i].~T();
    }
};