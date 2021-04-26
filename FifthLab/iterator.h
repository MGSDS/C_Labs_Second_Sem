//
// Created by Bill Williams on 4/16/21.
//

#ifndef FIFTHLAB_ITERATOR_H
#define FIFTHLAB_ITERATOR_H

#include <iterator>
#include <compare>
template<typename T>
class iter : public std::iterator<std::random_access_iterator_tag, T> {
protected:
    T* _ptr;

public:
    typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
    typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type value_type;
    typedef typename std::iterator<std::random_access_iterator_tag, T>::reference reference;
    iter() : _ptr(nullptr) {}
    explicit iter(reference rhs) : _ptr(&rhs){}
    iter(const iter& rhs) : _ptr(rhs._ptr) {}

    
    inline iter& operator=(const iter& rhs){this->_ptr = rhs._ptr; return *this;}


    inline T& operator*() {return *_ptr;}
    inline T* operator->() {return _ptr;}
    inline iter& operator++(){++_ptr; return *this;}
    inline iter operator++(int){iter tmp = *this; ++*this; return tmp;}
    inline iter& operator--(){--_ptr; return *this;}
    inline iter operator--(int){iter tmp = *this; --*this; return tmp;}


    iter& operator+=(int n){
        difference_type m = n;
        if (m >= 0) while (m--) ++*this;
        else while (m++) --*this;
        return *this;
    }
    inline iter operator+(int n){iter temp = *this; return temp += n;}
    friend inline iter operator+(int n, const iter<T>& it){iter temp = it; return temp += n;}

    inline iter& operator-=(int n){return *this += -n;}
    inline iter operator-(int n){return *this += -n;}
    friend inline difference_type operator-(const iter<T>& lhs, const iter<T>& rhs){return lhs._ptr - rhs._ptr;}

    inline value_type& operator[](difference_type rhs) {return *(_ptr + rhs);}

    auto operator<=>(const iter<T>& rhs) const =default;
//    friend bool operator == (const iter<T>& lhs, const iter<T>& rhs){return lhs._ptr == rhs._ptr;}
//    friend bool operator <= (const iter<T>& lhs, const iter<T>& rhs){return lhs._ptr <= rhs._ptr;}
//    friend bool operator < (const iter<T>& lhs, const iter<T>& rhs){return lhs._ptr < rhs._ptr;}
//    friend bool operator != (const iter<T>& lhs, const iter<T>& rhs){return !(lhs == rhs);}
//    friend bool operator >= (const iter<T>& lhs, const iter<T>& rhs){return lhs <= rhs;}
//    friend bool operator > (const iter<T>& lhs, const iter<T>& rhs){return lhs < rhs;}

    friend void swap (iter<T>& lhs, iter<T>& rhs){
        T tmp = *rhs;
        *rhs = *lhs;
        *lhs = tmp;
    }

};


#endif //FIFTHLAB_ITERATOR_H
