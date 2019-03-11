# TypeValueTestExtensionForGTest
 
Allows to perform tests that are parameterized by types and values at the same time using Google Test

# Why?
I guess it is easier to explain everything by example. Imagine that you want to test template sorting function. It my look as `sort<T>(It fisrts, It last)`. To test this function it makes sence to sort vectors of different types and size. To my knowleadge popular unit testing frameworks do not allow to parameterize single test with type and value at the same time. Code in this repo provides means to perform such tests.

# How?
To allow tests that are parameterized by types and values following approach is used. "getPermutations" template is used to generate... I better show code...

```cpp
struct A{};
struct B{};
struct C{};

//Declare types combination that will be used in testing
//In below case we will have two types in each test case
//The first types is from set {A,B,C}, the second from set {A,B}
using typesTuples = std::tuple<std::tuple<A,B,C>,std::tuple<A,B>>;
//Declare number of values that we intend to use during testing
//Later you should access these values using indices that will be generated
//In below case we will have two valuesId in each test case
//The first valueId will have values from 0 to 2, the second from 0 to 1
using valueTuples = std::tuple<TT::NUM<3>,TT::NUM<2>>;

//Generate types with values from A,A,0,0 to C,B,2,1
using TestTypes = Test<TT::getPermutations<typesTuples,valueTuples>::tuple>::Types;
/* That's how TT::getPermutations<typesTuples,valueTuples>::tuple
 * with all 36 permutations will look in this particular case:
 *
 * [std::_Tuple_impl<0,
    TT::Case<std::tuple< A, A >,std::tuple<TT::NUM< 0 >,TT::NUM< 0 >>>,
    TT::Case<std::tuple< A, A >,std::tuple<TT::NUM< 0 >,TT::NUM< 1 >>>,
    TT::Case<std::tuple< A, A >,std::tuple<TT::NUM< 1 >,TT::NUM< 0 >>>,
    TT::Case<std::tuple< A, A >,std::tuple<TT::NUM< 1 >,TT::NUM< 1 >>>,
    TT::Case<std::tuple< A, A >,std::tuple<TT::NUM< 2 >,TT::NUM< 0 >>>,
    TT::Case<std::tuple< A, A >,std::tuple<TT::NUM< 2 >,TT::NUM< 1 >>>,
    TT::Case<std::tuple< A, B >,std::tuple<TT::NUM< 0 >,TT::NUM< 0 >>>,
    TT::Case<std::tuple< A, B >,std::tuple<TT::NUM< 0 >,TT::NUM< 1 >>>,
    ...
    TT::Case<std::tuple< C, A >,std::tuple<TT::NUM< 1 >,TT::NUM< 1 >>>,
    TT::Case<std::tuple< C, A >,std::tuple<TT::NUM< 2 >,TT::NUM< 0 >>>,
    TT::Case<std::tuple< C, A >,std::tuple<TT::NUM< 2 >,TT::NUM< 1 >>>,
    TT::Case<std::tuple< C, B >,std::tuple<TT::NUM< 0 >,TT::NUM< 0 >>>,
    TT::Case<std::tuple< C, B >,std::tuple<TT::NUM< 0 >,TT::NUM< 1 >>>,
    TT::Case<std::tuple< C, B >,std::tuple<TT::NUM< 1 >,TT::NUM< 0 >>>,
    TT::Case<std::tuple< C, B >,std::tuple<TT::NUM< 1 >,TT::NUM< 1 >>>,
    TT::Case<std::tuple< C, B >,std::tuple<TT::NUM< 2 >,TT::NUM< 0 >>>,
    TT::Case<std::tuple< C, B >,std::tuple<TT::NUM< 2 >,TT::NUM< 1 >>>>]
 */
```

So as you seen in the example above `TT::getPermutations` generate type/valuesId permutation types.
Then inside test you can access these types and valuesIds as in example below:

```cpp
TYPED_TEST_CASE(TypedTest, TestTypes);

TYPED_TEST(TypedTest, printTypes)
{
    using TYPE0 = typename std::tuple_element<0, typename TypeParam::types>;//Will be A,B or C
    using TYPE1 = typename std::tuple_element<1, typename TypeParam::types>;//Will be A or B
    const std::size_t value_id_0 = std::tuple_element<0, typename TypeParam::valuesId>::type::value;//Will be 0,1 or 2
    const std::size_t value_id_1 = std::tuple_element<1, typename TypeParam::valuesId>::type::value;//Will be 0 or 1
    //Do some testing using TYPE0 ,TYPE1... and values from something as MY_GLOBAL_ARRAY0[value_id_0], MY_GLOBAL_ARRAY1[value_id_1]...
}
```
To get values you need to create some global arrays. That is a bit ugly but alternative code copy/pasting for each size value is way more uglier. 

To get better idea of how this works look at example testing code in this repo.

# What else?
Google test' `TYPED_TEST_SUITE` has a limit on number of types used. It is 50. Therefore `TYPED_TEST_SUITE_MODED` macro was added to remove it. Now max number of types should be at least 1024 according to C++ standart. `TYPED_TEST_SUITE_MODED` accepts `std::tuple` with types (ideally result of `TT::getPermutations`) as second parameter.

The code neeeds C++14 because it uses `std::make_index_sequence` and maybe some functions with auto return type. I feel wit a bit of work all these stuff can be replaced with C++11

Also code containes some usefulnish macros
```cpp
/// Macros for long code responsible for getting type or valueId
/// from TypeParam inside TYPED_TEST
#define GET_TYPE(id) typename std::tuple_element<id, typename TypeParam::types>::type
#define GET_VALUE_ID(id) std::tuple_element<id, typename TypeParam::valuesId>::type::value
```
All useful code is in "type_value_test.h" file, rest are just examples and helpers for examples

# Dependencies

Of course this code depends on Google test and has `#include <gtest/gtest.h>` so make sure you have it. However "type_value_test.h" forward declares all stuff related to gtest and does not need any external dependencies.
