#include <iostream>
#include <fstream>
#include <string>
#include "./src/parser/Parser.h"
#include "./src/error/ConsoleErrorPrinter.h"

void repl(){
    std::cout << "Repl v0.1\n";
    while(true){
        std::cout << "> ";
        std::string src;
        std::getline(std::cin, src);
        // Run program
    }
}

int main(int argc, char* argv[]) {
    if(argc == 1){
        repl();
    }else if(argc == 2){
        std::ifstream file(argv[1]);
        std::string source = "";
        if(file.is_open()){
            std::string line;
            while(std::getline(file, line)){
                line += '\n';
                source += line;
            }
            file.close();
            ConsoleErrorPrinter printer(source);
            Parser parser(printer);
            ast::Program program = parser.parse(source);
            program.printAST();
        }else{
            std::cout << "Error opening file. Check if there is a file with the selected name.\n";
        }
    }else{
        std::cout << "Usage: main.exe programName.prog\n";
    }
    return 0;
}
