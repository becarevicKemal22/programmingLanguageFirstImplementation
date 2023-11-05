cmake_minimum_required(VERSION 3.25)
project(Maturski)

set(CMAKE_CXX_STANDARD 20)

include_directories("src/lexer" "src/error")
add_executable(Maturski main.cpp src/lexer/Lexer.cpp src/lexer/Lexer.h src/lexer/Token.cpp src/lexer/Token.h src/lexer/TokenType.h src/error/ErrorPrinter.cpp src/error/ErrorPrinter.h src/lexer/Keywords.h)
add_subdirectory(tests)
