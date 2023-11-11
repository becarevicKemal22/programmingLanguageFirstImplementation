#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"
#include "ConsoleErrorPrinter.h"
#include "Interpreter.h"
#include "RuntimeValue.h"
#include <chrono>

void repl(){
    std::cout << "Repl v0.1\n";
    while(true){
        std::cout << "> ";
        std::string src;
        std::getline(std::cin, src);
        // Run program
    }
}

int main(int argc, char* argv[]){
    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        std::ifstream file(argv[1]);
        std::string source;
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                line += '\n';
                source += line;
            }
            file.close();
            ConsoleErrorPrinter printer(source);
            Parser parser(printer);
            ast::Program program;
//            auto start = std::chrono::high_resolution_clock::now();
            try {
                program = parser.parse(source);
            } catch (std::runtime_error &err) {
                exit(1);
            }
            if(parser.hadError){
                exit(1);
            }
//            auto end = std::chrono::high_resolution_clock::now();
//            std::chrono::duration<double> duration = end - start;
//            double duration_seconds = duration.count();
//            std::cout << "Elapsed time: " << duration_seconds << " seconds" << std::endl;
            program.printAST();
            std::cout << "\n";
            std::cout << "Program successfully parsed.\n";
            Interpreter interpreter(printer);
            RuntimeValuePtr result = interpreter.visitProgram(&program);
            std::cout << "Result: " << result->stringify() << std::endl;

        } else {
            std::cout << "Error opening file. Check if there is a file with the selected name.\n";
        }
    } else {
        std::cout << "Usage: main.exe programName.prog\n";
    }

    return 0;
}
