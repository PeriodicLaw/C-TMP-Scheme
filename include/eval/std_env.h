#pragma once

namespace {
    using env0 = empty_env;
    using env1 = add_env<sym("apply"), Builtin<builtins::Builtin_apply>, env0>;
    using env2 = add_env<sym("eval"), Builtin<builtins::Builtin_eval>, env1>;
    using env3 = add_env<sym("atom?"), Builtin<builtins::Builtin_is_atom>, env2>;
    using env4 = add_env<sym("bool?"), Builtin<builtins::Builtin_is_bool>, env3>;
    using env5 = add_env<sym("int?"), Builtin<builtins::Builtin_is_int>, env4>;
    using env6 = add_env<sym("string?"), Builtin<builtins::Builtin_is_string>, env5>;
    using env7 = add_env<sym("symbol?"), Builtin<builtins::Builtin_is_symbol>, env6>;
    using env8 = add_env<sym("pair?"), Builtin<builtins::Builtin_is_pair>, env7>;
    using env9 = add_env<sym("list?"), Builtin<builtins::Builtin_is_list>, env8>;
    using env10 = add_env<sym("car"), Builtin<builtins::Builtin_car>, env9>;
    using env11 = add_env<sym("cdr"), Builtin<builtins::Builtin_cdr>, env10>;
    using env12 = add_env<sym("cons"), Builtin<builtins::Builtin_cons>, env11>;
    using env13 = add_env<sym("list"), Builtin<builtins::Builtin_list>, env12>;
    using env14 = add_env<sym("+"), Builtin<builtins::Builtin_add>, env13>;
    using env15 = add_env<sym("-"), Builtin<builtins::Builtin_sub>, env14>;
    using env16 = add_env<sym("*"), Builtin<builtins::Builtin_mult>, env15>;
    using env17 = add_env<sym("/"), Builtin<builtins::Builtin_div>, env16>;
    using env18 = add_env<sym("%"), Builtin<builtins::Builtin_mod>, env17>;
    using env19 = add_env<sym("not"), Builtin<builtins::Builtin_not>, env18>;
    using env20 = add_env<sym("and"), Builtin<builtins::Builtin_and>, env19>;
    using env21 = add_env<sym("or"), Builtin<builtins::Builtin_or>, env20>;
    using env22 = add_env<sym("equal?"), Builtin<builtins::Builtin_is_equal>, env21>;
    using env23 = add_env<sym("="), Builtin<builtins::Builtin_num_equal>, env22>;
    using env24 = add_env<sym(">"), Builtin<builtins::Builtin_num_greater>, env23>;
}

using std_env = typename SeqEval<S(
        define("<", lambda(
            S(sym("x"), sym("y")),
            call("not", call("or",
                call("=", sym("x"), sym("y"),
                call(">", sym("x"), sym("y"))
            )))
        )),
        define("!=", lambda(
            S(sym("x"), sym("y")),
            call("not", call("=", sym("x"), sym("y")))
        )),
        define(">=", lambda(
            S(sym("x"), sym("y")),
            call("not", call("<", sym("x"), sym("y")))
        )),
        define("<=", lambda(
            S(sym("x"), sym("y")),
            call("not", call(">", sym("x"), sym("y")))
        )),
        
        define("Y", lambda(S(sym("F")),
            define("W", lambda(S(sym("x")),
                S(sym("F"),
                  lambda(sym("arg"),
                      call("apply",
                           S(sym("x"), sym("x")),
                           sym("arg"))
                      ))
            )),
            S(sym("W"), sym("W"))
        ))
    ), env24>::env;