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

template <class ContainerT>
    class RangeDefault {
        public:
            typename ContainerT::const_iterator __begin;
            typename ContainerT::const_iterator __end;
            
            explicit RangeDefault(const ContainerT& X){
                __begin = X.begin();
                __end = X.begin();
            };
            
            friend RangeDefault<ContainerT> take (int n, const ContainerT& X);
            friend RangeDefault<ContainerT> drop (int n, const ContainerT& X);
            
            auto begin() {
                return __begin;
            }
            
            auto end() {
                return __end;
            }
    };

template <class ContainerT>
class Range {
    public:
        typename ContainerT::const_iterator __begin;
        typename ContainerT::const_iterator __end;
        
        explicit Range(const ContainerT& X){
            __begin = X.begin();
            __end = X.begin();
        };
        
        auto begin() {
            return __begin;
        }
        
        auto end() {
            return __end;
        }
        
        
        RangeDefault<ContainerT> take (const size_t& n) {
            RangeDefault<ContainerT> obj(X);
            int iter = 0;
            
            while (iter < n && obj.__end != X.end()) {
                iter++;
                obj.__end++;
            }
            
            return obj;
        }
};

template <class ContainerT, class OtherTypeT>
auto operator | (const ContainerT& X, const OtherTypeT& Y) {
    Range G(X);
    Y.__begin() = G.begin();
    Y.__end() = G.end();
    
    return Y;
}





template <class ContainerT>
RangeDefault<ContainerT> drop (const size_t& n) {
    RangeDefault<ContainerT> obj(X);
    int iter = 0;
    
    while (iter < n && obj.__begin != X.end()) {
        iter++;
        obj.__begin++;
    }
    obj.__end = X.end();
    
    return obj;
}

template <class ContainerT>
class RangeReverse {
    public:
        typename ContainerT::const_reverse_iterator __begin;
        typename ContainerT::const_reverse_iterator __end;
        
        explicit RangeReverse(const ContainerT& X){
            __begin = X.rbegin();
            __end = X.rend();
        };
        
        auto begin() {
            return __begin;
        }
        
        auto end() {
            return __end;
        }
};

template <class ContainerT>
RangeReverse<ContainerT> reverse (const ContainerT& X) {
    RangeReverse<ContainerT> obj(X);
    return obj;
}

template <class ContainerT>
    class RangeKeys {
        public:
            typename ContainerT::const_reverse_iterator __begin;
            typename ContainerT::const_reverse_iterator __end;
            
            explicit RangeKeys(const ContainerT& X){
                __begin = X.rbegin();
                __end = X.rend();
            };
            
            auto begin() {
                return __begin;
            }
            
            auto end() {
                return __end;
            }
    };


#endif //INC_9RANGE_LIB_RANGE_H_
