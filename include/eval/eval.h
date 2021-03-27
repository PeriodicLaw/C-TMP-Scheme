#pragma once

template<bool x, typename Env> struct Eval<Bool<x>, Env> {
    using result = Bool<x>;
    using env = Env;
};

template<int x, typename Env> struct Eval<Int<x>, Env> {
    using result = Int<x>;
    using env = Env;
};

template<char... s, typename Env> struct Eval<String<s...>, Env> {
    using result = String<s...>;
    using env = Env;
};

template<char... s, typename Env> struct Eval<Symbol<s...>, Env> {
    using result = find_env<Symbol<s...>, Env>;
    using env = Env;
};

template<char... Name, typename Expr, typename Env>
struct Eval<Cons<sym("define"), Cons<Symbol<Name...>, Cons<Expr, Nil>>>, Env> {
    using Var = Symbol<Name...>;
    using eval = Eval<Expr, Env>;
    using result = void;
    using env = add_env<Var, typename eval::result, typename eval::env>;
};

template<char... Name, typename Expr, typename Env>
struct Eval<Cons<sym("set!"), Cons<Symbol<Name...>, Cons<Expr, Nil>>>, Env> {
    using Var = Symbol<Name...>;
using eval = Eval<Expr, Env>;
    using result = void;
    using env = set_env<Var, typename eval::result, typename eval::env>;
};

template<typename Expr, typename Env>
struct Eval<Cons<sym("quote"), Cons<Expr, Nil>>, Env> {
    using result = Expr;
    using env = Env;
};

namespace {
    template<typename Expr, typename Env>
    struct QuasiQuote {
        using result = Expr;
        using env = Env;
    };
    template<typename Head, typename Tail, typename Env>
    struct QuasiQuote<Cons<Head, Tail>, Env> {
        using eval1 = QuasiQuote<Head, Env>;
        using eval2 = QuasiQuote<Tail, typename eval1::env>;
        using result = Cons<typename eval1::result, typename eval2::result>;
        using env = typename eval2::env;
    };
    template<typename Expr, typename Env>
    struct QuasiQuote<Cons<sym("unquote"), Cons<Expr, Nil>>, Env> {
        using eval = Eval<Expr, Env>;
        using result = typename eval::result;
        using env = typename eval::env;
    };
}

template<typename Expr, typename Env>
struct Eval<Cons<sym("quasiquote"), Cons<Expr, Nil>>, Env> {
    using quasiquote = QuasiQuote<Expr, Env>;
    using result = typename quasiquote::result;
    using env = typename quasiquote::env;
};

namespace {
    template<typename> struct GetBool;
    template<bool x> struct GetBool<Bool<x>> {
        static constexpr bool result = x;
    };
    
    template<bool, typename, typename> struct BoolChoose;
    template<typename A, typename B> struct BoolChoose<true, A, B> {
        using result = A;
    };
    template<typename A, typename B> struct BoolChoose<false, A, B> {
        using result = B;
    };
}

template<typename Cond, typename Left, typename Right, typename Env>
struct Eval<Cons<sym("if"), Cons<Cond, Cons<Left, Cons<Right, Nil>>>>, Env> {
    using eval_cond = Eval<Cond, Env>;
    using eval = typename BoolChoose<
            GetBool<typename eval_cond::result>::result,
            Eval<Left, typename eval_cond::env>,
            Eval<Right, typename eval_cond::env>>::result;
    using result = typename eval::result;
    using env = typename eval::env;
};

namespace {
    template<typename Args, typename Env> struct ListEval;

    template<typename Env> struct ListEval<Nil, Env> {
        using result = Nil;
        using env = Env;
    };

    template<typename First, typename Others, typename Env>
    struct ListEval<Cons<First, Others>, Env> {
        using eval_first = Eval<First, Env>;
        using eval_others = ListEval<Others, typename eval_first::env>;
        using result = Cons<typename eval_first::result, typename eval_others::result>;
        using env = typename eval_others::env;
    };
}

template<typename Caller, typename Args, typename Env>
struct Eval<Cons<Caller, Args>, Env> {
    using caller = typename Eval<Caller, Env>::result;
    using evalargs = ListEval<Args, Env>;
    using apply = Apply<caller, typename evalargs::result, typename evalargs::env>;
    using result = typename apply::result;
    using env = typename evalargs::env;
};

template<typename Args, typename Exprs, typename Env>
struct Eval<Cons<sym("lambda"), Cons<Args, Exprs>>, Env> {
    using result = Closure<Args, Exprs, Env>;
    using env = Env;
};



template<typename Last, typename Env>
struct SeqEval<Cons<Last, Nil>, Env> {
    using eval_last = Eval<Last, Env>;
    using result = typename eval_last::result;
    using env = typename eval_last::env;
};

template<typename First, typename Others, typename Env>
struct SeqEval<Cons<First, Others>, Env> {
    using eval_first = Eval<First, Env>;
    using eval_others = SeqEval<Others, typename eval_first::env>;
    using result = typename eval_others::result;
    using env = typename eval_others::env;
};