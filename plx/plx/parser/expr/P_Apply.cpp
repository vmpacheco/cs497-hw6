#include <cassert>

#include <plx/data/Queue.hpp>
#include <plx/expr/Apply.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/parser/expr/P_Expr.hpp>
#include <plx/parser/P_Primitive.hpp>

namespace PLX {

    bool pArgumentList(List*& tokens, Object*& value) {
        return pProperListOf(pOpenParen, pAny, pComma, pCloseParen, ")", tokens, value);
    }

    bool pApply(List*& tokens, Object*& value) {

        Object* ident;
        
        if (!pIdentifier(tokens, ident)) {
            if (!pParenExpr(tokens, ident)) {
                std::cout << "failed at parenexpr";
                return false;
            } else if (!pArgumentList(tokens, value)) {
                std::cout << "failed at no ident arg list";
                return false;
            }
        }

        if (!pArgumentList(tokens, value)) {
            std::cout << "failed at arg list";
            return false;
        }

        Queue* valueQueue = static_cast<Queue*>(value);
        
        value = new Apply(ident, valueQueue->asList());

        return true;
    }

}
