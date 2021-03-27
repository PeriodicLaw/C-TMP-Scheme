#pragma once
#include "atom_helpers.h"
#include "sexp_helper.h"

#define define(name, expr) S(sym("define"), sym(name), expr)
#define set(name, expr) S(sym("set!"), sym(name), expr)
#define lambda(vars, expr...) S(sym("lambda"), vars, expr)
#define ifelse(cond, left, right) S(sym("if"), cond, left, right)
#define call(name, expr...) S(sym(name), expr)

#define q(expr) S(sym("quote"), expr)
#define uq(expr) S(sym("unquote"), expr)
#define qq(expr) S(sym("quasiquote"), expr)

#define defun(name, vars, expr...) \
  define(name,                     \
    call("Y", lambda(S(sym(name)), \
      lambda(vars, expr)           \
    )))

namespace cond_builder {
    template<typename...> struct CondBuilder;
    template<typename Expr> struct CondBuilder<Expr> {
        using Type = Expr;
    };
    template<typename Cond, typename Expr, typename... Others>
    struct CondBuilder<Cond, Expr, Others...> {
        using Type = ifelse(Cond, Expr, typename CondBuilder<Others...>::Type);
    };
}

#define cond(expr...) typename cond_builder::CondBuilder<expr>::Type