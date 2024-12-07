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
    Array() : Array(8) { }

    Array(int cap) : curSize(0), capacity(cap) { data = (T*)(malloc(capacity * sizeof(T))); }

    Array(const Array& other) : capacity(other.capacity), curSize(other.curSize)
    {
        data = static_cast<T*>(malloc(capacity * sizeof(T)));

        for (int i = 0; i < curSize; ++i) {
            new (data + i) T(other.data[i]);
        }
    }

    Array(Array&& other) : data(other.data), capacity(other.capacity), curSize(other.curSize)
    {
        other.data = nullptr;
        other.capacity = 0;
        other.curSize = 0;
    }

    ~Array() {
        for (int i = 0; i < curSize; ++i)
            data[i].~T();
        free(data);
    }

    void add_capacity(int new_cap)
    {
        T* new_data = static_cast<T*>(malloc(new_cap * sizeof(T)));

        for (int i = 0; i < curSize; ++i)
        {
            new (new_data + i) T(std::move(data[i]));
            data[i].~T();
        }

        free(data);

        data = new_data;
        capacity = new_cap;
    }

    int insert(const T& value) { return insert(curSize, value); }

    int insert(int index, const T& value) {
        assert(index >= 0 && index <= curSize);

        if (curSize >= capacity) {
            add_capacity(2 * capacity);
        }
        for (int i = curSize; i > index; --i) {
            new (data + i) T(std::move(data[i - 1]));
        }

        new (data + index) T(value);

        ++curSize;
        return index;
    }

    void remove(int index) {
        assert(index >= 0 && index < curSize);

        data[index].~T();

        for (int i = index; i < curSize - 1; ++i) {
            new (data + i) T(std::move(data[i + 1]));
            data[i + 1].~T();
        }
            
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

    Array& operator=(const Array& other)
    {
        Array temp(other);
        my_swap(temp);

        return *this;
    }

    Array& operator=(Array&& other)
    {
        my_swap(other);

        return *this;
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

    void my_swap(Array& other) noexcept
    {
        std::swap(data, other.data);
        std::swap(capacity, other.capacity);
        std::swap(curSize, other.curSize);
    }
};