#include <iostream>
#include <vector>

namespace custom_general_algo {

    template<class InputIt, class T>
    bool all_of(InputIt first, InputIt last, const T &pred) {
        for (InputIt i = first; i < last; ++i) {
            if (!pred(*i)) {
                return false;
            }
        }
        return true;
    }

    template<class InputIt, class T>
    bool any_of(InputIt first, InputIt last, const T &pred) {
        for (InputIt i = first; i < last; ++i) {
            if (pred(*i)) {
                return true;
            }
        }
        return false;
    }

    template<class InputIt, class T>
    bool none_of(InputIt first, InputIt last, const T &pred) {
        for (InputIt i = first; i < last; ++i) {
            if (pred(*i)) {
                return false;
            }
        }
        return true;
    }

    template<class InputIt, class T>
    bool one_of(InputIt first, InputIt last, const T &pred) {
        size_t count = 0;
        for (InputIt i = first; i < last; ++i) {
            if (pred(*i)) {
                count++;
            }
            if (count > 1)
                return false;
        }
        return count == 1;
    }

    template<class InputIt, class T>
    bool is_sorted(InputIt first, InputIt last, const T &pred) {
        for (InputIt i = first; i < last - 1; ++i) {
            if (!pred(*i, *(i + 1))) {
                return false;
            }
        }
        return true;
    }

    template<class InputIt, class T>
    bool is_partitioned(InputIt first, InputIt last, const T &pred) {
        bool flag = false;
        bool predres = pred(*first);
        for (InputIt i = first+1; i < last; ++i) {
            if (pred(*i) != predres) {
                if(!flag){
                    flag = true;
                    predres = pred(*i);
                }
                else{
                    return false;
                }
            }
        }
        return flag;
    }

    template<class InputIt, typename T>
    InputIt find_not(InputIt first, InputIt last, const T &element) {
        for (InputIt i = first; i < last; ++i) {
            if(*i != element){
                return i;
            }
        }
        return last;
    }

    template<class InputIt, typename T>
    InputIt find_backward(InputIt first, InputIt last, const T &element) {
        for (InputIt i = last - 1; i >= first; --i) {
            if(*i == element){
                return i;
            }
        }
        return last;
    }

    template<class InputIt>
    bool is_palindrome(InputIt first, InputIt last) {
        for (size_t i = 0; i <= (last - first) / 2; ++i) {
            if(*(first + i) != *(last - i - 1)){
                return false;
            }
        }
        return true;
    }

}
struct Comp1{
    bool operator()(const int &a) const{
        return a < 5;
    }
};

struct Comp2{
    bool operator()(const int &a, const int &b) const{
        return a < b;
    }
};

int main() {
    std::vector<int> arr = {1, 2, 5, 6, -1};
    std::cout << custom_general_algo::all_of(arr.begin(), arr.end(), Comp1()) << std::endl;
    std::cout << custom_general_algo::any_of(arr.begin(), arr.end(), Comp1()) << std::endl;
    std::cout << custom_general_algo::none_of(arr.begin(), arr.end(), Comp1()) << std::endl;
    std::cout << custom_general_algo::one_of(arr.begin(), arr.end(), Comp1()) << std::endl;
    std::cout << custom_general_algo::is_sorted(arr.begin(), arr.end(), Comp2()) << std::endl;
    std::cout << custom_general_algo::is_partitioned(arr.begin(), arr.end(), Comp1()) << std::endl;
    std::cout << ((custom_general_algo::find_not(arr.begin(), arr.end(), 5)) != arr.end()) << std::endl;
    std::cout << ((custom_general_algo::find_backward(arr.begin(), arr.end(), 5)) != arr.end()) << std::endl;
    std::cout << custom_general_algo::is_palindrome(arr.begin(), arr.end()) << std::endl;

    return 0;
}
