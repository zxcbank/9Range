//
// Created by Святослав on 21.03.2024.
//

#ifndef INC_9RANGE_LIB_RANGE_H_
#define INC_9RANGE_LIB_RANGE_H_

#include <iostream>
#include <iterator>
#include <vector>

template <class ContainerT>
    concept AvailabilityOfReverseIterator =
    std::bidirectional_iterator<class ContainerT::reverse_iterator>;

template <class It>
class Range {
    public:
        It __begin;
        It __end;
        
        explicit Range(const It& Xb, const It& Xe) {
            __begin = Xb;
            __end = Xe;
        }
        
        auto begin() const {
            return __begin;
        }
        
        auto end() const {
            return __end;
        }
};

template <class It>
class KeysIteratorAdaptor {
    public:
        using value_type = typename It::value_type::first_type;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = typename It::iterator_category;
        using difference_type = std::ptrdiff_t;
        
        It __main_it;
        
        explicit KeysIteratorAdaptor(const It& Xb){ //TODO: придумать как короче итератор только с кейс
            __main_it = Xb;
        }
        
        reference operator * () {
            return __main_it->first;
        }
        
//        auto operator -> () {
//            return (*this);
//        }
        
        KeysIteratorAdaptor operator++ () {
            return KeysIteratorAdaptor(++__main_it);
        }
        
        KeysIteratorAdaptor operator-- () {
            return KeysIteratorAdaptor(--__main_it);
        }
        
        bool operator == (const KeysIteratorAdaptor& I2) {
            return (this->__main_it == I2.__main_it);
        }
        
        bool operator != (const KeysIteratorAdaptor& I2){
            return !(*this == I2);
        }
        
};

class RangeReverse {
    public:
        RangeReverse() = default;
};

class RangeDrop {
    public:
        int __t;
        
        explicit RangeDrop(int t) : __t(t){};
};

class RangeTake {
    public:
        int __t;
        
        explicit RangeTake(int t) : __t(t){};
};

class RangeKeys {
    public:
        RangeKeys() = default;
};

template <class ContainerT, class OtherTypeT>
auto operator | (const ContainerT& X, const OtherTypeT& Y) {
    
    if constexpr (std::is_same_v<OtherTypeT, RangeDrop>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        while (iter < Y.__t && T.__begin != X.end()) {
            iter++;
            ++T.__begin;
        }
        return T;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeTake>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        T.__end = X.begin();
        while (iter < Y.__t && T.__end != X.end()) {
            
            iter++;
            T.__end++;
        }

        return T;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeReverse>) {
        Range T (X.rbegin(), X.rend());
        return T;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeKeys>) {
        KeysIteratorAdaptor T (X.begin());
        KeysIteratorAdaptor T1 (X.end());
        Range R(T, T1);
        
        return R;
    }
}

RangeTake take (int n) {
    RangeTake obj(n);
    return obj;
}

RangeDrop drop (int n) {
    RangeDrop obj(n);
    return obj;
}

RangeReverse reverse () {
    RangeReverse obj;
    return obj;
}

RangeKeys keys() {
    RangeKeys obj;
    return obj;
}

#endif //INC_9RANGE_LIB_RANGE_H_
