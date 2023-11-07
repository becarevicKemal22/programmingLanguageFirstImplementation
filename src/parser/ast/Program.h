//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_PROGRAM_H
#define MATURSKI_PROGRAM_H

#include <vector>
#include <memory>
#include "Statement.h"
#include "AstPrinter.h"

namespace ast{

    class Program : public Statement {
    public:
        Program() : Statement() {
            body = {};
        }
        std::vector<std::shared_ptr<Statement>> body;
        void printAST(){
            AstPrinter* printer = new AstPrinter();
            for(auto stmt : body){
                stmt->accept(printer);
            }
            delete printer;
        }
    };

}

#endif //MATURSKI_PROGRAM_H
