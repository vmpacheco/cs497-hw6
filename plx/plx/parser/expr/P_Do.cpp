#include <cassert>

#include <plx/data/Queue.hpp>
#include <plx/expr/Do.hpp>
#include <plx/parser/P_Primitive.hpp>
#include <plx/parser/P_ReservedWords.hpp>

namespace PLX {

    bool pDo(List*& tokens, Object*& value) {
        
        if (!pReservedDo(tokens, value)) {
            return false;
        }

        Object* any;
        Queue* exprs = new Queue();

        while (pAny(tokens, any)) {
            exprs->enq(any);
        }

        if (!pReservedEnd(tokens, value)) {
            return false;
        }

        value = new Do(exprs->asList());

        return true;
    }

}
