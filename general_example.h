//#pragma once

//#include <gtest/gtest.h>
//#include <gmock/gmock-matchers.h>

//#include "type_value_test.h"


////Below is a general illustration of how TVT::getPermutations generates
////all permutations for types and valuesId and how these can be used
////to perform test that need type and value parameters at the same time
//template<typename T>
//struct Test;

//template<typename ...T>
//struct Test<std::tuple<T...>>
//{
//    using Types = ::testing::Types<T...>;
//};

//template <typename T>
//class TypedTest : public ::testing::Test {};

//struct A{};
//struct B{};
//struct C{};

////Declare types combination that will be used in testing
////In below case we will have two types in each test case
////The first types is from set {A,B,C}, the second from set {A,B}
//using typesTuples = std::tuple<std::tuple<A,B,C>,std::tuple<A,B>>;
////Declare number of values that we intend to use during testing
////Later you should access these values using indices that will be generated
////In below case we will have two valuesId in each test case
////The first valueId will have values from 0 to 2, the second from 0 to 1
//using valueTuples = std::tuple<TVT::NUM<3>,TVT::NUM<2>>;

////Generate types with values from A,A,0,0 to C,B,2,1
//using TestTypes = Test<TVT::getPermutations<typesTuples,valueTuples>::tuple>::Types;
///* That's how TVT::getPermutations<typesTuples,valueTuples>::tuple
// * with all 36 permutations will look in this particular case:
// *
// * [std::_Tuple_impl<0,
//    TVT::Case<std::tuple< A, A >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< A, A >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< A, A >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< A, A >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< A, A >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< A, A >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< A, B >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< A, B >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< A, B >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< A, B >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< A, B >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< A, B >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< B, A >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< B, A >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< B, A >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< B, A >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< B, A >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< B, A >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< B, B >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< B, B >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< B, B >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< B, B >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< B, B >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< B, B >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< C, A >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< C, A >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< C, A >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< C, A >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< C, A >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< C, A >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< C, B >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< C, B >,std::tuple<TVT::NUM< 0 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< C, B >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< C, B >,std::tuple<TVT::NUM< 1 >,TVT::NUM< 1 >>>,
//    TVT::Case<std::tuple< C, B >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 0 >>>,
//    TVT::Case<std::tuple< C, B >,std::tuple<TVT::NUM< 2 >,TVT::NUM< 1 >>>>]
// */

//TYPED_TEST_CASE(TypedTest, TestTypes);

//TYPED_TEST(TypedTest, printTypes)
//{
//    using TYPE0 = typename std::tuple_element<0, typename TypeParam::types>;//Will be A,B or C
//    using TYPE1 = typename std::tuple_element<1, typename TypeParam::types>;//Will be A or B
//    const std::size_t value_id_0 = std::tuple_element<0, typename TypeParam::valuesId>::type::value;//Will be 0,1 or 2
//    const std::size_t value_id_1 = std::tuple_element<1, typename TypeParam::valuesId>::type::value;//Will be 0 or 1
//    //Set break point after expression below to see what exactly TestTypes contains
//    //You should see that type of testTypeInstance looks as type in huge comment above
//    typename TVT::getPermutations<typesTuples,valueTuples>::tuple testTypeInstance;

//    std::cout<<" Types: "<<typeid (typename TYPE0::type).name() <<" "<<typeid (typename TYPE1::type).name()<<" valuesId: "<<value_id_0<<" "<<value_id_1<<std::endl;
//    //Do some testing using TYPE0 ,TYPE1... and values from something as MY_GLOBAL_ARRAY0[value_id_0], MY_GLOBAL_ARRAY1[value_id_1]...
//}
