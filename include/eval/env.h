#pragma once
#include "expr/expr.h"

namespace {

    template<typename, typename> struct Binding;
    template<char... s, typename T> struct Binding<Symbol<s...>, T> {
        static_assert(is_sexpr<T>());
        using var = Symbol<s...>;
        using value = T;
    };

    template<typename...> struct Env;
    template<> struct Env<> {};
    template<typename Var, typename Value, typename... Others> struct Env<Binding<Var, Value>, Others...> {};
    
}

// 空环境
using empty_env = Env<>;



namespace {
    
    template<typename, typename> struct FindEnv;
    
    template<typename Var, typename Value, typename... Others>
    struct FindEnv<Var, Env<Binding<Var, Value>, Others...>> {
        using result = Value;
    };
    
    template<typename Var, typename AnotherVar, typename AnotherValue, typename... Others>
    struct FindEnv<Var, Env<Binding<AnotherVar, AnotherValue>, Others...>> {
        using result = typename FindEnv<Var, Env<Others...>>::result;
    };
    
}

// 在环境中查找变量的值
template<typename Var, typename Env> using find_env = typename FindEnv<Var, Env>::result;



namespace {
    
    template<typename, typename, typename> struct AddEnv;
    
    template<typename Var, typename Value, typename... Others>
    struct AddEnv<Var, Value, Env<Others...>> {
        using result = Env<Binding<Var, Value>, Others...>;
    };
    
}

// 向环境中添加变量
template<typename Var, typename Value, typename Env> using add_env = typename AddEnv<Var, Value, Env>::result;



namespace {
    
    template<typename, typename, typename> struct SetEnv;

    template<typename Var, typename Value, typename OldValue, typename... Others>
    struct SetEnv<Var, Value, Env<Binding<Var, OldValue>, Others...>> {
        using result = Env<Binding<Var, Value>, Others...>;
    };

    template<typename Var, typename Value, typename AnotherVar, typename AnotherValue, typename... Others>
    struct SetEnv<Var, Value, Env<Binding<AnotherVar, AnotherValue>, Others...>> {
        using result = Env<Binding<AnotherVar, AnotherValue>, typename SetEnv<Var, Value, Env<Others...>>::result>;
    };
    
}

// 修改环境中的变量
template<typename Var, typename Value, typename Env> using set_env = typename SetEnv<Var, Value, Env>::result;