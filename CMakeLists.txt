cmake_minimum_required(VERSION 3.25)
project(Maturski)

set(CMAKE_CXX_STANDARD 20)

include_directories("src/lexer" "src/error" "src/parser" "src/parser/ast" "src/parser/visitor")
add_executable(Maturski main.cpp src/lexer/Lexer.cpp src/lexer/Lexer.h src/lexer/Token.h src/lexer/TokenType.h src/error/ErrorPrinter.cpp src/error/ErrorPrinter.h src/lexer/Keywords.h src/error/ConsoleErrorPrinter.cpp src/error/ConsoleErrorPrinter.h src/parser/NodeType.h src/parser/ast/Statement.h src/parser/Parser.cpp src/parser/Parser.h src/parser/ast/Program.h src/parser/ast/Expression.h src/parser/ast/NumericLiteral.h src/parser/visitor/Visitor.h src/parser/visitor/AstPrinter.h src/parser/ast/Identifier.h)
add_subdirectory(tests)
