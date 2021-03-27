#pragma once
#include <iostream>

namespace builtins {
    struct Builtin_apply {
        static void print() {
            std::cout << "apply";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Caller, typename Args, typename Env>
        struct FuncApply<Cons<Caller, Cons<Args, Nil>>, Env> {
            using result = typename Apply<Caller, Args, Env>::result;
        };
        
        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_eval {
        static void print() {
            std::cout << "eval";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Arg, typename Env>
        struct FuncApply<Cons<Arg, Nil>, Env> {
            using result = typename Eval<Arg, Env>::result;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    
    
    struct Builtin_is_atom {
        static void print() {
            std::cout << "atom?";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Arg, typename Env>
        struct FuncApply<Cons<Arg, Nil>, Env> {
            using result = Bool<false>;
        };
        template<int x, typename Env>
        struct FuncApply<Cons<Int<x>, Nil>, Env> {
            using result = Bool<true>;
        };
        template<bool x, typename Env>
        struct FuncApply<Cons<Bool<x>, Nil>, Env> {
            using result = Bool<true>;
        };
        template<char... s, typename Env>
        struct FuncApply<Cons<String<s...>, Nil>, Env> {
            using result = Bool<true>;
        };
        template<char... s, typename Env>
        struct FuncApply<Cons<Symbol<s...>, Nil>, Env> {
            using result = Bool<true>;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_is_bool {
        static void print() {
            std::cout << "bool?";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Arg, typename Env>
        struct FuncApply<Cons<Arg, Nil>, Env> {
            using result = Bool<false>;
        };
        template<bool x, typename Env>
        struct FuncApply<Cons<Bool<x>, Nil>, Env> {
            using result = Bool<true>;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_is_int {
        static void print() {
            std::cout << "int?";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Arg, typename Env>
        struct FuncApply<Cons<Arg, Nil>, Env> {
            using result = Bool<false>;
        };
        template<int x, typename Env>
        struct FuncApply<Cons<Int<x>, Nil>, Env> {
            using result = Bool<true>;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_is_string {
        static void print() {
            std::cout << "string?";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Arg, typename Env>
        struct FuncApply<Cons<Arg, Nil>, Env> {
            using result = Bool<false>;
        };
        template<char... s, typename Env>
        struct FuncApply<Cons<String<s...>, Nil>, Env> {
            using result = Bool<true>;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_is_symbol {
        static void print() {
            std::cout << "symbol?";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Arg, typename Env>
        struct FuncApply<Cons<Arg, Nil>, Env> {
            using result = Bool<false>;
        };
        template<char... s, typename Env>
        struct FuncApply<Cons<Symbol<s...>, Nil>, Env> {
            using result = Bool<true>;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_is_pair {
        static void print() {
            std::cout << "pair?";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Arg, typename Env>
        struct FuncApply<Cons<Arg, Nil>, Env> {
            using result = Bool<false>;
        };
        template<typename A, typename B, typename Env>
        struct FuncApply<Cons<Cons<A, B>, Nil>, Env> {
            using result = Bool<true>;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_is_list {
        static void print() {
            std::cout << "list?";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Arg, typename Env>
        struct FuncApply<Cons<Arg, Nil>, Env> {
            using result = Bool<false>;
        };
        template<typename Env>
        struct FuncApply<Cons<Nil, Nil>, Env> {
            using result = Bool<true>;
        };
        template<typename A, typename B, typename Env>
        struct FuncApply<Cons<Cons<A, B>, Nil>, Env> {
            using result = typename FuncApply<B, Env>::result;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_car {
        static void print() {
            std::cout << "car";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename A, typename B, typename Env>
        struct FuncApply<Cons<Cons<A, B>, Nil>, Env> {
            using result = A;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_cdr {
        static void print() {
            std::cout << "cdr";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename A, typename B, typename Env>
        struct FuncApply<Cons<Cons<A, B>, Nil>, Env> {
            using result = B;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_cons {
        static void print() {
            std::cout << "cons";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename A, typename B, typename Env>
        struct FuncApply<Cons<A, Cons<B, Nil>>, Env> {
            using result = Cons<A, B>;
        };

        template<typename Arg, typename Env>
        using apply = typename FuncApply<Arg, Env>::result;
    };
    
    struct Builtin_list {
        static void print() {
            std::cout << "list";
        }

        template<typename Arg, typename Env>
        using apply = Arg;
    };
    
    struct Builtin_add {
        static void print() {
            std::cout << "+";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Env>
        struct FuncApply<Nil, Env> {
            static constexpr int result = 0;
        };
        template<int x, typename Others, typename Env>
        struct FuncApply<Cons<Int<x>, Others>, Env> {
            static constexpr int result = x + FuncApply<Others, Env>::result;
        };

        template<typename Arg, typename Env>
        using apply = Int<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_sub {
        static void print() {
            std::cout << "-";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<int x, int y, typename Env>
        struct FuncApply<Cons<Int<x>, Cons<Int<y>, Nil>>, Env> {
            static constexpr int result = x-y;
        };

        template<typename Arg, typename Env>
        using apply = Int<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_mult {
        static void print() {
            std::cout << "*";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Env>
        struct FuncApply<Nil, Env> {
            static constexpr int result = 1;
        };
        template<int x, typename Others, typename Env>
        struct FuncApply<Cons<Int<x>, Others>, Env> {
            static constexpr int result = x * FuncApply<Others, Env>::result;
        };

        template<typename Arg, typename Env>
        using apply = Int<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_div {
        static void print() {
            std::cout << "/";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<int x, int y, typename Env>
        struct FuncApply<Cons<Int<x>, Cons<Int<y>, Nil>>, Env> {
            static_assert(y != 0);
            static constexpr int result = x/y;
        };

        template<typename Arg, typename Env>
        using apply = Int<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_mod {
        static void print() {
            std::cout << "%";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<int x, int y, typename Env>
        struct FuncApply<Cons<Int<x>, Cons<Int<y>, Nil>>, Env> {
            static_assert(y != 0);
            static constexpr int result = x%y;
        };

        template<typename Arg, typename Env>
        using apply = Int<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_not {
        static void print() {
            std::cout << "not";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<bool x, typename Env>
        struct FuncApply<Cons<Bool<x>, Nil>, Env> {
            static constexpr bool result = !x;
        };

        template<typename Arg, typename Env>
        using apply = Bool<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_and {
        static void print() {
            std::cout << "and";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Env>
        struct FuncApply<Nil, Env> {
            static constexpr bool result = true;
        };
        template<bool x, typename Others, typename Env>
        struct FuncApply<Cons<Bool<x>, Others>, Env> {
            static constexpr bool result = x && FuncApply<Others, Env>::result;
        };

        template<typename Arg, typename Env>
        using apply = Bool<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_or {
        static void print() {
            std::cout << "or";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename Env>
        struct FuncApply<Nil, Env> {
            static constexpr bool result = false;
        };
        template<bool x, typename Others, typename Env>
        struct FuncApply<Cons<Bool<x>, Others>, Env> {
            static constexpr bool result = x || FuncApply<Others, Env>::result;
        };

        template<typename Arg, typename Env>
        using apply = Bool<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_is_equal {
        static void print() {
            std::cout << "equal?";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<typename A, typename B, typename Env>
        struct FuncApply<Cons<A, Cons<B, Nil>>, Env> {
            static constexpr bool result = false;
        };
        template<typename A, typename Env>
        struct FuncApply<Cons<A, Cons<A, Nil>>, Env> {
            static constexpr bool result = true;
        };

        template<typename Arg, typename Env>
        using apply = Bool<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_num_equal {
        static void print() {
            std::cout << "=";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<int x, int y, typename Env>
        struct FuncApply<Cons<Int<x>, Cons<Int<y>, Nil>>, Env> {
            static constexpr bool result = x == y;
        };

        template<typename Arg, typename Env>
        using apply = Bool<FuncApply<Arg, Env>::result>;
    };
    
    struct Builtin_num_greater {
        static void print() {
            std::cout << ">";
        }

        template<typename Arg, typename Env>
        struct FuncApply;
        template<int x, int y, typename Env>
        struct FuncApply<Cons<Int<x>, Cons<Int<y>, Nil>>, Env> {
            static constexpr bool result = x > y;
        };

        template<typename Arg, typename Env>
        using apply = Bool<FuncApply<Arg, Env>::result>;
    };
}