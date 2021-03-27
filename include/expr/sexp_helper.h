#pragma once
#include "expr.h"

namespace sexp_helper {

    template<typename...> struct SExpBuilder;
    template<> struct SExpBuilder<> {
        using Type = Nil;
    };
    template<typename A, typename... B> struct SExpBuilder<A, B...> {
        using Type = Cons<A, typename SExpBuilder<B...>::Type>;
    };

}

#define S(args...) typename sexp_helper::SExpBuilder<args>::Type