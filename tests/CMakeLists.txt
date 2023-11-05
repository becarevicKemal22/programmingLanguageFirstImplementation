project(tests)
add_subdirectory(lib/Catch2)

add_executable(tests LexerTest.cpp ../src/error/ErrorPrinter.cpp ../src/lexer/Lexer.cpp)
target_link_libraries(tests Catch2::Catch2WithMain)