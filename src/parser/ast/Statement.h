//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_STATEMENT_H
#define MATURSKI_STATEMENT_H

#include <memory>
#include "Interpreter.h"
#include "Resolver.h"

namespace ast {
    class Statement{
    public:
        Statement() = default;
        virtual ~Statement() = default;
        virtual RuntimeValuePtr accept(Interpreter* visitor) const {
            return visitor->visitStatement(this);
        };
        virtual void accept(Resolver* visitor) const {
            return visitor->visitStatement(this);
        };
        virtual void print() = 0;
    };
}

#endif //MATURSKI_STATEMENT_H
