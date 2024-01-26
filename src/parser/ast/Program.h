//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_PROGRAM_H
#define MATURSKI_PROGRAM_H

#include <vector>
#include <memory>
#include "Statement.h"

namespace ast{

    class Program : public Statement {
    public:
        Program() : Statement() {
            body = {};
        }
        std::vector<std::shared_ptr<Statement>> body;
        void printAST(){
            for(auto stmt : body){
                stmt->print();
            }
        }
        void print() override {};
    };

}

#endif //MATURSKI_PROGRAM_H
