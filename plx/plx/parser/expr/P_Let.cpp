#include <cassert>

#include <plx/data/Triple.hpp>
#include <plx/expr/Let.hpp>
#include <plx/expr/LetIn.hpp>
#include <plx/data/Queue.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_ReservedWords.hpp>
#include <plx/parser/P_Any.hpp>
#include <plx/parser/expr/P_Expr.hpp>
#include <plx/parser/P_SpecialChars.hpp>

namespace PLX {


    bool pLet(List*& tokens, Object*& value) {
        const std::initializer_list<Parser> parserList {
            pReservedLet,
            pIdentifier,
            pIgnoreEquals,
            pRequireAny
        };
        if (!pSeq(parserList, tokens, value)) {
            return false;
        }

        Queue* valueQueue = static_cast<Queue*>(value);

        Object* identifier = valueQueue->deq();
        Object* tripleValue = valueQueue->deq();

        Triple* bindings = new Triple(identifier, tripleValue);

        Object* ignore;
        if (pReservedIn(tokens, ignore)) {
            Object* body = new Object();
            
            if (!pRequireAny(tokens, body)) {
                return false;
            }

            value = new LetIn(bindings, body);
        } else {
            value = new Let(bindings);
        }

        return true;
    }

}