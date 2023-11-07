//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_STATEMENT_H
#define MATURSKI_STATEMENT_H

#include <memory>
#include "../visitor/Visitor.h"

namespace ast {
    class Statement{
    public:
        Statement() = default;
        virtual ~Statement() = default;
//        virtual void accept(Visitor* visitor) const {
//            visitor->visitStatement(this);
//        };
        virtual void print() = 0;
    };
}

#endif //MATURSKI_STATEMENT_H
