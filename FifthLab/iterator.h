//
// Created by Bill Williams on 4/16/21.
//

#ifndef FIFTHLAB_ITERATOR_H
#define FIFTHLAB_ITERATOR_H

#include <iterator>
#include <compare>
template<typename T>
class iter : public std::iterator<std::random_access_iterator_tag, T> {

public:
    typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
    typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type value_type;
    typedef typename std::iterator<std::random_access_iterator_tag, T>::reference reference;

protected:
    T* _ptr;
    unsigned int* _capacity;
    T* _front;
    unsigned int* _beginPos;

public:

    iter() : _ptr(nullptr), _front(nullptr), _capacity(nullptr), _beginPos(nullptr){}
    iter(const iter& rhs) : _ptr(rhs._ptr), _capacity(rhs._capacity), _front(rhs._front), _beginPos(rhs._beginPos) {}


    
    iter& operator=(const iter& rhs){
        _front = rhs._front;
        _ptr = rhs._ptr;
        _capacity = rhs._capacity;
        _beginPos = rhs._beginPos;
        return *this;
    }

    inline T& operator*() {return *_ptr;}
    inline T* operator->() {return _ptr;}
    iter& operator++(){
        if(_ptr >= _front + *_capacity - 1)
            _ptr = _front;
        else
            ++_ptr;
        return *this;}
    inline iter operator++(int){iter tmp = *this; ++*this; return tmp;}

    iter& operator--(){
        if(_ptr <= _front)
            _ptr = _front + *_capacity - 1;
        else
            --_ptr;
        return *this;
    }
    inline iter operator--(int){iter tmp = *this; --*this; return tmp;}


    iter& operator+=(difference_type n){
        if(n != 0) {
            difference_type ptrPos = std::distance(_front, _ptr);;
            difference_type newPtrPos = (ptrPos + n) % *_capacity;
            if (newPtrPos < 0)
                newPtrPos = *_capacity + newPtrPos;
            _ptr += newPtrPos - ptrPos;
        }
//        if(n < 0){
//            while (n++) --*this;
//        }
//        else {
//            while (n--) ++*this;
//        }
        return *this;
    }
    inline iter operator+(difference_type n){iter temp = *this; return temp += n;}
    friend inline iter operator+(difference_type n, const iter<T>& it){iter temp = it; return temp += n;}
    friend inline iter operator+(const iter<T>& it, difference_type n){iter temp = it; return temp += n;}

    iter& operator-=(difference_type n){return *this += -n;}
    friend inline iter operator-(const iter<T>& it, difference_type n){iter temp = it; return temp += -n;}
    friend inline difference_type operator-(const iter<T>& it, reference ref){return it._ptr - &ref;}
    friend inline difference_type operator-(const iter<T>& lhs, const iter<T>& rhs){return lhs._ptr - rhs._ptr;}

    inline value_type& operator[](difference_type rhs) {return *(_ptr + rhs);}

    friend bool operator == (const iter<T>& lhs, const iter<T>& rhs){return lhs._ptr == rhs._ptr;}
    friend bool operator == (const iter<T>& lhs, reference rhs){return lhs._ptr == rhs;}
    friend bool operator != (const iter<T>& lhs, const iter<T>& rhs){return !(lhs._ptr == rhs._ptr);}

    friend bool operator < (const iter<T>& lhs, const iter<T>& rhs){
        return lhs.getPtrPos() < rhs.getPtrPos();
    }
    friend bool operator <= (const iter<T>& lhs, const iter<T>& rhs){return lhs < rhs || lhs == rhs;}
    friend bool operator >= (const iter<T>& lhs, const iter<T>& rhs){return !(lhs < rhs);}
    friend bool operator > (const iter<T>& lhs, const iter<T>& rhs){return lhs >= rhs && lhs != rhs;}

    friend void swap (iter<T>& lhs, iter<T>& rhs){
        T tmp = *rhs;
        *rhs = *lhs;
        *lhs = tmp;
    }

    friend class CircularBuffer;

private:
    explicit iter(reference rhs,  unsigned int& capacity, reference front, unsigned int& beginPos) : _ptr(&rhs), _front(&front), _capacity(&capacity), _beginPos(&beginPos){}
    [[nodiscard]]
    unsigned int getPtrPos() const{
        difference_type PtrPos = std::distance(_front, _ptr);
        difference_type dist = PtrPos - *_beginPos;
        if(dist < 0){
            return *_capacity - dist;
        }
        return dist;
    }
};


#endif //FIFTHLAB_ITERATOR_H
