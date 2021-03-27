#pragma once

#include "predefine.h"

#include "expr/expr.h"
#include "expr/atom_helpers.h"
#include "expr/sexp_helper.h"
#include "expr/print.h"
#include "expr/simplifiers.h"

#include "eval/env.h"
#include "eval/eval.h"
#include "eval/apply.h"
#include "eval/builtins.h"
#include "eval/std_env.h"

template<typename... Exprs> using scheme = typename SeqEval<typename sexp_helper::SExpBuilder<Exprs...>::Type, std_env>::result;
