#ifndef APPLIED_EXAMPLE_H
#define APPLIED_EXAMPLE_H
#include <functional>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "type_value_test.h"

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
struct SortingAlgorithm{
    virtual void sort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ())=0;
    virtual ~SortingAlgorithm(){}
};

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
struct InsertionSort: public SortingAlgorithm<ITERATOR, COMPARATOR>{
    virtual void sort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()) override{
        if(first == last || std::next(first) == last) return;
        for(auto iterator = std::next(first);iterator!=last;++iterator){
            const auto insertionIterator = std::upper_bound(first,iterator,*iterator,comparator);
            std::rotate(insertionIterator,iterator,std::next(iterator));
        }
    }
    virtual ~InsertionSort(){}
};

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
struct SelectionSort: public SortingAlgorithm<ITERATOR, COMPARATOR>{
    virtual void sort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()) override{
        if(first == last || std::next(first) == last) return;
        for(auto iterator = first;iterator!=last;++iterator){
            const auto minValueIterator = std::min_element(iterator,last,comparator);
            std::swap(*iterator,*minValueIterator);
        }
    }
    virtual ~SelectionSort(){}
};

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
struct BubbleSort: public SortingAlgorithm<ITERATOR, COMPARATOR>{
    virtual void sort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()) override{
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
    }
    virtual ~BubbleSort(){}
};

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
struct MergeSort: public SortingAlgorithm<ITERATOR, COMPARATOR>{
    virtual void sort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()) override{
        if(first == last || std::next(first) == last) return;
        const auto length = std::distance(first,last);
        const auto middle = std::next(first,length/2);
        mergeSort(first,middle,comparator);
        mergeSort(middle,last,comparator);
        std::inplace_merge(first, middle, last,comparator);
    }
    virtual ~MergeSort(){}
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

template <typename T>
class TypedTest : public ::testing::Test {};

using typesTuples = std::tuple<std::tuple<int,unsigned,double,ElementWithComparator>>;
using valueTuples = std::tuple<TT::NUM<4>,TT::NUM<7>>;

//using TestTypes = Test<TVT::getPermutations<typesTuples,valueTuples>::tuple>::Types;


//using myTypes = typename std::tuple<int,long,float,double>;
using myTypes = TT::getPermutations<typesTuples,valueTuples>::tuple;

TYPED_TEST_SUITE_MODED(TypedTest, myTypes );

TYPED_TEST(TypedTest, printTypes)
{
//    using TYPE0 = typename std::tuple_element<0, typename TypeParam::types>;
//    using TYPE1 = typename std::tuple_element<1, typename TypeParam::types>;
    ::testing::Types<int> typeInt;
    int a = 0;
//    const std::size_t value_id_0 = std::tuple_element<0, typename TypeParam::valuesId>::type::value;
//    const std::size_t value_id_1 = std::tuple_element<1, typename TypeParam::valuesId>::type::value;

}

#endif // APPLIED_EXAMPLE_H