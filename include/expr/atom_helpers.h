#pragma once
#include "expr.h"

#define boolean(x) Bool<x>

#define num(x) Int<x>

// 这里使用了一种用宏把字符串展开为字符列表的技巧，详见：
// https://stackoverflow.com/questions/18031818/trying-to-pass-string-literals-as-template-arguments/36273815#36273815

#define STRING_LITERAL_20(str) ((TERMINATED_19(str))?(str[19]):('\0')), STRING_LITERAL_19(str)
#define STRING_LITERAL_19(str) ((TERMINATED_18(str))?(str[18]):('\0')), STRING_LITERAL_18(str)
#define STRING_LITERAL_18(str) ((TERMINATED_17(str))?(str[17]):('\0')), STRING_LITERAL_17(str)
#define STRING_LITERAL_17(str) ((TERMINATED_16(str))?(str[16]):('\0')), STRING_LITERAL_16(str)
#define STRING_LITERAL_16(str) ((TERMINATED_15(str))?(str[15]):('\0')), STRING_LITERAL_15(str)
#define STRING_LITERAL_15(str) ((TERMINATED_14(str))?(str[14]):('\0')), STRING_LITERAL_14(str)
#define STRING_LITERAL_14(str) ((TERMINATED_13(str))?(str[13]):('\0')), STRING_LITERAL_13(str)
#define STRING_LITERAL_13(str) ((TERMINATED_12(str))?(str[12]):('\0')), STRING_LITERAL_12(str)
#define STRING_LITERAL_12(str) ((TERMINATED_11(str))?(str[11]):('\0')), STRING_LITERAL_11(str)
#define STRING_LITERAL_11(str) ((TERMINATED_10(str))?(str[10]):('\0')), STRING_LITERAL_10(str)
#define STRING_LITERAL_10(str) ((TERMINATED_9(str))?(str[9]):('\0')), STRING_LITERAL_9(str)
#define STRING_LITERAL_9(str)  ((TERMINATED_8(str))?(str[8]):('\0')), STRING_LITERAL_8(str)
#define STRING_LITERAL_8(str)  ((TERMINATED_7(str))?(str[7]):('\0')), STRING_LITERAL_7(str)
#define STRING_LITERAL_7(str)  ((TERMINATED_6(str))?(str[6]):('\0')), STRING_LITERAL_6(str)
#define STRING_LITERAL_6(str)  ((TERMINATED_5(str))?(str[5]):('\0')), STRING_LITERAL_5(str)
#define STRING_LITERAL_5(str)  ((TERMINATED_4(str))?(str[4]):('\0')), STRING_LITERAL_4(str)
#define STRING_LITERAL_4(str)  ((TERMINATED_3(str))?(str[3]):('\0')), STRING_LITERAL_3(str)
#define STRING_LITERAL_3(str)  ((TERMINATED_2(str))?(str[2]):('\0')), STRING_LITERAL_2(str)
#define STRING_LITERAL_2(str)  ((TERMINATED_1(str))?(str[1]):('\0')), STRING_LITERAL_1(str)
#define STRING_LITERAL_1(str)  str[0]

#define TERMINATED_19(str) TERMINATED_18(str) && str[18]
#define TERMINATED_18(str) TERMINATED_17(str) && str[17]
#define TERMINATED_17(str) TERMINATED_16(str) && str[16]
#define TERMINATED_16(str) TERMINATED_15(str) && str[15]
#define TERMINATED_15(str) TERMINATED_14(str) && str[14]
#define TERMINATED_14(str) TERMINATED_13(str) && str[13]
#define TERMINATED_13(str) TERMINATED_12(str) && str[12]
#define TERMINATED_12(str) TERMINATED_11(str) && str[11]
#define TERMINATED_11(str) TERMINATED_10(str) && str[10]
#define TERMINATED_10(str) TERMINATED_9(str) && str[9]
#define TERMINATED_9(str) TERMINATED_8(str) && str[8]
#define TERMINATED_8(str) TERMINATED_7(str) && str[7]
#define TERMINATED_7(str) TERMINATED_6(str) && str[6]
#define TERMINATED_6(str) TERMINATED_5(str) && str[5]
#define TERMINATED_5(str) TERMINATED_4(str) && str[4]
#define TERMINATED_4(str) TERMINATED_3(str) && str[3]
#define TERMINATED_3(str) TERMINATED_2(str) && str[2]
#define TERMINATED_2(str) TERMINATED_1(str) && str[1]
#define TERMINATED_1(str) str[0]

#define fullchars(str) STRING_LITERAL_20(str)

namespace atom_helpers {

    template<char, typename> struct StringCons;
    template<char c, char... s> struct StringCons<c, String<s...>> {
        using Type = String<s..., c>;
    };
    template<char... str> struct IntoString;
    template<> struct IntoString<> {
        using Type = String<>;
    };
    template<char c, char... str> struct IntoString<c, str...> {
        static_assert(c != '\0');
        using Type = typename StringCons<c, typename IntoString<str...>::Type>::Type;
    };
    template<char... str> struct IntoString<'\0', str...> {
        using Type = typename IntoString<str...>::Type;
    };
    
    template<char, typename> struct SymbolCons;
    template<char c, char... s> struct SymbolCons<c, Symbol<s...>> {
    using Type = Symbol<s..., c>;
    };
    template<char... str> struct IntoSymbol;
    template<char c> struct IntoSymbol<c> {
        static_assert(c != '\0');
        using Type = Symbol<c>;
    };
    template<char c, char... str> struct IntoSymbol<c, str...> {
        static_assert(c != '\0');
        using Type = typename SymbolCons<c, typename IntoSymbol<str...>::Type>::Type;
    };
    template<char... str> struct IntoSymbol<'\0', str...> {
        using Type = typename IntoSymbol<str...>::Type;
    };
    
}

#define str(str) typename atom_helpers::IntoString<fullchars(str)>::Type
#define sym(str) typename atom_helpers::IntoSymbol<fullchars(str)>::Type