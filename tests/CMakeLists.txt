project(tests)
add_subdirectory(lib/Catch2)

add_executable(tests LexerTest.cpp ../src/error/ErrorPrinter.cpp ../src/lexer/Lexer.cpp ../src/error/MockErrorPrinter.cpp ../src/error/MockErrorPrinter.h)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)