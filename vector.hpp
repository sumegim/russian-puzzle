#pragma once

#include <cstdlib>


template <typename T>
class ConstFastVector {
protected:
    T* items;
    size_t itemNum;

public:
    ConstFastVector(const T array[], size_t array_size)
        : items((T*)array)
        , itemNum(array_size)
    {}

    size_t size() const {
        return itemNum;
    }

    T& operator[](size_t idx) const {
        return items[idx];
    }
protected:
    void freeMyelf() {
        free(items);
    }
};

template <typename T>
class FastVector : public ConstFastVector<T>{
    static const size_t DEF_ALLOC = 15;

    size_t allocated;

public:
    FastVector()
        : ConstFastVector<T>(static_cast<T*>(malloc(sizeof(T)*DEF_ALLOC)), 0)
        , allocated(DEF_ALLOC)
    {}

    FastVector(const FastVector& other)
        : ConstFastVector<T>(static_cast<T*>(malloc(sizeof(T)*other.itemNum)), other.itemNum)
        , allocated(other.itemNum)
    {
        memcpy(this->items, other.items, ConstFastVector<T>::itemNum*sizeof(T));
    }

    ~FastVector() {
        ConstFastVector<T>::freeMyelf();
    }

    FastVector& operator=(const FastVector& other) {
        this->items = static_cast<T*>(malloc(sizeof(T)*other.itemNum));
        this->itemNum = other.itemNum;
        this->allocated = other.itemNum;
        memcpy(this->items, other.items, ConstFastVector<T>::itemNum*sizeof(T));
        return *this;
    }

    void push(const T& item) {
        if (allocated < ConstFastVector<T>::itemNum + 1)
            reallocate();

        ConstFastVector<T>::items[ConstFastVector<T>::itemNum] = item;
        ConstFastVector<T>::itemNum++;
    }

    void pop(T* item = nullptr) {
        if (item)
            *item = ConstFastVector<T>::items[ConstFastVector<T>::itemNum-1];

        ConstFastVector<T>::itemNum--;
    }

private:
    void reallocate() {
        ConstFastVector<T>::items = static_cast<T*>(realloc(
            ConstFastVector<T>::items,
            sizeof(T)*ConstFastVector<T>::itemNum*2)
        );
        allocated *= 2;
    }
};
