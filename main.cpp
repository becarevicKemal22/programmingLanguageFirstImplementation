#include <iostream>
#include <fstream>
#include <string>

#include <Lexer.h>
#include <ErrorPrinter.h>

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
            ErrorPrinter printer(source);
            Lexer lexer(source);
            lexer.tokenize(printer);
            lexer.print();
        }else{
            std::cout << "Error opening file. Check if there is a file with the selected name.\n";
        }
    }else{
        std::cout << "Usage: main.exe programName.prog\n";
    }
    return 0;
}
