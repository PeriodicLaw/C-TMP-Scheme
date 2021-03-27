#include "scheme.h"

int main() {
    print<scheme<
        defun("list-ref",
            S(sym("items"), sym("n")),
            ifelse(
                call("=", sym("n"), num(0)),
                call("car", sym("items")),
                call("list-ref", call("cdr", sym("items")), call("-", sym("n"), num(1)))
            )),
        define("squares",
            call("list", num(1), num(4), num(9), num(16), num(25))),
        call("list-ref", sym("squares"), num(3))
    >>();
    
    print<scheme<
        defun("length",
            S(sym("items")),
            ifelse(
                call("equal?", sym("items"), q(S())),
                num(0),
                call("+", num(1), call("length", call("cdr", sym("items"))))
            )),
        define("odds",
            call("list", num(1), num(3), num(5), num(7))),
        call("length", sym("odds"))
    >>();
    
    print<scheme<
        defun("map",
            S(sym("proc"), sym("items")),
            ifelse(
                call("equal?", sym("items"), q(S())),
                q(S()),
                call("cons",
                     call("proc", call("car", sym("items"))),
                     call("map", sym("proc"), call("cdr", sym("items")))
                     ))),
        call("map",
             lambda(S(sym("x")), call("*", sym("x"), sym("x"))),
             call("list", num(1), num(2), num(3), num(4)))
    >>();
}