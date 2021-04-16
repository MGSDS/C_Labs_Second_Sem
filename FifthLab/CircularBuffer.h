//
// Created by Bill Williams on 4/8/21.
//

#ifndef FIFTHLAB_CIRCULARBUFFER_H
#define FIFTHLAB_CIRCULARBUFFER_H
#include "iterator.h"

template<typename T>
class CircularBuffer {

public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef iter<T> iterator;
    typedef const iter<T> const_iterator;
    typedef signed int difference_type;
    typedef unsigned int size_type;

private:
    value_type* _array;
    size_type _size;
    size_type _maxSize;

public:
    explicit CircularBuffer(size_type sz = 0,value_type x = value_type()) : _size(sz), _maxSize(sz + 5){
        _array = new value_type[sz];
        for (size_type i = 0; i < _size; ++i) {
            _array[i] = x;
        }
    }

    CircularBuffer(const CircularBuffer<value_type>& bf){
        auto* tmp = new value_type[bf._size];
        for (size_type i = 0; i < bf._size; ++i) {
            tmp[i] = bf[i];
        }
        value_type* tmp2 = _array;
        _array = tmp;
        _array = bf._array;
        _size = bf._size;
        _maxSize = bf._maxSize;
        delete[] tmp2;
        return this;
    }

    CircularBuffer& operator=(const CircularBuffer<value_type>& bf){
        this = CircularBuffer(bf);
        return *this;
    }

    ~CircularBuffer(){
        delete[] _array;
    }

    bool operator==(const CircularBuffer<value_type>& bf){
        if(bf._size != _size)
            return false;
        for (size_type i = 0; i < bf._size; ++i)
            if (_array[i] != bf._array[i])
                return false;
        return true;
    }

    bool operator!=(const CircularBuffer<value_type> bf){
        return !(this == bf);
    }

    iterator begin(){
        return iterator(_array[0]);
    }

    iterator end(){
        return iterator(_array[_size]);
    }



    iterator cbegin(){
        return const_iterator(_array[0]);
    }

    iterator cend(){
        return const_iterator(_array[_size]);
    }

    [[nodiscard]] size_type size(){
        return _size;
    }

    size_type max_size(){
        return _maxSize;
    }

    void push_back(const_reference value){
        reserve(_size + 1);
        _array[_size++] = value;
    }

    void insert(const_reference value, size_type position) {
        if (position < _size){
            reserve(_size + 1);
            for (size_type i = _size - 1; i > position; --i) {
                _array[i] = _array[i-1];
            }
        }
        else {
            reserve(position + 1);
        }
        _array[position] = value;
    }

    void clear(){
        _size = 0;
    }

    bool empty() {
        return _size == 0;
    }

    void reserve(size_type n){
        if(_maxSize < n)
            resize(n);
    }

    void resize(size_type n){
        auto* tmp = new value_type[n];
        value_type* tmp2 = _array;
        _maxSize = n;
        _size = _size <= _maxSize ? _size : _maxSize;
        for (size_type i = 0; i < _size; ++i) {
            tmp2[i] = tmp[i];
        }
        for (size_type i = 0; i < _size; ++i) {
            tmp2[i] = tmp[i];
        }
        delete[] tmp2;
        _array = tmp;
    }

    reference operator[](size_type pos){
        return _array[pos];
    }

    reference at(size_type pos){
        return operator[](pos % _size);
    }
};

#endif //FIFTHLAB_CIRCULARBUFFER_H
