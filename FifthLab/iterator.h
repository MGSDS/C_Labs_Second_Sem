//
// Created by Bill Williams on 4/16/21.
//

#ifndef FIFTHLAB_ITERATOR_H
#define FIFTHLAB_ITERATOR_H

#include <iterator>
template<typename T>
class iter : public std::iterator<std::random_access_iterator_tag, T> {
protected:
    T* _ptr;
private:
    typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type diff_type;
public:
    iter() : _ptr(nullptr) {}
    explicit iter(T& element) : _ptr(&element){}
    iter(const iter<T> &rhs) : _ptr(rhs._ptr) {}

    inline iter<T>& operator=(const iter<T> &rhs) {_ptr = rhs._ptr; return *this;}

    inline iter<T>& operator+=(diff_type rhs) {_ptr += rhs; return *this;}
    inline iter<T>& operator-=(diff_type rhs) {_ptr -= rhs; return *this;}
    inline iter<T>& operator++() {++_ptr; return *this;}
    inline iter<T>& operator--() {--_ptr; return *this;}
    inline iter<T> operator++(int) {iter<T> tmp(*this); ++_ptr; return tmp;}
    inline iter<T> operator--(int) {iter<T> tmp(*this); --_ptr; return tmp;}
    inline iter<T> operator+(const iter<T>& rhs) {return iter<T>(_ptr+rhs.ptr);}
    inline iter<T> operator-(const iter<T>& rhs) {return iter<T>(_ptr-rhs.ptr);}
    inline iter<T> operator+(diff_type rhs) {return iter<T>(_ptr+rhs);}
    inline iter<T> operator-(diff_type rhs) {return iter<T>(_ptr-rhs);}
    friend inline iter<T> operator+(diff_type lhs, const iter<T>& rhs) {return iter<T>(lhs+rhs._ptr);}
    friend inline iter<T> operator-(diff_type lhs, const iter<T>& rhs) {return iter<T>(lhs-rhs._ptr);}

    inline T& operator*() {return *_ptr;}
    inline T* operator->() {return _ptr;}

    inline T& operator[](diff_type rhs) {return _ptr[rhs];}

    inline bool operator<=>(const iter<T> rhs){return _ptr <=> rhs._ptr;}

private:
    explicit iter(T* rhs) : _ptr(rhs) {}

};



#endif //FIFTHLAB_ITERATOR_H
