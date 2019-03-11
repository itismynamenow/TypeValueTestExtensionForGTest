#ifndef THINGS_TO_TEST_H
#define THINGS_TO_TEST_H
#include <functional>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>     /* srand, rand */

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
void selectionSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
    if(first == last || std::next(first) == last) return;
    for(auto iterator = first;iterator!=last;++iterator){
        const auto minValueIterator = std::min_element(iterator,last,comparator);
        std::swap(*iterator,*minValueIterator);
    }
};

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
void insertionSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
    if(first == last || std::next(first) == last) return;
    for(auto iterator = std::next(first);iterator!=last;++iterator){
        const auto insertionIterator = std::upper_bound(first,iterator,*iterator,comparator);
        std::rotate(insertionIterator,iterator,std::next(iterator));
    }
};

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
void bubbleSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
    if(first == last || std::next(first) == last) return;
    auto end = std::prev(last);
    bool isSorted = true;
    do{
        isSorted = true;
        for(auto iterator = first;iterator!=end;++iterator){
            if(!comparator(*iterator,*std::next(iterator))){
                std::swap(*iterator,*std::next(iterator));
                isSorted = false;
            }
        }
    }while(--end,!isSorted);
};

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
void mergeSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
    if(first == last || std::next(first) == last) return;
    const auto length = std::distance(first,last);
    const auto middle = std::next(first,length/2);
    mergeSort(first,middle,comparator);
    mergeSort(middle,last,comparator);
    std::inplace_merge(first, middle, last,comparator);
};

/// Below are few custom types that we will use for sorting
/// One of them contains less operator that will be used for sorting
/// Another contains custom comparator that we will pass as argument
struct ElementWithComparator{
    int value;
    static auto getComparator(){
        return [](const ElementWithComparator &a, const ElementWithComparator &b ) { return a.value < b.value; };
    }
};

struct ElementWithLessOperator{
    int value;
    bool operator < ( const ElementWithLessOperator &another ) const{
        return ( value < another.value );
    }
};

/// Below function generates vector with random values of given size
/// The function takes arithmetic types and types declared above
template<class T, typename std::enable_if<std::is_arithmetic<T>::value, T>::type* = nullptr>
std::vector<T>makeRandomVector(int size){
    std::vector<T> vec(size);
    for(auto &element: vec){
        element = rand() % 1000;
    }
    return vec;
}

template<class T, typename std::enable_if<std::is_same<T,ElementWithComparator>::value || std::is_same<T,ElementWithLessOperator>::value, T>::type* = nullptr>
std::vector<T>makeRandomVector(int size){
    std::vector<T> vec(size);
    for(auto &element: vec){
        element.value = rand() % 1000;
    }
    return vec;
}

#endif // THINGS_TO_TEST_H
