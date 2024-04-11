//
// Created by Святослав on 21.03.2024.
//

#ifndef INC_9RANGE_LIB_RANGE_H_
#define INC_9RANGE_LIB_RANGE_H_

#include <iostream>
#include <iterator>
#include <vector>
#include <functional>

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
        
        explicit KeysIteratorAdaptor(const It& Xb){
            __main_it = Xb;
        }
        explicit KeysIteratorAdaptor() = default;
        
        reference operator * () {
            return __main_it->first;
        }
        
        auto operator -> () {
            return (*this);
        }
        
        KeysIteratorAdaptor operator++ () {
            ++__main_it;
            return *this;
        }
        
        KeysIteratorAdaptor operator-- () {
            --__main_it;
            return *this;
        }
        
        KeysIteratorAdaptor operator++ (int) {
            KeysIteratorAdaptor t = *this;
            ++*this;
            return t;
        }
        
        KeysIteratorAdaptor operator-- (int) {
            KeysIteratorAdaptor t = *this;
            --*this;
            return t;
        }
        
        bool operator == (const KeysIteratorAdaptor& I2) {
            return (this->__main_it == I2.__main_it);
        }
        
        bool operator != (const KeysIteratorAdaptor& I2){
            return !(*this == I2);
        }
        
};
template <class It, class func>
    class FilterIteratorAdaptor {
        public:
            using value_type = typename It::value_type;
            using pointer = value_type*;
            using reference = value_type&;
            using iterator_category = typename It::iterator_category;
            using difference_type = std::ptrdiff_t;
            
            It __main_it;
            It __end_it;
            func __f;
            
            explicit FilterIteratorAdaptor(const It& Xb, func foo, const It& Xend){
                __main_it = Xb;
                __end_it = Xend;
                __f = foo;
            }
            explicit FilterIteratorAdaptor() = default;
            
            reference operator * () {
                return *__main_it;
            }
            
            auto operator -> () {
                return (*this);
            }
            
            FilterIteratorAdaptor operator++ () {
                ++__main_it;
                while (!__f(*__main_it) && (__end_it != __main_it)) {
                    ++*this;
                }
                return *this;
            }
            
            FilterIteratorAdaptor operator-- () {
                --__main_it;
                return *this;
            }
            
            FilterIteratorAdaptor operator++ (int) {
                FilterIteratorAdaptor t = *this;
                ++*this;
                return t;
            }
            
            FilterIteratorAdaptor operator-- (int) {
                FilterIteratorAdaptor t = *this;
                --*this;
                return t;
            }
            
            bool operator == (const FilterIteratorAdaptor& I2) {
                return (this->__main_it == I2.__main_it);
            }
            
            bool operator != (const FilterIteratorAdaptor& I2){
                return !(this->__main_it == I2.__main_it);
            }
    };

template <class It, class func>
    class IteratorAdaptor {
        public:
            using value_type = typename It::value_type;
            using pointer = value_type*;
            using reference = value_type&;
            using iterator_category = typename It::iterator_category;
            using difference_type = std::ptrdiff_t;
            
            It __main_it;
            func __f;
            
            explicit IteratorAdaptor(const It& Xb, func foo){
                __main_it = Xb;
                __f = foo;
            }
            explicit IteratorAdaptor() = default;
            
            reference operator * () {
                auto t = *__main_it;
                *__main_it = __f(t);
                return *__main_it;
            }
            
            auto operator -> () {
                return (*this);
            }
            
            IteratorAdaptor operator++ () {
                ++__main_it;
                return *this;
            }
            
            IteratorAdaptor operator-- () {
                --__main_it;
                return *this;
            }
            
            IteratorAdaptor operator++ (int) {
                IteratorAdaptor t = *this;
                ++*this;
                return t;
            }
            
            IteratorAdaptor operator-- (int) {
                IteratorAdaptor t = *this;
                --*this;
                return t;
            }
            
            bool operator == (const IteratorAdaptor& I2) {
                return (this->__main_it == I2.__main_it);
            }
            
            bool operator != (const IteratorAdaptor& I2){
                return !(*this == I2);
            }
};

template <class It>
    class ValuesIteratorAdaptor {
        public:
            using value_type = typename It::value_type::second_type;
            using pointer = value_type*;
            using reference = value_type&;
            using iterator_category = typename It::iterator_category;
            using difference_type = std::ptrdiff_t;
            
            It __main_it;
            
            explicit ValuesIteratorAdaptor(const It& Xb){ //TODO: придумать как короче итератор только с кейс
                __main_it = Xb;
            }
            explicit ValuesIteratorAdaptor() = default;
            
            reference operator * () {
                return __main_it->second;
            }
            
            auto operator -> () {
                return (*this);
            }
            
            ValuesIteratorAdaptor& operator++ () {
                ++__main_it;
                return *this;
            }
            
            ValuesIteratorAdaptor operator++ (int) {
                ValuesIteratorAdaptor t = *this;
                ++*this;
                return t;
            }
            
            ValuesIteratorAdaptor& operator-- () {
                --__main_it;
                return *this;
            }
            
            ValuesIteratorAdaptor operator-- (int) {
                
                ValuesIteratorAdaptor t = *this;
                --*this;
                return t;
                
            }
            
            bool operator == (const ValuesIteratorAdaptor& I2) {
                return (this->__main_it == I2.__main_it);
            }
            
            bool operator != (const ValuesIteratorAdaptor& I2){
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

class RangeValues {
    public:
        RangeValues() = default;
};

template<class func = std::identity>
class RangeTransform {
    public:
        using function = func;
        func __f;
        RangeTransform(func f) : __f(f) {} ;
        RangeTransform() = default;
        
        template<class func2>
        auto operator() (){
            
            return;
        }
};

template<class func = std::identity>
    class RangeFilter {
        public:
            using function = func;
            
            func __f;
            RangeFilter(func f) : __f(f) {} ;
            RangeFilter() = default;
            
            template<class func2>
            auto operator() (){
                
                return;
            }
    };


template <class ContainerT, class OtherTypeT>
auto operator | (ContainerT&& X, const OtherTypeT& Y) {
    
    if constexpr(std::is_same_v<OtherTypeT, RangeDrop>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        while (iter < Y.__t && T.__begin != X.end()) {
            iter++;
            ++T.__begin;
        }
        return T;
    } else if constexpr(std::is_same_v<OtherTypeT, RangeTake>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        T.__end = X.begin();
        while (iter < Y.__t && T.__end != X.end()) {
            
            iter++;
            T.__end++;
        }

        return T;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeReverse>) {
        Range T (std::reverse_iterator(X.end()), std::reverse_iterator(X.begin()));
        return T;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeKeys>) {
        KeysIteratorAdaptor<typename ContainerT::iterator> T (X.begin());
        KeysIteratorAdaptor<typename ContainerT::iterator> T1 (X.end());
        Range R(T, T1);

        return R;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeValues>) {
        ValuesIteratorAdaptor<typename ContainerT::iterator> T (X.begin());
        ValuesIteratorAdaptor<typename ContainerT::iterator> T1 (X.end());
        Range R(T, T1);
        
        return R;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeTransform<typename OtherTypeT::function>>) {
        IteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T (X.begin(), Y.__f);
        IteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T1 (X.end(), Y.__f);
        
        Range R(T, T1);
        return R;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeFilter<typename OtherTypeT::function>>) {
        FilterIteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T (X.begin(), Y.__f, X.end());
        FilterIteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T1 (X.end(), Y.__f, X.end());
    
        Range R(T, T1);
        return R;
    }
}

template <class ContainerT, class OtherTypeT>
auto operator | (ContainerT& X, const OtherTypeT& Y) {
    
    if constexpr(std::is_same_v<OtherTypeT, RangeDrop>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        while (iter < Y.__t && T.__begin != X.end()) {
            iter++;
            ++T.__begin;
        }
        return T;
    } else if constexpr(std::is_same_v<OtherTypeT, RangeTake>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        T.__end = X.begin();
        while (iter < Y.__t && T.__end != X.end()) {
            
            iter++;
            T.__end++;
        }
        
        return T;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeReverse>) {
        Range T (std::reverse_iterator(X.end()), std::reverse_iterator(X.begin()));
        return T;
    }
    else if constexpr (std::is_same_v<OtherTypeT, RangeKeys>) {
        KeysIteratorAdaptor<typename ContainerT::iterator> T (X.begin());
        KeysIteratorAdaptor<typename ContainerT::iterator> T1 (X.end());
        Range R(T, T1);
        
        return R;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeValues>) {
        ValuesIteratorAdaptor<typename ContainerT::iterator> T (X.begin());
        ValuesIteratorAdaptor<typename ContainerT::iterator> T1 (X.end());
        Range R(T, T1);
        
        return R;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeTransform<typename OtherTypeT::function>>) {
        IteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T (X.begin(), Y.__f);
        IteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T1 (X.end(), Y.__f);
        
        Range R(T, T1);
        return R;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeFilter<typename OtherTypeT::function>>) {
        FilterIteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T (X.begin(), Y.__f, X.end());
        FilterIteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T1 (X.end(), Y.__f, X.end());
        
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

RangeValues values() {
    RangeValues obj;
    return obj;
}

template<class func>
RangeTransform<func> transform(func f) {
    RangeTransform obj(f);
    return obj;
}

template<class func>
RangeFilter<func> filter(func f) {
    RangeFilter obj(f);
    return obj;
}

#endif //INC_9RANGE_LIB_RANGE_H_