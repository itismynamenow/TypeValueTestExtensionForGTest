#ifndef TYPE_VALUE_TEST_H
#define TYPE_VALUE_TEST_H
#include <tuple>
#include <utility>

namespace testing{
    namespace internal{
        struct Types0;
        template <typename T>
        std::string GetTypeName();
    }
}

namespace TT {
    template<typename T, typename V>
    struct Case
    {
        using types = T;
        using valuesId = V;
    };

    template<std::size_t I>
    struct NUM{
        static constexpr std::size_t value = I;
    };

    namespace {
        template<typename T, typename... Args>
        struct getTypeTupleCombinationsImpl{
          static constexpr std::size_t value = std::tuple_size<T>::value * getTypeTupleCombinationsImpl<Args...>::value;
        };

        template<typename T>
        struct getTypeTupleCombinationsImpl<T>{
          static constexpr std::size_t value = std::tuple_size<T>::value;
        };

        template<typename T, typename... Args>
        struct getProductImpl{
          static constexpr std::size_t value = T::value * getProductImpl<Args...>::value;
        };

        template<typename T>
        struct getProductImpl<T>{
          static constexpr std::size_t value = T::value;
        };

        template<typename... Ts>
        struct getTypeTupleCombinations;

        template<typename... Ts>
        struct getTypeTupleCombinations<std::tuple<Ts...>>{
            static constexpr std::size_t value = getTypeTupleCombinationsImpl<Ts...>::value;
        };

        template<typename... Ts>
        struct getProduct;

        template<typename... Ts>
        struct getProduct<std::tuple<Ts...>>{
            static constexpr std::size_t value = getProductImpl<Ts...>::value;
        };

        template<typename TypesTuples, typename TypesFrequencies, typename I, std::size_t J>
        struct getTypeFromTuple{
            using current_type_tuple = typename std::tuple_element<J, TypesTuples>::type;
            static constexpr std::size_t current_type_tuple_size = std::tuple_size<current_type_tuple>::value;
            static constexpr std::size_t current_frequency = std::tuple_element<J,TypesFrequencies>::type::value;            

            static_assert(current_frequency != 0, "current_frequency == 0");
            static_assert(current_type_tuple_size != 0, "current_type_tuple_size == 0");

            static constexpr std::size_t ratio = current_frequency/current_type_tuple_size;
            static constexpr std::size_t current_type_id = (I::value / ((ratio == 0)?1:ratio)) % current_type_tuple_size;
            using type = typename std::tuple_element<current_type_id, current_type_tuple>::type;
        };

        template<typename T1, typename T2, typename T3,typename T4>
        struct makeTypeCombinationTupleImpl;

        template<typename TypesTuples, typename TypesFrequencies,  typename I, std::size_t... Is>
        struct makeTypeCombinationTupleImpl<TypesTuples, TypesFrequencies, I, std::index_sequence<Is...>>{
            using tuples = std::tuple<typename getTypeFromTuple<TypesTuples, TypesFrequencies, I, Is>::type...>;
        };

        template<typename TypesTuples, typename TypesFrequencies, typename I>
        struct makeTypeCombinationTuple{
            static constexpr std::size_t type_count = std::tuple_size<TypesTuples>::value;
            using tuple = typename makeTypeCombinationTupleImpl<
                                TypesTuples,
                                TypesFrequencies,
                                I,
                                std::make_index_sequence<type_count>>::tuples;
        };

        template<typename ValuesIdTuple, typename ValuesIdFrequencies, typename I, std::size_t J>
        struct getValuesIdFromTuple{
            static constexpr std::size_t current_frequency = std::tuple_element<J,ValuesIdFrequencies>::type::value;
            static constexpr std::size_t current_value_id = std::tuple_element<J, ValuesIdTuple>::type::value;

            static_assert(current_frequency != 0, "current_frequency == 0");
            static_assert(current_value_id != 0, "current_frequency == 0");

            static constexpr std::size_t ratio = current_frequency / current_value_id;
            static constexpr std::size_t current_value = (I::value / ((ratio == 0)?1:ratio)) % current_value_id;
            using type = NUM<current_value>;
        };

        template<typename T1, typename T2, typename T3, typename T4>
        struct makeValueIdCombinationTupleImpl;

        template<typename ValuesIdTuple, typename ValuesIdFrequencies,  typename I, std::size_t... Is>
        struct makeValueIdCombinationTupleImpl<ValuesIdTuple, ValuesIdFrequencies, I, std::index_sequence<Is...>>{
            using tuples = std::tuple<typename getValuesIdFromTuple<ValuesIdTuple, ValuesIdFrequencies, I, Is>::type...>;
        };

        template<typename ValuesIdTuple, typename ValuesIdFrequencies, typename I>
        struct makeValueIdCombinationTuple{
            static constexpr std::size_t tuple_size = std::tuple_size<ValuesIdTuple>::value;
            using tuple = typename makeValueIdCombinationTupleImpl<
                                ValuesIdTuple,
                                ValuesIdFrequencies,
                                I,
                                std::make_index_sequence<tuple_size>>::tuples;
        };

        template<typename Tuple, std::size_t I>
        struct getTupleNthElement{
            using value = typename std::tuple_element<I,Tuple>::type;
        };

        template<typename Tuple, typename Is>
        struct makeSubtupleImpl;

        template<typename Tuple, std::size_t... Is>
        struct makeSubtupleImpl<Tuple, std::index_sequence<Is...>>{
            using tuple = std::tuple<typename getTupleNthElement<Tuple,Is>::value...>;
        };

        template<typename Tuple, std::size_t I>
        struct makeSubtuple{
            static constexpr std::size_t tuple_size = std::tuple_size<Tuple>::value;
            using tuple = typename makeSubtupleImpl<Tuple,std::make_index_sequence<tuple_size-I>>::tuple;
        };

        template<typename ValuesIdTuple, std::size_t I>
        struct makeValueIdFrequencyTupleImplBody{
            using tuple = typename makeSubtuple<ValuesIdTuple, I>::tuple;
            using value = NUM<getProduct<tuple>::value>;
        };

        template<typename ValuesIdTuple,typename Is>
        struct makeValueIdFrequencyTupleImpl;

        template<typename ValuesIdTuple,std::size_t... Is>
        struct makeValueIdFrequencyTupleImpl<ValuesIdTuple, std::index_sequence<Is...>>{
            using tuple = std::tuple< typename makeValueIdFrequencyTupleImplBody<ValuesIdTuple, Is>::value...>;
        };

        template<typename ValuesIdTuple>
        struct makeValueIdFrequencyTuple{
            static constexpr std::size_t tuple_size = std::tuple_size<ValuesIdTuple>::value;
            using tuple = typename makeValueIdFrequencyTupleImpl<ValuesIdTuple,std::make_index_sequence<tuple_size>>::tuple;
        };

        template<typename Tuple, std::size_t I>
        struct invertTupleImplBody{
            static constexpr std::size_t tuple_size = std::tuple_size<Tuple>::value;
            using value = typename std::tuple_element<tuple_size - I - 1,Tuple>::type;
        };

        template<typename Tuple, typename Is>
        struct invertTupleImpl;

        template< typename Tuple, std::size_t... Is>
        struct invertTupleImpl<Tuple, std::index_sequence<Is...>>{
            using tuple = typename std::tuple<typename invertTupleImplBody<Tuple,Is>::value...>;
        };

        template<typename Tuple>
        struct invertTuple{
            static constexpr std::size_t tuple_size = std::tuple_size<Tuple>::value;
            using tuple = typename invertTupleImpl<Tuple,std::make_index_sequence<tuple_size>>::tuple;
        };

        template<typename TypesTuple, typename ValuesIdProduct, std::size_t I>
        struct makeTypesTupleSizeTupleImplBody{

            static constexpr std::size_t tuple_size = std::tuple_size<TypesTuple>::value;
            static constexpr std::size_t currentTypeSize = std::tuple_size<typename std::tuple_element<I,TypesTuple>::type>::value;
            static constexpr std::size_t product = (I==0) ? currentTypeSize * ValuesIdProduct::value : currentTypeSize ;
            using value = NUM<product>;
        };

        template<typename TypesTuple,typename ValuesIdProduct, typename Is>
        struct makeTypesTupleSizeTupleImpl;

        template<typename TypesTuple, typename ValuesIdProduct, std::size_t... Is>
        struct makeTypesTupleSizeTupleImpl<TypesTuple, ValuesIdProduct,std::index_sequence<Is...>>{
            using tuple = std::tuple< typename makeTypesTupleSizeTupleImplBody<TypesTuple, ValuesIdProduct, Is>::value...>;
        };

        template<typename TypesTuple, typename ValuesIdProduct>
        struct makeTypesTupleSizeTuple{
            static constexpr std::size_t tuple_size = std::tuple_size<TypesTuple>::value;
            using tuple = typename makeTypesTupleSizeTupleImpl<TypesTuple,ValuesIdProduct,std::make_index_sequence<tuple_size>>::tuple;
        };

        template<typename TypesTuple>
        struct makeTypesFrequencyTuple{
            static constexpr std::size_t tuple_size = std::tuple_size<TypesTuple>::value;
            using tuple = typename makeValueIdFrequencyTupleImpl<TypesTuple,std::make_index_sequence<tuple_size>>::tuple;
        };

        template<typename TypesTuples, typename ValuesIdTuple, typename TypesFrequencies, typename ValuesIdFrequencies, std::size_t I>
        struct make_case
        {
            using typeTuple = typename makeTypeCombinationTuple<TypesTuples,TypesFrequencies,NUM<I>>::tuple;
            using valueIdTuple = typename makeValueIdCombinationTuple<ValuesIdTuple,ValuesIdFrequencies,NUM<I>>::tuple;
            using type = Case<typeTuple,valueIdTuple>;
        };

        template <typename T1, typename T2,typename T3, typename T4, typename Is>
        struct make_combinations;

        template <typename TypesTuples, typename ValuesIdTuple, typename TypesFrequencies, typename ValuesIdFrequencies, std::size_t... Is>
        struct make_combinations<TypesTuples, ValuesIdTuple, TypesFrequencies, ValuesIdFrequencies,std::index_sequence<Is...>>
        {
            using tuple = std::tuple<typename make_case<TypesTuples, ValuesIdTuple, TypesFrequencies, ValuesIdFrequencies, Is>::type...>;
        };
    }


    //TypesTuples contains n tuples with actual types
    //ValuesIdTuple contains m numbers
    //Final combination will contain tuple with members
    //that are elements from cartesian product of
    //TypesTuples[0] x TypesTuples[1] x ... x TypesTuples[n] x
    //ValuesIdTuple[0] x ValuesIdTuple[1] x ... x ValuesIdTuple[m]
    template <typename TypesTuples, typename ValuesIdTuple>
    struct getPermutations{
        static constexpr std::size_t combination_count = getTypeTupleCombinations<TypesTuples>::value * getProduct<ValuesIdTuple>::value;
        static constexpr std::size_t valuesId_product = getProduct<ValuesIdTuple>::value;

        using ValuesIdFrequencies = typename makeValueIdFrequencyTuple<ValuesIdTuple>::tuple;

        using InvertedTypesTuples = typename invertTuple<TypesTuples>::tuple;
        using TypesTupleSizeTuple = typename makeTypesTupleSizeTuple<InvertedTypesTuples,NUM<valuesId_product>>::tuple;
        using TypesFrequencies = typename makeTypesFrequencyTuple<TypesTupleSizeTuple>::tuple;

        using tuple = typename make_combinations
                               <TypesTuples,
                                ValuesIdTuple,
                                TypesFrequencies,
                                ValuesIdFrequencies,
                                std::make_index_sequence<combination_count>>
                             ::tuple;
    };

    template <typename T1, typename ...T>
    struct Type;

    template <typename T1>
    struct Type<T1>{
        typedef T1 Head;
        //Must be ::testing::internal::Types0 other won't work
        typedef ::testing::internal::Types0 Tail;
    };

    template <typename T1, typename ...T>
    struct Type {
        typedef T1 Head;
        typedef Type<T...> Tail;
    };

    template <typename ...Ts>
    struct Types{
        typedef Type<Ts...> type;
    };

    /// My replacer for default TypeList
    /// this implementation supports much more
    /// than 50 template parameters
    template <typename ...Ts>
    struct TypeList;

    template <typename ...Ts>
    struct TypeList<std::tuple<Ts...>>{
      typedef typename Types<Ts...>::type type;
    };

    /// custom name generator that generates much shorter names than default one
    struct NameGenerator {
      template <typename T>
      static std::string GetName(int i) {
        auto typesString = ::testing::internal::GetTypeName<typename T::types>();
        typesString = typesString.substr(std::string("std::tuple").size());
        auto valuesIdString = ::testing::internal::GetTypeName<typename T::valuesId>();
        valuesIdString = valuesIdString.substr(std::string("std::tuple").size());
        std::size_t index;
        while(index = valuesIdString.find("TT::NUM<"), index !=  std::string::npos){
            valuesIdString.erase(index,std::string("TT::NUM<").size());
        }
        while(index = valuesIdString.find(">"), index !=  std::string::npos){
            valuesIdString.erase(index,std::string(">").size());
        }
        while(index = valuesIdString.find("ull"), index !=  std::string::npos){
            valuesIdString.erase(index,std::string("ull").size());
        }
        valuesIdString += ">";
        return typesString + " " + valuesIdString;
      }
    };
}



/**
 *  Original macro TYPED_TEST_SUITE_MODED relies on
 *  ::testing::internal::TypeList that can only accept up to
 *  50 template parameters when C++ standart allows at least
 *  1024 template parameters. So this macro adresses this issue
 *  utilizing c++11 parameter pack that allows much bigger
 *  number of templates arguments.
 *
 * @param Types: std::tuple with types
 */
#define TYPED_TEST_SUITE_MODED(CaseName, Types, ...)                           \
  typedef TT::TypeList< Types >::type GTEST_TYPE_PARAMS_( \
      CaseName);                                                         \
  typedef ::testing::internal::NameGeneratorSelector<__VA_ARGS__>::type  \
      GTEST_NAME_GENERATOR_(CaseName)

/// Macros for long code responsible for getting type or valueId
/// from TypeParam inside TYPED_TEST
#define GET_TYPE(id) typename std::tuple_element<id, typename TypeParam::types>::type
#define GET_VALUE_ID(id) std::tuple_element<id, typename TypeParam::valuesId>::type::value


#endif // TYPE_VALUE_TEST_H
