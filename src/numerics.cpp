#include "scheme.h"

int main() {
    print<scheme<
        defun("fib",
            S(sym("n")),
            cond(
                call("=", sym("n"), num(0)), num(0),
                call("=", sym("n"), num(1)), num(1),
                call("+", call("fib", call("-", sym("n"), num(1))),
                          call("fib", call("-", sym("n"), num(2))))
            )),
        call("fib", num(5))
    >>();
    
    print<scheme<
        defun("gcd",
            S(sym("a"), sym("b")),
            ifelse(
                call("=", sym("b"), num(0)),
                sym("a"),
                call("gcd", sym("b"), call("%", sym("a"), sym("b")))
            )),
        call("gcd", num(206), num(40))
    >>();
    
    print<scheme<
        defun("prime?",
            S(sym("n")),
            defun("square", S(sym("x")),
                call("*", sym("x"), sym("x"))),
            defun("test-divisor", S(sym("m")),
                call("=", call("%", sym("n"), sym("m")), num(0))),
            defun("find-divisor", S(sym("m")),
                cond(
                    call(">", call("square", sym("m")), sym("n")), sym("n"),
                    call("test-divisor", sym("m")), sym("m"),
                    call("find-divisor", call("+", sym("m"), num(1)))
                )),
            call("=", sym("n"), call("find-divisor", num(2)))
        ),
        call("prime?", num(5))
    >>();
}