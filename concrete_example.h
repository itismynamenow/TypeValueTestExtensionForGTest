//#ifndef CONCRETE_EXAMPLE_H
//#define CONCRETE_EXAMPLE_H
//#include <functional>
//#include <algorithm>
//#include <vector>
//#include <stdlib.h>     /* srand, rand */

//#include <gtest/gtest.h>
//#include <gmock/gmock-matchers.h>

//#include "type_value_test.h"

///// In this example we will test template sort function
///// To test it we will run all of them on
///// vectors of different types and sizes
/////
/////
///// Below are several templates for sorting function
///// All functions have same outputs, inputs and template args

//template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
//void selectionSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
//    if(first == last || std::next(first) == last) return;
//    for(auto iterator = first;iterator!=last;++iterator){
//        const auto minValueIterator = std::min_element(iterator,last,comparator);
//        std::swap(*iterator,*minValueIterator);
//    }
//};

//template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
//void insertionSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
//    if(first == last || std::next(first) == last) return;
//    for(auto iterator = std::next(first);iterator!=last;++iterator){
//        const auto insertionIterator = std::upper_bound(first,iterator,*iterator,comparator);
//        std::rotate(insertionIterator,iterator,std::next(iterator));
//    }
//};

//template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
//void bubbleSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
//    if(first == last || std::next(first) == last) return;
//    auto end = std::prev(last);
//    bool isSorted = true;
//    do{
//        isSorted = true;
//        for(auto iterator = first;iterator!=end;++iterator){
//            if(!comparator(*iterator,*std::next(iterator))){
//                std::swap(*iterator,*std::next(iterator));
//                isSorted = false;
//            }
//        }
//    }while(--end,!isSorted);
//};

//template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
//void mergeSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
//    if(first == last || std::next(first) == last) return;
//    const auto length = std::distance(first,last);
//    const auto middle = std::next(first,length/2);
//    mergeSort(first,middle,comparator);
//    mergeSort(middle,last,comparator);
//    std::inplace_merge(first, middle, last,comparator);
//};


///// Below are few custom types that we will use for sorting
///// One of them contains less operator that will be used for sorting
///// Another contains custom comparator that we will pass as argument
//struct ElementWithComparator{
//    int value;
//    static auto getComparator(){
//        return [](const ElementWithComparator &a, const ElementWithComparator &b ) { return a.value < b.value; };
//    }
//};

//struct ElementWithLessOperator{
//    int value;
//    bool operator < ( const ElementWithLessOperator &another ) const{
//        return ( value < another.value );
//    }
//};

///// Below function generates vector with random values of given size
///// The function takes arithmetic types and types declared above
//template<class T, typename std::enable_if<std::is_arithmetic<T>::value, T>::type* = nullptr>
//std::vector<T>makeRandomVector(int size){
//    std::vector<T> vec(size);
//    for(auto &element: vec){
//        element = rand() % 1000;
//    }
//    return vec;
//}

//template<class T, typename std::enable_if<std::is_same<T,ElementWithComparator>::value || std::is_same<T,ElementWithLessOperator>::value, T>::type* = nullptr>
//std::vector<T>makeRandomVector(int size){
//    std::vector<T> vec(size);
//    for(auto &element: vec){
//        element.value = rand() % 1000;
//    }
//    return vec;
//}

//template<typename T>
//struct SortTest;
//template<typename ...T>
//struct SortTest<std::tuple<T...>>
//{
//    using Types = ::testing::Types<T...>;
//};

///// Global array below holds values that we will use in tests
///// GET_VALUE_ID(0) macro will be used in test case to get index
///// from 0 to 2 that will be used to obtain value from this array
//constexpr std::array<std::size_t,3> vector_sizes {0,1,10};

//using lessOperatorSortingTypesTuples = std::tuple<std::tuple<int,unsigned,double,ElementWithLessOperator>>;
//using comparatorSortingTypesTuples = std::tuple<std::tuple<ElementWithComparator>>;
//using valueTuplesSorting = std::tuple<TVT::NUM<vector_sizes.size()>>;

//using LessOperatorSortingTypes = SortTest<TVT::getPermutations<lessOperatorSortingTypesTuples,valueTuplesSorting>::tuple>::Types;
//using ComparatorSortingTypes = SortTest<TVT::getPermutations<comparatorSortingTypesTuples,valueTuplesSorting>::tuple>::Types;
//#define GET_TYPE(id) typename std::tuple_element<id, typename TypeParam::types>::type
//#define GET_VALUE_ID(id) std::tuple_element<id, typename TypeParam::valuesId>::type::value
//#define TEMPLATED_TEST_SUITE(caseName, types) TYPED_TEST_SUITE(caseName, types);

//#define TEMPLATED_TEST(...) TYPED_TEST(__VA_ARGS__)
//#define PLACEHOLDER(postfix) bubbleSort ## postfix
//#include "concrete_example.h"
//#undef PLACEHOLDER
//#define PLACEHOLDER(postfix) selectionSort ## postfix
//#include "concrete_example.h"
//#undef PLACEHOLDER
//#define PLACEHOLDER(postfix) mergeSort ## postfix
//#include "concrete_example.h"
//#undef PLACEHOLDER
//#define PLACEHOLDER(postfix) insertionSort ## postfix

/////Header guard must be closed here so we can include code below as
/////many times as we need and code below must allow multiple inclusion
//#endif // CONCRETE_EXAMPLE_H

//template <typename T>
//class PLACEHOLDER(Test0) : public ::testing::Test {};

//TEMPLATED_TEST_SUITE(PLACEHOLDER(Test0), LessOperatorSortingTypes)

//TEMPLATED_TEST(PLACEHOLDER(Test0), LessOperatorSorting)
//{
//    using TYPE0 = GET_TYPE(0);
//    const auto valueId0 = GET_VALUE_ID(0);
//    const auto value0 = vector_sizes.at(valueId0);
//    auto vec = makeRandomVector<TYPE0>(value0);
//    PLACEHOLDER()(vec.begin(),vec.end());
//    ASSERT_TRUE(std::is_sorted(vec.begin(),vec.end()));
//}

//template <typename T>
//class PLACEHOLDER(Test1) : public ::testing::Test {};

//TEMPLATED_TEST_SUITE(PLACEHOLDER(Test1), ComparatorSortingTypes)

//TEMPLATED_TEST(PLACEHOLDER(Test1), ComparatorSorting)
//{
//    using TYPE0 = GET_TYPE(0);
//    const auto valueId0 = GET_VALUE_ID(0);
//    const auto value0 = vector_sizes.at(valueId0);
//    auto vec = makeRandomVector<TYPE0>(value0);
//    PLACEHOLDER()(vec.begin(),vec.end(),TYPE0::getComparator());
//    ASSERT_TRUE(std::is_sorted(vec.begin(),vec.end(),TYPE0::getComparator()));
//    std::vector<int> vecInt;
//    for(const auto &element: vec){
//        vecInt.push_back(element.value);
//    }
//    ASSERT_TRUE(std::is_sorted(vecInt.begin(),vecInt.end()));
//}










