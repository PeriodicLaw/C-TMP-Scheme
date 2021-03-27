#include "scheme.h"

int main() {
    print<S(sym("eq?"), sym("x"), num(3))>();
    print<define("f",
                 lambda(
                         S(sym("x")),
                         S(sym("+"), sym("x"), num(3))))>();
    print<define("y",
                S(sym("+"), sym("x"), num(3)))>();
    print<q(sym("x"))>();
    print<qq(S(sym("x"), uq(sym("y")), str("z")))>();
    print<set("x",
              call("+",
                   sym("x"),
                   num(3)))>();
    print<Cons<sym("x"), sym("y")>>();
    return 0;
}