#pragma once

namespace {
    template<typename> struct IsSExpr {
        static constexpr bool value = false;
    };
}



template<bool> struct Bool {};

template<int> struct Int {};

template<char...> struct String {};

template<char...> struct Symbol;
template<char c, char... s> struct Symbol<c, s...> {};

struct Nil {};

template<typename A, typename B> struct Cons {
    static_assert(IsSExpr<A>::value);
    static_assert(IsSExpr<B>::value);
};

template<typename, typename, typename> struct Closure {};



namespace {
    template<bool x> struct IsSExpr<Bool<x>> {
        static constexpr bool value = true;
    };
    
    template<int x> struct IsSExpr<Int<x>> {
        static constexpr bool value = true;
    };

    template<char... s> struct IsSExpr<String<s...>> {
        static constexpr bool value = true;
    };

    template<char... s> struct IsSExpr<Symbol<s...>> {
        static constexpr bool value = true;
    };

    template<> struct IsSExpr<Nil> {
        static constexpr bool value = true;
    };

    template<typename A, typename B> struct IsSExpr<Cons<A, B>> {
        static constexpr bool value = IsSExpr<A>::value && IsSExpr<B>::value;
    };
    
    template<typename A> struct IsSExpr<Builtin<A>> {
        static constexpr bool value = true;
    };
    
    template<typename Args, typename Expr, typename Env> struct IsSExpr<Closure<Args, Expr, Env>> {
        static constexpr bool value = true;
    };
}

template<typename T> constexpr bool is_sexpr() {return IsSExpr<T>::value;}