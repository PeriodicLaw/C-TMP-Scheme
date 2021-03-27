#include "scheme.h"

// 用Scheme实现的Y组合子。由于严格求值的缘故，需要修改为Z组合子。详见：
// https://stackoverflow.com/questions/37469378/y-combinator-implementation-scheme/37492667#37492667

int main() {
    
    print<scheme<
        define("Y", lambda(S(sym("F")),
            define("W", lambda(S(sym("x")),
                S(sym("F"),
                  lambda(sym("arg"),
                      call("apply",
                           S(sym("x"), sym("x")),
                           sym("arg"))
                  ))
            )),
            S(sym("W"), sym("W")))),
        define("F*", lambda(S(sym("func-arg")),
            lambda(S(sym("n")),
                ifelse(call("equal?", sym("n"), num(0)),
                       num(1),
                       call("*", sym("n"),
                            call("func-arg",
                                 call("-", sym("n"), num(1)))))
            ))),
        S(S(sym("Y"), sym("F*")), num(5))
    >>();
    
    return 0;
}