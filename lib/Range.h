//
// Created by Святослав on 21.03.2024.
//

#ifndef INC_9RANGE_LIB_RANGE_H_
#define INC_9RANGE_LIB_RANGE_H_

#include <iostream>
#include <iterator>
#include <vector>
#include <functional>
#pragma once



template <class It>
class Range {
    public:
        It _begin;
        It _end;
        
        explicit Range(const It& Xb, const It& Xe) {
            _begin = Xb;
            _end = Xe;
        }
        
        auto begin() const {
            return _begin;
        }
        
        auto end() const {
            return _end;
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
        
        It _main_it;
        
        explicit KeysIteratorAdaptor(const It& Xb){
            _main_it = Xb;
        }
        explicit KeysIteratorAdaptor() = default;
        
        reference operator * () {
            return _main_it->first;
        }
        
        auto operator -> () {
            return (*this);
        }
        
        KeysIteratorAdaptor operator++ () {
            ++_main_it;
            return *this;
        }
        
        KeysIteratorAdaptor operator-- () {
            --_main_it;
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
            return (this->_main_it == I2._main_it);
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
            
            It main_it;
            It end_it;
            func f;
            
            explicit FilterIteratorAdaptor(const It& Xb, func foo, const It& Xend){
                main_it = Xb;
                end_it = Xend;
                f = foo;
            }
            explicit FilterIteratorAdaptor() = default;
            
            reference operator * () {
                if (!f(*main_it)) {
                    ++*this;
                }
                return *main_it;
            }
            
            auto operator -> () {
                return (*this);
            }
            
            FilterIteratorAdaptor operator++ () {
                ++main_it;
                while (!f(*main_it) && (end_it != main_it)) {
                    ++*this;
                }
                return *this;
            }
            
            FilterIteratorAdaptor operator-- () {
                --main_it;
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
                return (this->main_it == I2.main_it);
            }
            
            bool operator != (const FilterIteratorAdaptor& I2){
                return !(this->main_it == I2.main_it);
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
            
            It main_it;
            func f;
            
            explicit IteratorAdaptor(const It& Xb, func foo){
                main_it = Xb;
                f = foo;
            }
            
            IteratorAdaptor() = default;
            
            value_type operator * () {
                
                return f(*main_it);
            }
            
            auto operator -> () {
                return (*this);
            }
            
            IteratorAdaptor operator++ () {
                ++main_it;
                return *this;
            }
            
            IteratorAdaptor operator-- () {
                --main_it;
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
                return (this->main_it == I2.main_it);
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
            
            It main_it;
            
            explicit ValuesIteratorAdaptor(const It& Xb){
                main_it = Xb;
            }
            explicit ValuesIteratorAdaptor() = default;
            
            reference operator * () {
                return main_it->second;
            }
            
            auto operator -> () {
                return (*this);
            }
            
            ValuesIteratorAdaptor& operator++ () {
                ++main_it;
                return *this;
            }
            
            ValuesIteratorAdaptor operator++ (int) {
                ValuesIteratorAdaptor t = *this;
                ++*this;
                return t;
            }
            
            ValuesIteratorAdaptor& operator-- () {
                --main_it;
                return *this;
            }
            
            ValuesIteratorAdaptor operator-- (int) {
                
                ValuesIteratorAdaptor t = *this;
                --*this;
                return t;
                
            }
            
            bool operator == (const ValuesIteratorAdaptor& I2) {
                return (this->main_it == I2.main_it);
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
        int quantity;
        
        explicit RangeDrop(int t) : quantity(t){};
};

class RangeTake {
    public:
        int quantity;
        
        explicit RangeTake(int t) : quantity(t){};
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
        func foo;
        explicit RangeTransform(func f) : foo(f) {} ;
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
            
            func foo;
            explicit RangeFilter(func f) : foo(f) {} ;
            RangeFilter() = default;
            
            template<class func2>
            auto operator() (){
                
                return;
            }
    };

template<class U>
    concept AcceptableTypeEasy = (std::is_same_v<U, RangeTake> ||
        std::is_same_v<U, RangeDrop> ||
            std::is_same_v<U, RangeReverse> ||
                std::is_same_v<U, RangeKeys> ||
                    std::is_same_v<U, RangeValues> ||
                std::is_same_v<U, RangeTransform<typename U::function>> ||
            std::is_same_v<U, RangeFilter<typename U::function>>);


template <class ContainerT, AcceptableTypeEasy OtherTypeT>
auto operator | (ContainerT&& X, const OtherTypeT& Y) {
    
    if constexpr(std::is_same_v<OtherTypeT, RangeDrop>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        while (iter < Y.quantity && T._begin != X.end()) {
            iter++;
            ++T._begin;
        }
        return T;
    } else if constexpr(std::is_same_v<OtherTypeT, RangeTake>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        T._end = X.begin();
        while (iter < Y.quantity && T._end != X.end()) {
            
            iter++;
            T._end++;
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
    }
    else if constexpr (std::is_same_v<OtherTypeT, RangeTransform<typename OtherTypeT::function>>) {
        IteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T (X.begin(), Y.foo);
        IteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T1 (X.end(), Y.foo);

        Range R(T, T1);
        return R;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeFilter<typename OtherTypeT::function>>) {
        FilterIteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T (X.begin(), Y.foo, X.end());
        FilterIteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T1 (X.end(), Y.foo, X.end());

        Range R(T, T1);
        return R;
    }
}

template <class ContainerT, AcceptableTypeEasy OtherTypeT>
auto operator | (ContainerT& X, const OtherTypeT& Y) {
    
    if constexpr(std::is_same_v<OtherTypeT, RangeDrop>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        while (iter < Y.quantity && T._begin != X.end()) {
            iter++;
            ++T._begin;
        }
        return T;
    } else if constexpr(std::is_same_v<OtherTypeT, RangeTake>) {
        Range T (X.begin(), X.end());
        int iter = 0;
        
        T._end = X.begin();
        while (iter < Y.quantity && T._end != X.end()) {
            
            iter++;
            T._end++;
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
    }
    else if constexpr (std::is_same_v<OtherTypeT, RangeTransform<typename OtherTypeT::function>>) {
        IteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T (X.begin(), Y.foo);
        IteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T1 (X.end(), Y.foo);

        Range R(T, T1);
        return R;
    } else if constexpr (std::is_same_v<OtherTypeT, RangeFilter<typename OtherTypeT::function>>) {
        FilterIteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T (X.begin(), Y.foo, X.end());
        FilterIteratorAdaptor<typename ContainerT::iterator, typename OtherTypeT::function> T1 (X.end(), Y.foo, X.end());

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