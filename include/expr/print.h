#pragma once
#include <iostream>

namespace printer {
    
    template<char...> struct StringPrinter;
    template<typename> struct ListPrinter;
    template<typename> struct Printer;
    
    
    
    template<> struct StringPrinter<> {
        static void print() {}
    };
    template<char c, char... s> struct StringPrinter<c, s...> {
        static void print() {
            std::cout << c;
            StringPrinter<s...>::print();
        }
    };
    
    
    
    template<typename A> struct ListPrinter<Cons<A, Nil>> {
        static void print() {
            Printer<A>::print();
        }
    };
    template<typename A, typename B, typename C> struct ListPrinter<Cons<A, Cons<B, C>>> {
        static void print() {
            Printer<A>::print();
            std::cout << " ";
            ListPrinter<Cons<B, C>>::print();
        }
    };
    template<typename A, typename B> struct ListPrinter<Cons<A, B>> {
        static void print() {
            Printer<A>::print();
            std::cout << " . ";
            Printer<B>::print();
        }
    };


    
    template<bool x> struct Printer<Bool<x>> {
        static void print() {
            std::cout << (x ? "#t" : "#f");
        }
    };
    template<int x> struct Printer<Int<x>> {
        static void print() {
            std::cout << x;
        }
    };
    template<char... s> struct Printer<String<s...>> {
        static void print() {
            std::cout << "\"";
            StringPrinter<s...>::print();
            std::cout << "\"";
        }
    };
    template<char... s> struct Printer<Symbol<s...>> {
        static void print() {
            StringPrinter<s...>::print();
        }
    };
    template<> struct Printer<Nil> {
        static void print() {
            std::cout << "()";
        }
    };
    template<typename A> struct Printer {
        static void print() {
            std::cout << "(";
            ListPrinter<A>::print();
            std::cout << ")";
        }
    };
    template<typename Func> struct Printer<Builtin<Func>> {
        static void print() {
            std::cout << "#<Builtin Function ";
            Func::print();
            std::cout << ">";
        }
    };
    template<typename Args, typename Expr, typename Env> struct Printer<Closure<Args, Expr, Env>> {
        static void print() {
            std::cout << "#<Closure>";
        }
    };
    
}

template<typename T>
inline static void print() {
    printer::Printer<T>::print();
    std::cout << std::endl;
}