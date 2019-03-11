#ifndef APPLIED_EXAMPLE_H
#define APPLIED_EXAMPLE_H
#include <functional>
#include <string>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "type_value_test.h"
#include "things_to_test.h"

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

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
struct FakeSort: public SortingAlgorithm<ITERATOR, COMPARATOR>{
    virtual void sort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()) override{
    }
    virtual ~FakeSort(){}
};

/// We will be using indicies from TypeParam::valuesId in tests
/// to access data from below sizes array and getSortingObject()
constexpr std::array<int,4> sizes {0,1,2,10};

template<typename T, typename COMPARATOR = std::less<T>>
static SortingAlgorithm<typename std::vector<T>::iterator, COMPARATOR>* getSortingObject(int id){
    if(id == 0){
        return new BubbleSort<typename std::vector<T>::iterator, COMPARATOR>();
    }else if(id == 1){
        return new InsertionSort<typename std::vector<T>::iterator, COMPARATOR>();
    }else if(id == 2){
        return new SelectionSort<typename std::vector<T>::iterator, COMPARATOR>();
    }else if(id == 3){
        return new FakeSort<typename std::vector<T>::iterator, COMPARATOR>();
    }
}

using TypesWithLessOperatorTuples = std::tuple<std::tuple<int,unsigned,double,ElementWithLessOperator>>;
using TypesWithComparatorTuples = std::tuple<std::tuple<ElementWithComparator>>;
using ValuesIdTuple = std::tuple<TT::NUM<4>,TT::NUM<sizes.size()>>;
using LessOperatorTypesPermutations = TT::getPermutations<TypesWithLessOperatorTuples,ValuesIdTuple>::tuple;
using ComparatorTypesPermutations = TT::getPermutations<TypesWithComparatorTuples,ValuesIdTuple>::tuple;

template <typename T>
class SortingViaLessOperatorTest : public ::testing::Test {};

/// We using TYPED_TEST_SUITE_MODED because it allows us to have much more
/// than 50 types allowed by standart TYPED_TEST_SUITE
TYPED_TEST_SUITE_MODED(SortingViaLessOperatorTest, LessOperatorTypesPermutations);

TYPED_TEST(SortingViaLessOperatorTest, variableTypeAndSizeSort)
{
    using TYPE0 = GET_TYPE(0);
    const auto value_id_0 = GET_VALUE_ID(0);
    const auto value_id_1 = GET_VALUE_ID(1);
    auto sortObject = getSortingObject<TYPE0>(value_id_0);
    auto vec = makeRandomVector<TYPE0>(sizes.at(value_id_0));
    sortObject->sort(vec.begin(),vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(),vec.end()));
    delete sortObject;

}

template <typename T>
class SortingViaComparatorTest : public ::testing::Test {};

TYPED_TEST_SUITE_MODED(SortingViaComparatorTest, ComparatorTypesPermutations);

TYPED_TEST(SortingViaComparatorTest, variableTypeAndSizeSort)
{
    using TYPE0 = GET_TYPE(0);
    const auto value_id_0 = GET_VALUE_ID(0);
    const auto value_id_1 = GET_VALUE_ID(1);
    auto sortObject = getSortingObject<TYPE0, decltype(TYPE0::getComparator())>(value_id_0);
    auto vec = makeRandomVector<TYPE0>(sizes.at(value_id_0));
    sortObject->sort(vec.begin(),vec.end(),TYPE0::getComparator());
    ASSERT_TRUE(std::is_sorted(vec.begin(),vec.end(),TYPE0::getComparator()));
    std::vector<int> vecInt;
    for(const auto &element: vec){
        vecInt.push_back(element.value);
    }
    ASSERT_TRUE(std::is_sorted(vecInt.begin(),vecInt.end()));
    delete sortObject;

}


#endif // APPLIED_EXAMPLE_H
