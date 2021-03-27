#include "scheme.h"

// NOT implemented

int main() {
    print<scheme<
        define("caar", lambda(S(sym("l")), call("car", call("car", sym("l"))))),
        define("cdar", lambda(S(sym("l")), call("cdr", call("car", sym("l"))))),
        define("cadr", lambda(S(sym("l")), call("car", call("cdr", sym("l"))))),
        defun("lookup-var",
            S(sym("var"), sym("env")),
            ifelse(
                call("equal?", sym("env"), q(S())),
                S(sym("error")),
                ifelse(
                    call("equal?", sym("var"), call("caar", sym("env"))),
                    call("cdar", sym("env")),
                    call("lookup-var", call("cdr", sym("env")))
                ))),
        defun("define-var",
            S(sym("var"), sym("value"), sym("env")),
            call("cons",
                call("cons", sym("var"), sym("value")),
                sym("env"))),
        defun("set-var",
            S(sym("var"), sym("value"), sym("env")),
            ifelse(
                call("equal?", sym("env"), q(S())),
                S(sym("error")),
                ifelse(
                    call("equal?", sym("var"), call("caar", sym("env"))),
                    call("cons",
                         call("cons", sym("var"), sym("value")),
                         call("cdar", sym("env"))),
                    call("cons",
                         call("car", sym("env")),
                         call("set-var", call("cdr", sym("env"))))
                ))),
        
        defun("eval",
            S(sym("exp"), sym("env")),
            
            define("self-evaluating?", lambda(S(sym("exp")), 
                call("or",
                     call("int?", sym("exp")),
                     call("bool?", sym("exp")),
                     call("string?", sym("exp"))
                ))),
            
            define("tagged-list?", lambda(S(sym("exp"), sym("tag")),
                ifelse(
                    call("pair?", sym("exp")),
                    call("equal?", call("car", sym("exp")), sym("tag")),
                    boolean(false)
                ))),
            
            cond(
                call("self-evaluating?", sym("exp")), sym("exp"),
                call("symbol?", sym("exp")), call("lookup-var", sym("exp"), sym("env")),
                call("tagged-list?", sym("exp"), q(sym("quote"))), sym("exp"),
                
                
                S(sym("error"))
            )
        ),
        
        call("eval", q(S(num(1), sym("a"))), q(S()))
    >>();
}