#include "scheme.h"

int main() {
    print<scheme<
        define("x", num(3)),
        sym("x")
    >>();
    print<scheme<
        define("x", num(3)),
        sym("x"),
        set("x", num(5)),
        sym("x")
    >>();

    print<scheme<
        q(S(num(1), sym("x"), str("y")))
    >>();
    print<scheme<
        q(set("x", boolean(true)))
    >>();
    print<scheme<
        define("y", num(3)),
        qq(S(num(1), sym("y"), str("y"), uq(sym("y"))))
    >>();

    print<scheme<
        define("f",
               lambda(S(sym("x")),
                      define("y", sym("x")),
                      sym("y"))),
        S(sym("f"), num(1))
    >>();

    print<scheme<
        S(sym("atom?"), q(S()))
    >>();
    print<scheme<
        S(sym("pair?"), q(S()))
    >>();
    print<scheme<
        call("eval",
             q(S(sym("list?"), q(S()))))
    >>();

    print<scheme<
        call("list",
             num(1), num(2), num(3))
    >>();
    print<scheme<
        call("cdr",
             q(S(num(1), num(3), num(5))))
    >>();

    print<scheme<
        define("f",
               lambda(S(sym("x")),
                      call("+",
                           sym("x"),
                           num(3)))),
        S(sym("f"), num(1))
    >>();
    
    print<scheme<
        call("apply",
             sym("+"),
             q(S(num(1), num(2), num(3))))
    >>();
    
    print<scheme<
        define("f",
               lambda(sym("l"),
                      call("apply",
                           sym("+"),
                           sym("l")))),
        S(sym("f"), num(1), num(2), num(3))
    >>();
    
    print<scheme<
        define("abs", lambda(S(sym("x")),
            ifelse(call(">", sym("x"), num(0)),
                   sym("x"),
                   call("-", num(0), sym("x")))
        )),
        call("abs", num(-3))
    >>();

    return 0;
}