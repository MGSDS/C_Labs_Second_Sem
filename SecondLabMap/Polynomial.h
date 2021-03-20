//
//  Polynomial.hpp
//  SecondLab
//
//  Created by Bill Williams on 2/23/21.
//

#ifndef Polynomial_h
#define Polynomial_h

#include <string>
#include <sstream>
#include <unordered_map>

template <typename T> class Polynomial {
protected:
    std::unordered_map<size_t, T> coefficients;

public:
    Polynomial() = default;

    ~Polynomial() = default;

    bool operator==(const Polynomial<T>& obj){
        return coefficients == obj.coefficients;
    }

    Polynomial(const Polynomial<T> &obj) {
        this->coefficients = obj.coefficients;
    }

    Polynomial<T>& operator=(const Polynomial<T> &obj) {
        this->coefficients = obj.coefficients;
        return *this;
    }

    Polynomial<T> operator+(const Polynomial<T> &obj) {
        Polynomial tmp = *this;
        tmp += obj;
        return tmp;

    }

    Polynomial<T> operator-(const Polynomial<T> &obj) {
        Polynomial tmp = *this;
        tmp -= obj;
        return tmp;

    }

    Polynomial<T> operator*(const Polynomial<T> &obj) {
        Polynomial tmp = *this;
        tmp *= obj;
        return tmp;
    }

    void operator+=(const Polynomial<T> &obj) {
        std::unordered_map<size_t, T> tmp;
        tmp = this->coefficients;
        for (std::pair<size_t, T> i : obj.coefficients) {
            if (tmp.find(i.first) != tmp.end()) {
                tmp.at(i.first) += i.second;
            } else {
                tmp.insert(i);
            }
            if (tmp.at(i.first) == 0) {
                tmp.erase(*tmp.at(i.first));
            }
        }
        coefficients = tmp.coefficients;
    }

    void operator-=(const Polynomial<T> &obj) {
        std::unordered_map<size_t, T> tmp;
        tmp = this->coefficients;
        for (std::pair<size_t, T> i : obj.coefficients) {
            if (tmp.find(i.first) != tmp.end()) {
                tmp.at(i.first) -= i.second;
            } else {
                tmp.insert(-i);
            }
            if (tmp.at(i.first) == 0) {
                tmp.erase(*tmp.at(i.first));
            }

        }
        coefficients = tmp.coefficients;
    }

    void operator*=(const Polynomial<T> &obj) {
        std::unordered_map<size_t, T> tmp;
        tmp = this->coefficients;
        for (std::pair<size_t, T> i : obj.coefficients) {
            if (tmp.find(i.first) != tmp.end()) {
                tmp.at(i.first) *= i.second;
                if (tmp.at(i.first) == 0) {
                    tmp.erase(*tmp.at(i.first));
                }
            }
        }

        coefficients = tmp.coefficients;
    }

    Polynomial<T> operator+(T n) {
        Polynomial tmp = *this;
        tmp += n;
        return tmp;
    }

    Polynomial<T> operator-(T n) {
        Polynomial tmp = *this;
        tmp -= n;
        return tmp;
    }

    Polynomial<T> operator*(T n) {
        Polynomial tmp = *this;
        tmp *= n;
        return tmp;
    }

    Polynomial<T> operator/(T n) {
        Polynomial tmp = *this;
        tmp /= n;
        return tmp;
    }

    void operator+=(T n) {
        if (coefficients.find(0) != coefficients.end()) {
            coefficients.at(0) += n;
        } else {
            coefficients.insert(std::make_pair(0, n));
        }
        if (coefficients.at(0) == 0) {
            coefficients.erase(*coefficients.at(0));
        }
    }

    void operator-=(T n) {
        if (coefficients.find(0) != coefficients.end()) {
            coefficients.at(0) -= n;
        } else {
            coefficients.insert(std::make_pair(0, -n));
        }
        if (coefficients.at(0) == 0) {
            coefficients.erase(*coefficients.at(0));
        }
    }

    void operator*=(T n) {
        if (coefficients.find(0) != coefficients.end()) {
            coefficients.at(0) *= n;
        }
        if (coefficients.at(0) == 0) {
            coefficients.erase(*coefficients.at(0));
        }
    }

    void operator/=(T n) {
        if (n == 0)
            throw std::invalid_argument("Division by 0");
        if (coefficients.find(0) != coefficients.end()) {
            coefficients.at(0) /= n;
        }
        if (coefficients.at(0) == 0) {
            coefficients.erase(*coefficients.at(0));
        }
    }

    T &operator[](size_t n) {
        if (coefficients.find(n) != coefficients.end()) {
            coefficients.insert(std::make_pair(n, 0));
        }
        return coefficients.at(n);
    }

    friend std::ostream &operator<<(std::ostream &os, const Polynomial<T> &obj) {
        for (auto i : obj.coefficients) {
            if (i.second > 0)
                os << '+' << i.second << '*' << (i.first ? 'x' << '^' << i.first : 1);
            else if (i.second < 0)
                os << i.second << '*' << 'x' << '^' << i.first;
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Polynomial<T> &obj) {
        std::unordered_map<size_t, T> tmp;
        size_t pow;
        T coef;
        size_t n;
        is >> n;
        for (int i = 0; i < n; ++i) {
            is >> pow;
            is >> coef;
            tmp.insert(std::make_pair(pow, coef));
        }
        obj.coefficients = tmp;
        return is;

    }
};

#endif /* Polynomial_h */
