#pragma once

template<typename Func, typename Args, typename Env>
struct Apply<Builtin<Func>, Args, Env> {
    using result = typename Func::apply<Args, Env>;
};

namespace {
    template<typename ListParam, typename ListArg, typename Env>
    struct ArgsEnv {
        using env = add_env<ListParam, ListArg, Env>;
    };
    
    template<typename Env> struct ArgsEnv<Nil, Nil, Env> {
        using env = Env;
    };
    template<typename FirstParam, typename OtherParms, typename FirstArg, typename OtherArgs, typename Env>
    struct ArgsEnv<Cons<FirstParam, OtherParms>, Cons<FirstArg, OtherArgs>, Env> {
        using env = typename ArgsEnv<OtherParms, OtherArgs, add_env<FirstParam, FirstArg, Env>>::env;
    };
}

template<typename Params, typename Expr, typename ClosureEnv, typename Args, typename Env>
struct Apply<Closure<Params, Expr, ClosureEnv>, Args, Env> {
    using args_env = typename ArgsEnv<Params, Args, ClosureEnv>::env;
    using result = typename SeqEval<Expr, args_env>::result;
};