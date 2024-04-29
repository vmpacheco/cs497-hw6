#include <cassert>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/expr/If.hpp>
#include <plx/object/Object.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_ReservedWords.hpp>
#include <plx/parser/P_Any.hpp>

namespace PLX {

    bool pIf(List*& tokens, Object*& value) {
        const std::initializer_list<Parser> parserList {
            pReservedIf,
            pRequireAny,
            pReservedThen,
            pRequireAny,
            pReservedElse,
            pRequireAny
        };
        if (!pSeq(parserList, tokens, value)) {
            return false;
        }

        Queue* valueQueue = static_cast<Queue*>(value);
        
        Object* cond = valueQueue->deq();
        Object* conseq = valueQueue->deq();
        Object* alt = valueQueue->deq();

        value = new If(cond, conseq, alt);

        return true;
    }

}
