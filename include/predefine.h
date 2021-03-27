#pragma once

template<bool> struct Bool;
template<int> struct Int;
template<char...> struct String;
template<char...> struct Symbol;
struct Nil;
template<typename, typename> struct Cons;
template<typename> struct Builtin;
template<typename, typename, typename> struct Closure;

template<typename, typename> struct Eval;
template<typename, typename> struct SeqEval;
template<typename, typename, typename> struct Apply;