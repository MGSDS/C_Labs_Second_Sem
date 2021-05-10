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
    size_type _capacity;
    iterator _begin;
    iterator _end;
    size_type _beginPos;
    //value_type* front;

public:
    explicit CircularBuffer(size_type sz = 0,value_type x = value_type()) : _size(sz), _capacity(sz + 5), _beginPos(0){
        _array = new value_type[_capacity];
        for (size_type i = 0; i < _size; ++i) {
            _array[i] = x;
        }
        _begin = iterator(_array[0], _capacity, _array[0], _beginPos);
        _end = iterator(_array[0], _capacity, _array[0], _beginPos);
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
        _capacity = bf._capacity;
        _begin = bf._begin;
        _end = bf._end;
        _beginPos = bf._beginPos;
        delete[] tmp2;
        return this;
    }

    CircularBuffer& operator=(const CircularBuffer<value_type>& bf){
        *this = CircularBuffer(bf);
        return *this;
    }

    ~CircularBuffer(){
        delete[] _array;
    }

    bool operator==(const CircularBuffer<value_type>& bf){
        if(bf._size != _size)
            return false;
        iterator b = bf.begin();
        for(iterator a = begin() ; a != end(); ++a){
            if(a != b)
                return false;
            ++b;
        }
        return true;
    }

    bool operator!=(const CircularBuffer<value_type> bf){
        return !(this == bf);
    }

    iterator begin(){
        return iterator(_begin);
    }

    iterator end(){
        return iterator(_end);
    }



    iterator cbegin(){
        return const_iterator(_begin);
    }

    iterator cend(){
        return const_iterator(_end);
    }

    [[nodiscard]] size_type size(){
        return _size;
    }

    size_type capacity(){
        return _capacity;
    }

    void push_back(const_reference value){
        if(_capacity - 1 == _size)
            reserve(_size + 10);
        *_end++ = (T) value;
        _size++;
    }

    void push_front(const_reference value){
        if(_capacity - 1 == _size)
            reserve(_size + 10);
        *--_begin = (T) value;
        _beginPos = _beginPos - 1 >= 0 ? _beginPos - 1 :  _beginPos - 1 + _capacity;
        _size++;
    }
    void pop_front(){
        if(_begin == _end)
            throw std::range_error("CircularBuffer is empty");
        _begin++;
        _beginPos = _beginPos + 1 < _capacity ? _beginPos + 1 :  _beginPos + 1 - _capacity;
        _size--;
    }
    void pop_back(){
        if(_begin == _end)
            throw std::range_error("CircularBuffer is empty");
        _end--;
        _size--;
    }

    void insert(size_type position, const_reference value) {
        position = position % (_size + 1);
        if(_capacity <= _size + 1){
            reserve(_size + 10);
        }
        if (position < _size){
            for (iterator i = _end; i != _begin + position; --i) {
                T& tmp = *i;
                tmp = *(i - 1);
            }
        }
        T& tmp = *(_begin + position);
        tmp = value;
        ++_size;
        ++_end;
    }

    void clear(){
        _size = 0;
        _beginPos = 0;
        _begin = iterator(_array[0], _capacity, _array[0], _beginPos);
        _end = iterator(_array[_size], _capacity, _array[0], _beginPos);
    }

    bool empty() {
        return _size == 0;
    }

    void reserve(size_type n){
        if(_capacity >= n + 1){
            return;
        }
        auto* tmp = new value_type[n + 1];
        value_type* tmp2 = _array;
        _capacity = n + 1;
        _size = _size <= _capacity ? _size : _capacity;
        for (size_type i = 0; i < _size; ++i) {
            tmp[i] = *(_begin + i);
        }
        _array = tmp;
        delete[] tmp2;
        _beginPos = 0;
        _begin = iterator(_array[0], _capacity, _array[0], _beginPos);
        _end = iterator(_array[_size], _capacity, _array[0], _beginPos);
    }

    void resize(size_type n, value_type x = value_type()){
        auto* tmp = new value_type[n];
        value_type* tmp2 = _array;
        _capacity = n + 1;
        _size = _size <= _capacity - 1 ? _size : _capacity - 1;
        for (size_type i = 0; i < _size; ++i) {
            tmp[i] = *(_begin + i);
        }
        for(int i = _size; i < _capacity - 1; ++i){
            tmp[i] = x;
        }
        _array = tmp;
        delete[] tmp2;
        _size = n;
        _beginPos = 0;
        _begin = iterator(_array[0], _capacity, _array[0], _beginPos);
        _end = iterator(_array[_size], _capacity, _array[0], _beginPos);
    }

    reference operator[](size_type pos){
        return *(_begin + pos);
    }

    reference at(size_type pos){
        return operator[](pos % _size);
    }
};

#endif //FIFTHLAB_CIRCULARBUFFER_H
